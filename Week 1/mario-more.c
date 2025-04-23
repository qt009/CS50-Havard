#include <cs50.h>
#include <stdio.h>

#define BRICK '#'

void printMiddle(char blank)
{
    for (int i = 0; i < 2; i++)
    {
        printf("%c", blank);
    }
}

void printRow(int row, int height)
{
    int numberOfBlanks = height - row - 1;
    int numberOfBricks = row + 1;
    char blank = ' ';

    for (int i = 0; i < numberOfBlanks; i++)
    {
        printf("%c", blank);
    }

    for (int i = 0; i < numberOfBricks; i++)
    {
        printf("%c", BRICK);
    }

    printMiddle(blank);

    for (int i = 0; i < numberOfBricks; i++)
    {
        printf("%c", BRICK);
    }

    // no need for this since we just continue
    // for (int i = 0; i < numberOfBlanks; i++){
    //     printf("%c", blank);
    // }

    printf("\n");
}

void out_print(int height)
{

    for (int row = 0; row < height; row++)
    {
        printRow(row, height);
    }
}

bool isHeightValid(int height)
{
    if (height <= 0)
        return false;
    if (height > 8)
        return false;
    return true;
}

int main()
{
    int height = get_int("Height: ");

    while (!isHeightValid(height))
    {
        height = get_int("Height: ");
    }

    out_print(height);
}
