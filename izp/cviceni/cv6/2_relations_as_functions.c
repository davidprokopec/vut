#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SET_SIZE 10

typedef struct {
    int items[MAX_SET_SIZE];
    int cardinality;
} set_t;

typedef struct {
    int x;
    int y;
} pair_t;

void print_rel(pair_t rel[5]) {
    printf("{");
    for (int i = 0; i < 5; i++) {
        printf("(%d, %d)", rel[i].x, rel[i].y);
        if (i != 4) {
            printf(", ");
        }
    }
    printf("}\n");
}

bool rel_is_func(pair_t rel[5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (rel[i].x == rel[j].x) {
                return false;
            }
        }
    }
    return true;
}

/* 
příklad definice množiny
set_t ctyri_prvky = {{1,2,3,4}, 4};
- Naprogramujte funkci, která ověří, zda daná relace odpovídá
funkci.
- Rozšiřte funkci tak, aby našla minimální a maximální bod funkce:
*/
bool rel_minmax(pair_t rel[5], pair_t* min, pair_t* max) {
    if (!rel_is_func(rel)) {
        return false;
    }

    *min = rel[0];
    *max = rel[0];

    for (int i = 1; i < 5; i++) {
        if (rel[i].y < min->y) {
            *min = rel[i];
        }
        if (rel[i].y > max->y) {
            *max = rel[i];
        }
    }

    return true;
}

/*
Implementujte funkci, která provede inverzi bodu (zamění hodnoty ve dvojici):
*/
void pair_invert(pair_t* point) {
    int tmp = point->x;
    point->x = point->y;
    point->y = tmp;
}

int main() {
    pair_t rel[5] = {{1, 2}, {2, 3}, {3, 5}, {4, 5}, {6, 1}};
    print_rel(rel);

    pair_t min, max;
    if (rel_minmax(rel, &min, &max)) {
        printf("Min: (%d, %d)\n", min.x, min.y);
        printf("Max: (%d, %d)\n", max.x, max.y);
    } else {
        printf("Not a function\n");
    }

    pair_invert(&min);
    printf("Swapped min: (%d, %d)\n", min.x, min.y);


    return 0;
}
