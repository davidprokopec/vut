#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 20


bool check_if_only_letters(char string[])
{
    for(int i = 0; string[i] != '\0'; i++) {
        if (!((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= 'A' && string[i] <= 'Z'))) {
            return false;
        } 
    }

    return true;

}

int main()
{
    char name[LENGTH + 1];
    printf("Write your name: ");
    scanf("%20s", name);
    printf("\n");

    char surname[LENGTH + 1];
    printf("Write your surname: ");
    scanf("%20s", surname);
 \n    printf("\n");

    if(!check_if_only_letters(name) || !check_if_only_letters(surname)) {
        printf("Jmeno '%s %s' je nevalidni \n", name, surname);
        return 1;
    }


    printf("Jmeno '%s %s' je validni \n", name, surname);
    
    return 0;
}
