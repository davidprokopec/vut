#include <stdio.h>

int main()
{
    char replace;
    printf("Write a char to replace with _: ");
    scanf("%c", &replace);

    printf("\n");

    char str[101];

    printf("Write a string: ");
    scanf("%100s", str);

    printf("\n");

    printf("String you wrote: %s\n", str);

    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] == replace) {
            str[i] = '_';
        }
    }
    
    printf("Converted %c to _: %s\n", replace, str);

    return 0;
}