#include <stdio.h>
#include <string.h>

int main()
{
    char str1[101];
    printf("Write a string #1: ");
    scanf("%100s", str1);
    printf("String #1: %s\n", str1);
    printf("\n");

    char str2[101];
    printf("Write a string #2: ");
    scanf("%100s", str2);
    printf("String #2: %s\n", str2);
    printf("\n");
    

    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0') {
        if(str1[i] != str2[i]) {
            break;
        }
        i++;
    }

    if(str1[i] == '\0' && str2[i] == '\0') {
        printf("strings are the same\n");
    } else {
        printf("strings are not the same\n");
    }

    return 0;

}