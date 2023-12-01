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
    int x;
    int y;
} Change;

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

enum Directions { LEFT = 1, RIGHT, UP_DOWN = 4 };

// Helper functions
void print_help();
bool parse_arguments(int argc, char **argv);
// Map functions
void map_dtor(Map *map);
bool load_map(Map *map);
bool test_map(Map *map);
// Cell functions
int get_cell_index(Map *map, int row, int column);
// Border functions
bool is_border(Map *map, int row, int column, int border);
int start_border(Map *map, int row, int column);
// Path functions
bool solve(Map *map, int row, int column, int leftRight);

int main(int argc, char *argv[]) {
  // TODO - test upravit aby kontroloval ze sedi pocet radku a sloupcu podle prvniho radku
  // TODO - upravit solve
    if (!parse_arguments(argc, argv)) {
        printf("Use --help for more information\n");
        return 0;
    }

    if (config.help) {
        print_help();
        return 0;
    }

    Map map;
    bool mapLoaded = load_map(&map);

    if (!mapLoaded) {
        printf("Error while loading the map\n");
        return 0;
    }

    if (config.test) {
        if (test_map(&map)) {
            printf("Valid\n");
        } else {
            printf("Invalid\n");
        }
        map_dtor(&map);
        return 0;
    }

    if (config.rpath) {
        bool found = solve(&map, config.startRow, config.startCol, RIGHT);
        if (found) {
        } else {
        }
        map_dtor(&map);
        return 0;
    }

    if (config.lpath) {
        bool found = solve(&map, config.startRow, config.startCol, LEFT);
        if (!found) {
        } else {
        }
        map_dtor(&map);
        return 0;
    }

    map_dtor(&map);
    return 0;
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

bool parse_arguments(int argc, char **argv) {
    if (argc < 2) {
        printf("Invalid arguments\n");
        return false;
    }
    if (strcmp(argv[1], "--help") == 0) {
        config.help = true;
        return true;
    }
    if (strcmp(argv[1], "--test") == 0) {
        if (argc < 3) {
            printf("Please specify path to map file.\n");
            return false;
        }
        config.test = true;
        config.filePath = argv[2];
        return true;
    }

    const char *pathErrorMessage = "Please specify row, column and path to map file.\n";

    if (strcmp(argv[1], "--rpath") == 0) {
        config.rpath = true;
    } else if (strcmp(argv[1], "--lpath") == 0) {
        config.lpath = true;
    } else if (strcmp(argv[1], "--shortest") == 0) {
        config.shortest = true;
    }

    if (argc < 5) {
        printf("%s", pathErrorMessage);
        return false;
    } else {
        config.startRow = atoi(argv[2]);
        config.startCol = atoi(argv[3]);

        config.filePath = argv[4];
        return true;
    }
    return false;
}

bool load_map(Map *map) {
    FILE *file = fopen(config.filePath, "r");

    if (file == NULL) {
        printf("File not found\n");
        return false;
    }

    char line[100];
    int lineCount = 0;
    int index = 0;
    const char delimiters[] = " \t\r\n\v\f";

    while (fgets(line, sizeof(line), file)) {
        if (lineCount == 0) {
            // get size of map
            char *token = strtok(line, delimiters);
            map->rows = atoi(token);
            token = strtok(NULL, delimiters);
            map->cols = atoi(token);
            map->cells = malloc(map->rows * map->cols * sizeof(unsigned char));
            if (map->cells == NULL) {
                return false;
            }
        } else {
            // get cells
            char *token = strtok(line, delimiters);
            while (token != NULL) {
                map->cells[index] = (unsigned char)atoi(token);
                token = strtok(NULL, delimiters);
                index++;
            }
        }
        lineCount++;
    }

    fclose(file);

    return true;
}

void map_dtor(Map *map) {
    if (map->cells != NULL) {
        free(map->cells);
    }
}

bool test_map(Map *map) {
    for (int i = 0; i < map->rows * map->cols; i++) {
        if (map->cells[i] > 7) {
            return false;
        }
    }
    return true;
}

int get_cell_index(Map *map, int row, int column) {
    if (row > map->rows || column > map->cols) {
        return -1;
    }
    return (row - 1) * map->cols + column - 1;
}

bool is_border(Map *map, int row, int column, int border) {
    return (map->cells[map->cols * (row - 1) + column - 1] & border);
}

int start_border(Map *map, int row, int column) {
    if (row == 1) {
        if (column == 1) {
            if (!is_border(map, row, column, LEFT)) {
                return RIGHT;
            }
            if (!is_border(map, row, column, UP_DOWN)) {
                return UP_DOWN;
            }
        } else if (column == map->cols) {
            if (map->cols & 1 && !is_border(map, row, column, UP_DOWN)) {
                return UP_DOWN;
            }
            if (!is_border(map, row, column, RIGHT)) {
                return LEFT;
            }
        } else if (column & 1 && !is_border(map, row, column, UP_DOWN)) {
            return UP_DOWN;
        }
    } else if (row == map->rows) {
        if (map->rows & 1) {
            if (column == 1 && !is_border(map, row, column, LEFT)) {
                return RIGHT;
            }
            if (column == map->cols) {
                if (!(map->cols & 1) && !is_border(map, row, column, RIGHT)) {
                    return LEFT;
                }
                if (!is_border(map, row, column, UP_DOWN)) {
                    return UP_DOWN;
                }
            } else if (column & 1) {
                return -1; // ISP
            } else if (!is_border(map, row, column, UP_DOWN)) {
                return UP_DOWN;
            }
        } else {
            if (column == 1 && !is_border(map, row, column, LEFT)) {
                return RIGHT;
            }
            if (column == map->cols) {
                if (map->cols & 1 && !is_border(map, row, column, RIGHT)) {
                    return LEFT;
                }
                if (!is_border(map, row, column, UP_DOWN)) {
                    return UP_DOWN;
                }
            } else if (!(column & 1) && !is_border(map, row, column, UP_DOWN)) {
                return UP_DOWN;
            }
        }
    } else if (row < map->rows) {
        if (column == 1 && !is_border(map, row, column, LEFT)) {
            return RIGHT;
        }
        if (column > 1 && column <= map->cols && !is_border(map, row, column, RIGHT)) {
            return LEFT;
        }
    }
    return -1;
}

// Function to solve the map
bool solve(Map *map, int row, int column, int leftRight) {

    // Changes in x and y for different directions
    Change d[] = {
        {-1, 0}, // UP
        {0, -1}, // LEFT
        {0, 1},  // RIGHT
        {1, 0}   // DOWN
    };

    int horizontalDirection = -1; // Helper variable for direction
    int currRow = row;
    int currColumn = column;
    int currDirection = start_border(map, currRow, currColumn);

    if (currDirection == -1) {
        return false;
    }

    bool isInMaze = true;
    while (isInMaze) {
        printf("%d %d \n", currRow, currColumn);
        if (!is_border(map, currRow, currColumn, RIGHT) && !is_border(map, currRow, currColumn, LEFT)
            && !is_border(map, currRow, currColumn, UP_DOWN)) {
            if ((leftRight == LEFT && ((currRow ^ currColumn) & 1))
                || (leftRight == RIGHT && (!((currRow ^ currColumn) & 1)))) {
                if (currDirection == LEFT) {
                    currDirection = UP_DOWN; //druhy pripad
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
        } else if (!is_border(map, currRow, currColumn, RIGHT) && is_border(map, currRow, currColumn, LEFT)
                   && !is_border(map, currRow, currColumn, UP_DOWN)) {
            if (currDirection == LEFT) {
                currDirection = UP_DOWN;
            } else {
                currDirection = RIGHT;
            }
        } else if (is_border(map, currRow, currColumn, RIGHT) && !is_border(map, currRow, currColumn, LEFT)
                   && !is_border(map, currRow, currColumn, UP_DOWN)) {
            if (currDirection == RIGHT) {
                currDirection = UP_DOWN;
            } else {
                currDirection = LEFT;
            }
        } else if (!is_border(map, currRow, currColumn, RIGHT) && is_border(map, currRow, currColumn, LEFT)
                   && is_border(map, currRow, currColumn, UP_DOWN)) {
            currDirection = RIGHT;
        } else if (is_border(map, currRow, currColumn, RIGHT) && !is_border(map, currRow, currColumn, LEFT)
                   && is_border(map, currRow, currColumn, UP_DOWN)) {
            currDirection = LEFT;
        }

        if (currDirection == UP_DOWN) {
            if ((currRow ^ currColumn) & 1) { /*hore*/
                horizontalDirection = 3;
            } else {
                horizontalDirection = 0;
            }
        } else {
            horizontalDirection = currDirection;
        }
        currRow = currRow + d[horizontalDirection].x;
        currColumn = currColumn + d[horizontalDirection].y;

        isInMaze = currRow > 0 && currRow <= map->rows && currColumn > 0 && currColumn <= map->cols;
    }
    return true;
}
