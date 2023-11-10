#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* usage = "syntax: %s [-x|-y] [-n COUNT] -s STR\n"
                    "-x and -y are optional and mutually exclusive\n"
                    "-s STR - mandatory, STR is a string\n"
                    "-n COUNT - optional, COUNT is non-negative integer (default: 10)\n";

typedef struct {
    bool xflag;
    bool yflag;
    int nvalue;
    char* svalue;
} config_t;

/* GLOBAL CONFIGURATION */
config_t config = {.xflag = false, .yflag = false, .nvalue = 10, .svalue = NULL};

/**
* returns 1 if success
*/
bool parse_args(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp("-x", argv[i]) == 0) {
            if (config.xflag || config.yflag) {
                return false;
            }
            config.xflag = true;
        } else if (strcmp("-y", argv[i]) == 0) {
            if (config.xflag || config.yflag) {
                return false;
            }
            config.yflag = true;
        } else if (strcmp("-n", argv[i]) == 0) {
            if (argv[i + 1] == NULL) {
                return false;
            }
            config.nvalue = atoi(argv[i + 1]);
            i++;
        } else if (strcmp("-s", argv[i]) == 0) {
            if (argv[i + 1] == NULL) {
                return false;
            }
            config.svalue = argv[i + 1];
            i++;
        } else {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (parse_args(argc, argv) != 1) {
        fprintf(stderr, usage, argv[0]);
        return 1;
    }

    if (config.xflag) {
        printf("You want to apply -x\n");
    }
    if (config.yflag) {
        printf("You want to apply -y\n");
    }
    printf("COUNT is %u\n", config.nvalue);
    printf("-s is %s\n", config.svalue);
    return 0;
}
