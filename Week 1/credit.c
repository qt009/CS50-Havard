#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum Type { Mastercard, VISA, American_Express, Default };

struct Card
{
    enum Type type;
    long long number;
};

string printType(enum Type type)
{
    string t;
    switch (type)
    {
        case American_Express:
            t = "AMEX";
            break;
        case VISA:
            t = "VISA";
            break;
        case Mastercard:
            t = "MASTERCARD";
            break;
        default:
            t = "INVALID";
            break;
    }
    return t;
}

int getNumberLength(long long num)
{

    if (num == 0)
        return 1;
    int length = 0;
    unsigned long long n = (num < 0) ? (unsigned long long) llabs(num) : (unsigned long long) num;
    while (n > 0)
    {
        n /= 10;
        length++;
    }
    return length;
}

// long long calculateChecksum(long long number){
//     int nDigits = getNumberLength(number);
//     int posLastDigit = nDigits - 1;

//     int firstSum = 0;
//     int secondSum = 0;

//     int pointer = posLastDigit-1;
//     int mod = 10;
//     int div = 1;
//     while (pointer >=0){

//         firstSum += ((number % mod)/div) * 2;
//         mod *= 100;
//         div = div * 100;

//         pointer -= 2;
//     }

//     pointer = posLastDigit;
//     mod = 1;
//     div = 1;
//     while (pointer >=0){

//         secondSum += ((number % mod)/div);
//         mod *= 10;
//         div = div * 100;

//         pointer --;
//     }

//     return firstSum + secondSum;
// }

long long calculateChecksum(long long number)
{
    int total = 0;
    bool every_other = false;
    // process from last digit up
    while (number > 0)
    {
        int digit = number % 10;
        number /= 10;
        if (every_other)
        {
            int prod = digit * 2;
            // sum digits of prod:
            total += (prod / 10) + (prod % 10);
        }
        else
        {
            total += digit;
        }
        every_other = !every_other;
    }
    return total;
}

bool isCardValid(struct Card *card)
{
    long long num = card->number;

    long long nDigits = getNumberLength(num);

    if (nDigits == 15)
    {
        card->type = American_Express;
    }
    else if (nDigits == 13)
    {
        card->type = VISA;
    }

    int frontDigit = num / pow(10, nDigits - 1);
    int twoFrontDigits = num / pow(10, nDigits - 2);

    switch (card->type)
    {
        case American_Express:
            if ((twoFrontDigits != 34) && (twoFrontDigits != 37))
                return false;
            break;
        case VISA:
            if (frontDigit != 4)
                return false;
            break;
        case Mastercard:
            if ((twoFrontDigits < 51) || (twoFrontDigits > 55))
                return false;
            break;
        case Default:
            if (((nDigits == 13) || (nDigits == 16)) && (frontDigit == 4))
            {
                card->type = VISA;
                return true;
            }
            if ((nDigits == 16) && ((twoFrontDigits >= 51) && (twoFrontDigits <= 55)))
            {
                card->type = Mastercard;
                return true;
            }

        default:
            return false;
            break;
    }

    return true;
}

int main()
{
    long long number = get_long_long("Number: ");

    struct Card card;
    card.number = number;
    card.type = Default;

    // while (!isCardValid(&card))
    // {
    //     number = get_long_long("Number: ");
    //     card.number = number;
    // }

    if (isCardValid(&card))
    {
        long long c = calculateChecksum(number);

        if ((c % 10) == 0)
        {
            printf("%s\n", printType(card.type));
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
