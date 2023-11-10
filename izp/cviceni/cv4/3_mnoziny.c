#include <stdio.h>
#include <string.h>

/**
Uvažujeme množiny čísel s fixní maximální velikostí (zatím nemáme dostatečnou znalost pro efektivnější reprezentaci). Implementujte funkce:
isInSet (prvek je v množině)
isSet (ověření, že pole reprezentuje množinu, tj. každý prvek se vyskytuje jen jednou)
printIntersection, printUnion, printProduct (průnik, sjednocení a kartézský součin množin)
*/

int is_it_set(int set[], int x, int len)
{
    for (int i = 0; i < len; i++) {
        if(set[i] == x) {
            return 1;
        }
    }
    return 0;
}

int is_set(int set[], int len) 
{
    for (int i = 0; i < len; i++) {
        for(int j = 1; j < len; i++) {
            if(set[i] == set[j]) {
                return 0;
            }
        }
    }
    return 1;
}

void print_intersection(int set1[], int set2[], int len) 
{
    printf("{ ");
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (set1[i] == set2[j]) {
                printf("%d ", set1[i]);
            }
        }
    }

    printf("}\n");
}

void print_union(int set1[], int set2[], int len) 
{
    int union[len];
    printf("{ ");
    for (int i = 0; i < len; i++) {
        printf("%d ", set1[i]);
    }

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if()
        }
    }


    printf("}\n");
}


#define SIZE 5

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

    print_intersection(arr1, arr2, SIZE);
    print_union(arr1, arr2, SIZE);

}