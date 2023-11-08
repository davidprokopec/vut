#include <stdio.h>

int main()
{
    char str[101];

    printf("write a string: ");
    scanf("%100s", str);

    printf("\n");

    printf("String you wrote: %s\n", str);



    return 0;

}