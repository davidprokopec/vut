#include <stdio.h>
#include <string.h>

#define LENGTH 20


int my_max(int a, int b) 
{
    if (a > b) {
        return a;
    }
    return b;
}

int my_abs(int x)
{
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

int my_crazy_min(int a, int b)
{
    if(a < b) {
        return my_abs(a);
    } 
    return my_abs(b);
}

// vrací délku řetězce v počtu znaků
int my_strlen(char str[])
{
    int i = 0;
    while(str[i] != '\0') {
        i++;
    }
    return i;
}

// hledá první výskyt znaku v řetězci, vrací -1, pokud se znak v řetězci nevyskytuje
int my_strchr(char str[], char ch)
{
    int i = 0;
    while(str[i] != '\0') {
        if(str[i] == ch) {
            return i;
        }
        i++;
    }
    return -1;
}

// hledá poslední výskyt znaku v řetězci, vrací -1, pokud znak neobsahuje
int my_strrchr(char str[], char ch)
{
    int i = 0;
    int last = -1;
    while(str[i] != '\0') {
        if (str[i] == ch) {
            last = i;
        }
        i++;
    }
    return last;

}

int get_max(int arr[], int len)
{
    int max = arr[0];
    for(int i = 1; i < len; i++) {
        if (arr[i] > max) {
            max = i;
        }
    }

    return max;
}

int get_sum(int arr[], int len)
{
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += arr[i];
    }

    return sum;
}

// Funkce porovná pole a vrací 1, pokud každý prvek v poli arr1
// je menší než prvek na stejném indexu v poli arr2.
int smaller_than(int arr1[], int arr2[], int arr_len)
{
    for (int i = 0; i < arr_len; i++) {
        if(arr1[i] >= arr2[i]) {
            return 0;
        }
    }
    return 1;
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
    printf("\n");

    if(!check_if_only_letters(name) || !check_if_only_letters(surname)) {
        printf("Jmeno '%s %s' je nevalidni \n", name, surname);
        return 1;
    }


    printf("Jmeno '%s %s' je validni \n", name, surname);
    
    return 0;
}
