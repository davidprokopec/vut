#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initial string content
const char *str_init = "Hello World!";

// Find first substring occurrence in a string and return its starting position.
// Return -1 if the string does not contain substring.
int find_substr(char *str, char *substr) {
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

// Replace same-length substrings in a string.
void replace_same_length(char *str, char *substr, char *new_substr) {
    int index = find_substr(str, substr);
    if (index == -1) {
        return;
    }
    for (int i = index; str[i] != '\0'; i++) {
        str[i] = new_substr[i - index];
    }
}

// Replace substring in a string with any new substring.
// Returns new string with replaced substring or NULL in case of any error.
char *replace(char *str, char *substr, char *new_substr) {
    int position = find_substr(str, substr);
    if (position == -1) {
        return NULL;
    }

    // get the necessary lengths
    int str_len = strlen(str);
    int substr_len = strlen(substr);
    int new_substr_len = strlen(new_substr);
    int len_diff = new_substr_len - substr_len;

    if (len_diff > 0) {
        int i;
        for (i = position + substr_len; i < str_len; i++) {
            str[i - len_diff] = str[i];
        }
        str[i - len_diff] = '\0';

        char *new_str = (char *)realloc(str, str_len - len_diff + 1);
        if (new_str == NULL) {
            return NULL;
        }
        str = new_str;
    }

    if (len_diff < 0) {
        // the new string will be longer, move the rest of the string to the right

        // resize before shifting-right the suffix
        char *new_str = (char *)realloc(str, str_len - len_diff + 1);
        if (new_str == NULL) {
            return NULL;
        }
        str = new_str;

        // shift-right the suffix
        for (int i = str_len; i >= position + substr_len; i--) {
            str[i + len_diff] = str[i];
        }
    }
}

int main() {
    // Allocate new string.
    char *str = (char *)malloc(strlen(str_init) + 1);
    if (str == NULL) {
        return 1;
    }
    // Set the initial string by copying it.
    strcpy(str, str_init);
    // Replace substring with a new same-length substring.
    replace_same_length(str, "World!", "worlds");
    printf("%s\n", str);
    // Replace substring with a new shorter substring.
    str = replace(str, "worlds", "IZP!");
    if (str == NULL) {
        return 1;
    }
    printf("%s\n", str);
    // Replace substring with a new longer substring.
    str = replace(str, "IZP!", "World!");
    if (str == NULL) {
        return 1;
    }
    printf("%s\n", str);
    // Cleanup
    free(str);
    printf("Successully replaced all substrings!\n");
    // Allocate and initialize a new string.
    free(str);
    str = (char *)malloc(strlen(str_init) + 1);
    if (str == NULL) {
        return 1;
    }
    strcpy(str, str_init);
    // Try using replace with substring that is not in the string.
    str = replace(str, "worlds", "World!");
    if (str == NULL) {
        free(str);
        return 1;
    }
    printf("%s\n", str);
    return 0;
}
