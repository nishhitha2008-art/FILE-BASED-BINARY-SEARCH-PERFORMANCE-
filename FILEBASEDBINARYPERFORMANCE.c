#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 500
#define RANGE 10000

int main()
{
    FILE *fp;
    long numbers[MAX];
    long i, j, temp, number;
    long low, high, mid;
    long value;
    int count, duplicate, found;

    srand((unsigned)time(NULL));

    /* Generate 500 unique random numbers */
    count = 0;

    while (count < MAX)
    {
        number = (rand() % RANGE) + 1;
        duplicate = 0;

        for (i = 0; i < count; i++)
        {
            if (numbers[i] == number)
            {
                duplicate = 1;
                break;
            }
        }

        if (duplicate == 0)
        {
            numbers[count] = number;
            count++;
        }
    }

    /* Sort numbers in ascending order */
    for (i = 0; i < MAX - 1; i++)
    {
        for (j = 0; j < MAX - 1 - i; j++)
        {
            if (numbers[j] > numbers[j + 1])
            {
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }

    /* Store numbers in file */
    fp = fopen(
        "C:\\TURBOC3\\BIN\\PROJECT\\newname.txt", "w"
    );

    if (fp == NULL)
    {
        printf("\nFile cannot be created.");
        return 1;
    }

    for (i = 0; i < MAX; i++)
    {
        fprintf(fp, "%ld\n", numbers[i]);
    }

    fclose(fp);

    printf("\n500 unique random numbers generated successfully.");
    printf("\nNumbers sorted in ascending order.");
    printf("\nSaved in newname.txt");

    /* Input search number */
    printf("\n\nEnter the number to search (1-10000): ");

    if (scanf("%ld", &number) != 1)
    {
        printf("\nInvalid input.");
        return 1;
    }

    if (number < 1 || number > RANGE)
    {
        printf("\nEnter a number between 1 and 10000.");
        return 0;
    }

    /* Open file for binary search */
    fp = fopen(
        "C:\\TURBOC3\\BIN\\PROJECT\\newname.txt", "r"
    );

    if (fp == NULL)
    {
        printf("\nFile cannot be opened.");
        return 1;
    }

    low = 0;
    high = MAX - 1;
    found = 0;

    /* Binary search using file positions */
    while (low <= high)
    {
        mid = low + (high - low) / 2;

        rewind(fp);

        for (i = 0; i <= mid; i++)
        {
            if (fscanf(fp, "%ld", &value) != 1)
            {
                fclose(fp);
                printf("\nError reading file.");
                return 1;
            }
        }

        if (value == number)
        {
            found = 1;
            break;
        }
        else if (value < number)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    fclose(fp);

    /* Display result */
    if (found == 1)
    {
        printf("\nNumber %ld found successfully.", number);
        printf("\nPosition in newname.txt: %ld", mid + 1);
    }
    else
    {
        printf("\nNumber %ld not found in newname.txt.", number);
    }

    return 0;
}