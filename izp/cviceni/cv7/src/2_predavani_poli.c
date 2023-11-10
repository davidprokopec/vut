#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void print_arr(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i != size - 1) {
            printf(",");
        }
    }
    printf("]\n");
}

void arr_multiply(int* arr, int size, int multiplier) {
    for (int i = 0; i < size; i++) {
        arr[i] *= multiplier;
    }
}

void to_upper(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        }
    }
}

int find_substr(char* str, char* substr) {
    int index = -1;
    for (int i = 0; str[i] != '\0'; i++) {
        bool found = true;
        for (int j = 0; substr[j] != '\0'; j++) {
            if (str[i + j] != substr[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            index = i;
            break;
        }
    }
    return index;
}

void arr_insert(int* arr, int size, int index, int value) {
    for (int i = size - 1; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = value;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    print_arr(arr, 5);
    arr_multiply(arr, 5, 2);
    print_arr(arr, 5);

    char msg[] = "My interesting message";
    printf("%s\n", msg);
    to_upper(msg);
    printf("%s\n", msg);

    char* str = "My long message";
    printf("%d\n", find_substr(str, "My"));
    printf("%d\n", find_substr(str, "y l"));
    printf("%d\n", find_substr(str, "long"));
    printf("%d\n", find_substr(str, "sag"));
    printf("%d\n", find_substr(str, "saga"));
    printf("%d\n", find_substr(str, "sage"));
    printf("%d\n", find_substr(str, "ge"));
    printf("%d\n", find_substr(str, "ger"));

    print_arr(arr, 5);
    arr_insert(arr, 5, 0, 10);
    print_arr(arr, 5);
    arr_insert(arr, 5, 4, 10);
    print_arr(arr, 5);
    arr_insert(arr, 5, 3, 42);
    print_arr(arr, 5);
}
