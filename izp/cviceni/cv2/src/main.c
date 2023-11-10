#include <stdio.h>
#include <stdlib.h>

#define SIZE 4


int main()
{
    int numbers[SIZE];
    int max;
    int average;
    int total;


    for (int i = 0; i <= SIZE; i++) {
        scanf("%d", &numbers[i]);
    }

    max = numbers[0];


    for (int i = 0; i <= SIZE; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }

        total = total + numbers[i];
    }


    average = total / (SIZE + 1);


    printf("Maximum je: %d\n", max);
    printf("Soucet je: %d\n", total);
    printf("Prumer je: %d\n", average);


    return 0;
}
