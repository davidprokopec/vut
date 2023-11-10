#include <stdio.h>

void inc(int* a) {
    (*a)++;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10;
    int y = 20;

    inc(&x);

    printf("%d %d\n", x, y);

    swap(&x, &y);

    printf("%d %d\n", x, y);
}
