#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *items;
    int size;
} vector_t;

int *resize(int *arr, unsigned int new_size) {
    int *new_arr = realloc(arr, new_size * sizeof(int));
    if (new_arr == NULL) {
        free(arr);
        return NULL;
    }
    return new_arr;
}

vector_t *vector_ctor() {
    vector_t *vec = malloc(sizeof(vector_t));
    if (vec != NULL) {
        vec->size = 0;
        vec->items = NULL;
    }
    return vec;
}

void vector_dtor(vector_t *vector) {
    if (vector == NULL) {
        return;
    }
    if (vector->items != NULL) {
        free(vector->items);
    }
    free(vector);
}

int vector_add(vector_t *vec, int value) {
    vec->items = resize(vec->items, vec->size + 1);
    if (vec->items == NULL) {
        return 0;
    }
    vec->items[vec->size] = value;
    vec->size++;
    return 1;
}

int main() {
    vector_t *vec = vector_ctor();
    for (int i = 0; i < 3; i++) {
        int x;
        scanf("%d", &x);
        if (!vector_add(vec, x)) {
            return 1;
        }
    }
    vector_dtor(vec);
}
