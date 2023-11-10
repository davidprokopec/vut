#include <stdio.h>

int main() {
    // data type of input stream
    FILE *input;

    input = fopen("nums.txt", "r");

    int sum = 0;
    if (input != NULL) {
        int num;
        while(fscanf(input, "%d", &num) != EOF) {
            sum += num;
        }

    }
    // CLOSE FILE!!!
    fclose(input);

    printf("Sum of all numbers is %d \n", sum);
}