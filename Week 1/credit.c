#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int getNumberLength(long num){
    return floor(log10(labs(num))) + 1;
}

long calculateChecksum(long number){
    int nDigits = getNumberLength(number);
    int posLastDigit = nDigits - 1;
    int checksum = 13;

    int pointer = posLastDigit;
    int mod = 10;
    while (pointer >=0){
        printf("Num: %ld", number % mod);
        checksum += number % mod;
        mod *= 10;
    }

    return checksum;
}





bool isNumberValid(long num){
    if (num == 0) return false;
    return true;
}

int main()
{
    int number = get_long("Number: ");
    while (!isNumberValid(number))
    {
        number = get_long("Number: ");
    }
    long c = calculateChecksum(number);
    printf("Checksum: %ld", c);

}
