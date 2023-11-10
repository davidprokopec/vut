#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define SIZE 5
/**
Načtěte dvě pole číslic o velikosti 5 a určete počet společných číslic (pozice nehraje roli).
Nejprve předpokládejme, že pole neobsahují duplicity.
Vylepšit o možnost duplicit (např. pro [1,1,5,5,2] a [5,5,1,1,3] je v výsledek 2).
Zjednodušit tento program pomocí funkce, která pro zadané pole a číslo vrátí 0/1 podle toho, jestli se číslo v poli nachází.
*/
int main() 
{
    int arr1[SIZE], arr2[SIZE];

    printf("Write array of numbers #1: ");
    for(int i = 0; i < SIZE; i ++) {
        scanf("%d", &arr1[i]);
    }
    printf("\n");

    printf("Write array of numbers #2: ");
    for(int i = 0; i < SIZE; i ++) {
        scanf("%d", &arr2[i]);
    }
    printf("\n");

    int match = 0;
    for(int i = 0; i < SIZE; i++) {
        bool same = false;

        for(int j = i-1; j >= 0; j--) {
            if(arr1[i] == arr1[j]) {
               same = true; 
               break;
            }
        }

        if(same) continue;

        for(int y = 0; y < SIZE; y++) {
            if(arr1[i] == arr2[y]) {
                match++;
            }
        }
    }

    printf("number of matches: %d \n", match);

}