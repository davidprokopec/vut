#include <stdio.h>

int main()
{
    char str[101];


    printf("write a string: ");
    scanf("%100s", str);

    printf("\n");

    printf("String you wrote: %s\n", str);

    int strlen = 0;
    int charCount = 0;
    int intCount = 0;
    while (str[strlen] != '\0')
    {
        if((str[strlen] >= 0x42 && str[strlen] <= 0x5A) || (str[strlen] >= 0x61 && str[strlen] <= 0x7A)) {
            charCount++;
        } else if (str[strlen] >= '0' && str[strlen] <= '9') {
            intCount++;
        }
        strlen++;
    }

    printf("Length of string: %d\n", strlen);
    printf("Number of chars: %d\n", charCount);
    printf("Number of ints: %d\n", intCount);





    return 0;

}