#include <stdio.h>

int main()
{
    char str[101];

    printf("write a string: ");
    scanf("%100s", str);

    printf("\n");

    printf("String you wrote: %s\n", str);

    int strlen = 0;
    while (str[strlen] != '\0')
    {
        strlen++;
    }

    printf("Length of string: %d\n", strlen);



    return 0;

}