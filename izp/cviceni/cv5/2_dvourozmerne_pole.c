#include <stdio.h>

#define MX_ROWS 3
#define MX_COLS 3

void find_index(int arr2d[MX_ROWS][MX_COLS], int x) {
    for (int row = 0; row < MX_ROWS; row++) {
        for (int col = 0; col < MX_COLS; col++) {
            if(arr2d[row][col] == x) {
                printf("Index for number %d, is row[%d] col[%d] \n", x, row, col);
                return;
            }
        }
    }
}

int main() {
    int arr2d[MX_ROWS][MX_COLS];

    for (int row = 0; row < MX_ROWS; row++) {
        for (int col = 0; col < MX_COLS; col++) {
            arr2d[row][col] = 0;
        }
    }

    int x = 6;

    arr2d[2][2] = x;

    find_index(arr2d, x);
}