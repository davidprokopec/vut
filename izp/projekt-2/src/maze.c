#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int rows;
    int cols;
    unsigned char *cells;
} Map;

typedef struct {
    int row;
    int column;
} Move;

typedef struct {
    bool help;
    bool test;
    bool rpath;
    bool lpath;
    bool shortest;
    int startRow;
    int startCol;
    char *filePath;
} Config;

// LEFT = 001, RIGHT = 010, UP_DOWN = 100
enum Directions { LEFT = 1, RIGHT, UP_DOWN = 4 };

enum Status { ERROR, OK };

// Helper functions
void print_help();
bool parse_arguments(Config *config, int argc, char **argv);
// Map functions
void map_dtor(Map *map);
bool load_map(Map *map, char *filePath);
// Border functions
bool is_border(Map *map, int row, int column, int border);
int start_border(Map *map, int row, int column);
// Path functions
bool solve(Map *map, int row, int column, int leftRight);

int main(int argc, char *argv[]) {
    Config config = {
        .help = false,
        .test = false,
        .rpath = false,
        .lpath = false,
        .shortest = false,
        .startRow = 0,
        .startCol = 0,
        .filePath = NULL,
    };
    if (!parse_arguments(&config, argc, argv)) {
        printf("Use --help for more information\n");
        return ERROR;
    }

    if (config.help) {
        print_help();
        return OK;
    }

    Map map;
    bool mapLoaded = load_map(&map, config.filePath);

    if (!mapLoaded) {
        map_dtor(&map);
        if (config.test) {
            printf("Invalid\n");
            return ERROR;
        }
        printf("Map is invalid\n");
        return ERROR;
    }

    if (config.test) {
        printf("Valid\n");
    } else if (config.rpath) {
        solve(&map, config.startRow, config.startCol, RIGHT);
    } else if (config.lpath) {
        solve(&map, config.startRow, config.startCol, LEFT);
    }

    map_dtor(&map);
    return OK;
}

void print_help() {
    printf("Help\n");
    printf("-------------------------------------------\n");
    printf("Usage: maze [OPTION] [mazeFile]\n");
    printf("Options:\n");
    printf("  --help\t\t\t\t Print this help and exit\n");
    printf("  --test [mazeFile]\t\t\t Test the maze for validity\n");
    printf("  --rpath R C [mazeFile]\t\t Find a right-hand path from specified R (row) and C (column)\n");
    printf("  --lpath R C [mazeFile]\t\t Find a left-hand path from specified R (row) and C (column)\n");
    printf("  --shortest R C [mazeFile]\t\t Find the shortest path from specified R (row) and C (column)\n");
}

bool parse_arguments(Config *config, int argc, char **argv) {
    if (argc < 2) {
        printf("Invalid arguments\n");
        return false;
    }
    if (strcmp(argv[1], "--help") == 0) {
        config->help = true;
        return true;
    }
    if (strcmp(argv[1], "--test") == 0) {
        if (argc < 3) {
            printf("Please specify path to map file.\n");
            return false;
        }
        config->test = true;
        config->filePath = argv[2];
        return true;
    }

    const char *pathErrorMessage = "Please specify row, column and path to map file.\n";

    if (strcmp(argv[1], "--rpath") == 0) {
        config->rpath = true;
    } else if (strcmp(argv[1], "--lpath") == 0) {
        config->lpath = true;
    } else if (strcmp(argv[1], "--shortest") == 0) {
        config->shortest = true;
    }

    if (argc < 5) {
        printf("%s", pathErrorMessage);
        return false;
    } else {
        config->startRow = atoi(argv[2]);
        config->startCol = atoi(argv[3]);

        config->filePath = argv[4];
        return true;
    }
    return false;
}

// load map from file into Map struct
// if invalid value, return false
bool load_map(Map *map, char *filePath) {
    FILE *file = fopen(filePath, "r");

    if (file == NULL) {
        printf("filename: %s\n", filePath);
        return false;
    }

    // Read number of rows and columns
    if (fscanf(file, "%d %d", &(map->rows), &(map->cols)) != 2) {
        printf("Error while reading rows and columns\n");
        fclose(file);
        return false;
    }

    // Allocate memory for cells
    map->cells = (unsigned char *)malloc(map->rows * map->cols * sizeof(unsigned char));
    if (map->cells == NULL) {
        printf("Error while allocating memory for cells\n");
        fclose(file);
        return false;
    }

    // Read cell values with additional checks
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            unsigned char cellValue;
            if (fscanf(file, "%hhu", &cellValue) != 1 || cellValue > 7) {
                fclose(file);
                return false;
            }
            map->cells[i * map->cols + j] = (unsigned char)cellValue;
        }
    }

    fclose(file);
    return true;
}

// free Map struct
void map_dtor(Map *map) {
    if (map->cells != NULL) {
        free(map->cells);
    }
}

// check if is border is 
bool is_border(Map *map, int row, int column, int border) {
    // comparing each bit of border with cell value
    // cell - 5, border - 1
    // 0101 & 0001 = 0001 -> true
    return (map->cells[map->cols * (row - 1) + column - 1] & border);
}

// return first border from which we can start
int start_border(Map *map, int row, int column) {
    bool leftBorder = is_border(map, row, column, LEFT);
    bool rightBorder = is_border(map, row, column, RIGHT);
    bool upDownBorder = is_border(map, row, column, UP_DOWN);
    bool isColumnOdd = column % 2 == 0;
    bool isNumberOfRowsOdd = map->rows % 2 == 0;
    bool isNumberOfColumnsOdd = map->cols % 2 == 0;

    if (row == 1) {
        if (column == 1) {
            if (!is_border(map, row, column, LEFT)) {
                return RIGHT;
            }
            if (!is_border(map, row, column, UP_DOWN)) {
                return UP_DOWN;
            }
        } else if (column == map->cols) {
            if (!isNumberOfColumnsOdd && !upDownBorder) {
                return UP_DOWN;
            }
            if (!rightBorder) {
                return LEFT;
            }
        } else if (!isColumnOdd && !upDownBorder) {
            return UP_DOWN;
        }
    } else if (row == map->rows) {
        if (!isNumberOfRowsOdd) {
            if (column == 1 && !leftBorder) {
                return RIGHT;
            }
            if (column == map->cols) {
                if (isNumberOfColumnsOdd && !rightBorder) {
                    return LEFT;
                }
                if (!upDownBorder) {
                    return UP_DOWN;
                }
            } else if (!isColumnOdd) {
                return -1; // ISP
            } else if (!upDownBorder) {
                return UP_DOWN;
            }
        } else {
            if (column == 1 && !leftBorder) {
                return RIGHT;
            }
            if (column == map->cols) {
                if (!isNumberOfColumnsOdd && !rightBorder) {
                    return LEFT;
                }
                if (!upDownBorder) {
                    return UP_DOWN;
                }
            } else if (isColumnOdd && !upDownBorder) {
                return UP_DOWN;
            }
        }
    } else if (row < map->rows) {
        if (column == 1 && !leftBorder) {
            return RIGHT;
        }
        if (column > 1 && column <= map->cols && !rightBorder) {
            return LEFT;
        }
    }
    return -1;
}

// solve the maze
bool solve(Map *map, int row, int column, int leftRight) {

    Move possibleMoves[4] = {
        {-1, 0}, // UP
        {0, -1}, // LEFT
        {0, 1},  // RIGHT
        {1, 0}   // DOWN
    };

    int currRow = row;
    int currColumn = column;
    int nextMoveDirection = -1;
    int currDirection = start_border(map, currRow, currColumn);

    if (currDirection == -1) {
        return false;
    }

    bool isInMaze = true;
    while (isInMaze) {
        printf("%d,%d\n", currRow, currColumn);

        bool hasTopSide = (currRow + currColumn) % 2 == 0;
        bool leftBorder = is_border(map, currRow, currColumn, LEFT);
        bool rightBorder = is_border(map, currRow, currColumn, RIGHT);
        bool upDownBorder = is_border(map, currRow, currColumn, UP_DOWN);

        if (!rightBorder && !leftBorder && !upDownBorder) {
            if ((leftRight == LEFT && !hasTopSide) || (leftRight == RIGHT && hasTopSide)) {
                if (currDirection == LEFT) {
                    currDirection = UP_DOWN;
                } else if (currDirection == UP_DOWN) {
                    currDirection = LEFT;
                }
            } else {
                if (currDirection == RIGHT) {
                    currDirection = UP_DOWN;
                } else if (currDirection == UP_DOWN) {
                    currDirection = RIGHT;
                }
            }
        } else if (!rightBorder && leftBorder && !upDownBorder) {
            if (currDirection == LEFT) {
                currDirection = UP_DOWN;
            } else {
                currDirection = RIGHT;
            }
        } else if (rightBorder && !leftBorder && !upDownBorder) {
            if (currDirection == RIGHT) {
                currDirection = UP_DOWN;
            } else {
                currDirection = LEFT;
            }
        } else if (!rightBorder && leftBorder && upDownBorder) {
            currDirection = RIGHT;
        } else if (rightBorder && !leftBorder && upDownBorder) {
            currDirection = LEFT;
        }

        if (currDirection == UP_DOWN) {
            if (!hasTopSide) {
                // DOLU
                nextMoveDirection = 3;
            } else {
                // NAHORU
                nextMoveDirection = 0;
            }
        } else {
            nextMoveDirection = currDirection;
        }

        // nextMoveDirection - 0 = UP, 1 = LEFT, 2 = RIGHT, 3 = DOWN
        currRow = currRow + possibleMoves[nextMoveDirection].row;
        currColumn = currColumn + possibleMoves[nextMoveDirection].column;

        isInMaze = currRow > 0 && currRow <= map->rows && currColumn > 0 && currColumn <= map->cols;
    }
    return true;
}

