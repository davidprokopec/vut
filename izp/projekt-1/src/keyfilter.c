#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BUFFERSIZE 101

// uppercase a string
void string_to_upper(char* str) {
    while (*str != '\0') {
        if (*str >= 'a' && *str <= 'z') {
            *str -= 0x20;
        }
        str++;
    }
}

// find all possible results and store them in possibleResults
void find_possible_results(char* buffer, char* input, char possibleResults[][BUFFERSIZE], int* possibleResultsCount) {
    size_t bufferLen = strlen(buffer);
    size_t inputLen = strlen(input);

    if (bufferLen < inputLen) {
        // can skip because buffer is shorter than input
        // thus no match and cannot even give next character
        return;
    }

    for (int i = 0; i < (int)bufferLen; i++) {
        if (buffer[i] == '\n') {
            strcpy(possibleResults[*possibleResultsCount], buffer);
            (*possibleResultsCount)++;
            return;
        }

        if (buffer[i] != input[i]) {
            if (i == (int)inputLen || inputLen == 0) {
                // add buffer to possibleResults
                strcpy(possibleResults[*possibleResultsCount], buffer);
                (*possibleResultsCount)++;
            }
            break;
        }
    }
}

// find all possible characters and store them in possibleChars
void find_possible_chars(char possibleChars[], int* possibleCharsCount, char possibleResults[][BUFFERSIZE],
                         int possibleResultsCount, const char* input) {
    for (int i = 0; i < possibleResultsCount; i++) {
        char nextChar = possibleResults[i][strlen(input)];
        bool found = false;
        for (int j = 0; j < *possibleCharsCount; j++) {
            if (possibleChars[j] == nextChar) {
                found = true;
                break;
            }
        }
        if (!found) {
            possibleChars[*possibleCharsCount] = nextChar;
            (*possibleCharsCount)++;
        }
    }
}

// sort a string by ASCII table
void sort_by_ASCII(char* arr) {
    int n = strlen(arr);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                char tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

void print_possible_chars(char possibleChars[], int possibleCharsCount) {
    printf("Enable: ");
    for (int i = 0; i < possibleCharsCount; i++) {
        printf("%c", possibleChars[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Enter input, example: ./keyfilter br\n");
        return 1;
    }

    char input[BUFFERSIZE];
    strcpy(input, argv[1]);
    string_to_upper(input);

    char buffer[BUFFERSIZE];

    char possibleResults[BUFFERSIZE][BUFFERSIZE] = {};
    int possibleResultsCount = 0;

    // stream input from stdin
    while (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
        string_to_upper(buffer);
        find_possible_results(buffer, input, possibleResults, &possibleResultsCount);
    }

    // 0 possible results means no possible adress found
    if (possibleResultsCount == 0) {
        printf("Not found\n");
        return 0;
    }

    // 1 possible result means exact adress found
    if (possibleResultsCount == 1) {
        printf("Found: %s", possibleResults[0]);
        return 0;
    }

    // multiple possible results, ask for next character
    // size of 128 because ASCII table has 128 characters
    char possibleChars[128];
    int possibleCharsCount = 0;

    find_possible_chars(possibleChars, &possibleCharsCount, possibleResults, possibleResultsCount, input);

    // sort possible chars by ascii table
    sort_by_ASCII(possibleChars);

    // print possible chars
    print_possible_chars(possibleChars, possibleCharsCount);

    return 0;
}
