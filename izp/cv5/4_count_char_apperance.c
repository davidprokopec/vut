#include <stdio.h>

int main() {
    // data type of input stream
    FILE *input;

    input = fopen("lorem.txt", "r");

    char x = 'n';

    int count = 0;
    if (input != NULL) {
        char ch;
        while(ch != EOF) {
            ch = fgetc(input);
            if(ch == x) {
                count++;
            }
        }

    }

    fclose(input);

    printf("character %c has appeared in the text %d times \n", x, count);
    return 0;
}