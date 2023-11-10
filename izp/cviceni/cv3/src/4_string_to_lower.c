#include <stdio.h>

int main()
{
    char str[101];


    printf("write a string: ");
    scanf("%100s", str);

    printf("\n");

    printf("String you wrote: %s\n", str);

    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 0x20;
        }
    }
    
    printf("Converted string to lowercase: %s\n", str);

    return 0;
}