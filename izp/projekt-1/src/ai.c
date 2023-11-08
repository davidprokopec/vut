
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void string_to_lower(char *str) {
    while (*str != '\0') {
        if (*str >= 'A' && *str <= 'Z') {
            *str += 0x20;
        }
        str++;
    }
}

void string_to_upper(char *str) {
    while (*str != '\0') {
        if (*str >= 'a' && *str <= 'z') {
            *str -= 0x20;
        }
        str++;
    }
}

char char_to_upper(char x) {
    if (x >= 'a' && x <= 'z') {
        x -= 0x20;
    }
    return x;
}

void print_possible_chars(char *possibleChars, int possibleCharsCount) {
    printf("Enable: ");
    for (int i = 0; i < possibleCharsCount; i++) {
        printf("%c", char_to_upper(possibleChars[i]));
    }
    printf("\n");
}

void find_and_print_match(char *input, char *buffer) {
    if (strcmp(input, buffer) == 0) {
        printf("Found: %s", string_to_upper(buffer));
        exit(0);
    }
}

void find_possible_results(char *input, char *buffer, char possibleResults[][BUFFERSIZE], int *possibleResultsCount) {
    size_t bufferLen = strlen(buffer);
    size_t inputLen = strlen(input);

    if (bufferLen < inputLen) {
        return; // Skip because buffer is shorter than input
    }

    for (int i = 0; i < (int)bufferLen; i++) {
        if (buffer[i] == '\n') {
            // Found 1:1 match, can end here
            printf("Found: %s", string_to_upper(buffer));
            exit(0);
        }

        if (buffer[i] != input[i]) {
            if (i == 0 && inputLen != 0) {
                // First character does not match, can skip
                return;
            }

            if (i == (int)inputLen || inputLen == 0) {
                // Add buffer to possibleResults
                strcpy(possibleResults[(*possibleResultsCount)++], buffer);
            }
            return;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Enter input, example: ./keyfilter br < adresy.txt \n");
        return 1;
    }

    char input[100];
    strcpy(input, argv[1]);
    string_to_lower(input);

    char buffer[BUFFERSIZE];

    char possibleResults[100][BUFFERSIZE];
    int possibleResultsCount = 0;

    while (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
        string_to_lower(buffer);

        find_possible_results(input, buffer, possibleResults, &possibleResultsCount);
    }

    if (possibleResultsCount == 0) {
        printf("Not found\n");
        return 0;
    }

    if (possibleResultsCount == 1) {
        printf("Found: %s", string_to_upper(possibleResults[0]));
        return 0;
    }

    // Multiple possible results, ask for the next character
    char possibleChars[52];
    int possibleCharsCount = 0;

    for (int i = 0; i < possibleResultsCount; i++) {
        char nextChar = possibleResults[i][strlen(input)];
        bool found = false;
        for (int j = 0; j < possibleCharsCount; j++) {
            if (possibleChars[j] == nextChar) {
                found = true;
                break;
            }
        }
        if (!found) {
            possibleChars[possibleCharsCount++] = nextChar;
        }
    }

    // Sort possible chars by ASCII
    for (int i = 0; i < possibleCharsCount; i++) {
        for (int j = i + 1; j < possibleCharsCount; j++) {
            if (possibleChars[i] > possibleChars[j]) {
                char tmp = possibleChars[i];
                possibleChars[i] = possibleChars[j];
                possibleChars[j] = tmp;
            }
        }
    }

    print_possible_chars(possibleChars, possibleCharsCount);

    return 0;
}
