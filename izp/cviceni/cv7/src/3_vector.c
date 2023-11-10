#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int size;
} vector_t;

bool vector_ctor(vector_t *v, unsigned int size) {
    v->data = malloc(size * sizeof(int));
    if (v->data == NULL) {
        return false;
    }
    v->size = size;
    return true;
}

void vector_init(vector_t *v) {
    for (int i = 0; i < v->size; i++) {
        v->data[i] = i + 1;
    }
}

void vector_dtor(vector_t *v) {
    if (v->data != NULL) {
        free(v->data);
        v->data = NULL;
        v->size = 0;
    }
}

void vector_multiply(vector_t *v, int multiplier) {
    for (int i = 0; i < v->size; i++) {
        v->data[i] *= multiplier;
    }
}

bool vector_add(vector_t *v1, vector_t *v2) {
  if(v1->size != v2->size){
    return false;
  }
  for(int i = 0; i < v1->size; i++){
    v1->data[i] += v2->data[i];
  }
  return true;
}

void vector_print(vector_t* v) {
    printf("[");
    for (int i = 0; i < v->size; i++) {
        printf("%d", v->data[i]);
        if (i != v->size - 1) {
            printf(",");
        }
    }
    printf("]\n");
}

int main() {
    vector_t v;
    if (!vector_ctor(&v, 10)) {
        printf("Alloc failed\n");
        return 1;
    }
    vector_init(&v);
    vector_print(&v);

    vector_multiply(&v,5);
    vector_print(&v);

    vector_t v2;
    if(!vector_ctor(&v2,10)){
        printf("Alloc failed");
        return 1;
    }
    vector_init(&v2);

    if(!vector_add(&v,&v2)){
        printf("Different sizes\n");
        return 1;
    }
    vector_print(&v);

    vector_dtor(&v);
    vector_dtor(&v2);
    return 0;
}
