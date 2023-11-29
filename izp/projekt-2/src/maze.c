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

enum BorderTypes { RIGHT, LEFT, TOP_BOTTOM };

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
                map->cells[index] = token[0];
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

bool is_map_valid(Map *map) {
    if (map->rows * map->cols != (int)strlen((char *)map->cells)) {
        return false;
    }

    for (int i = 0; i < map->rows * map->cols; i++) {
        if (map->cells[i] < '0' || map->cells[i] > '7') {
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

int start_border(Map *map, int row, int column, int leftRight); // TODO

bool is_border(Map *map, int row, int column, enum BorderTypes border) {
    int cellValue = map->cells[get_cell_index(map, row, column)];
    switch (border) {
        case RIGHT: return cellValue & 1;
        case LEFT: return (cellValue >> 1) & 1;
        case TOP_BOTTOM: return (cellValue >> 2) & 1;
        default: return false;
    }
}

bool find_rpath(Map *map) {
    int startCellIndex = get_cell_index(map, config.startRow, config.startCol);
    if (startCellIndex == -1) {
        printf("Invalid start cell\n");
        return false;
    }
    printf("Start cell index: %d\n", startCellIndex);

    return true;
}

int main(int argc, char *argv[]) {
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
        if (is_map_valid(&map)) {
            printf("Valid\n");
        } else {
            printf("Invalid\n");
        }
        map_dtor(&map);
        return 0;
    }

    if (config.rpath) {
        printf("Find right hand path\n");
        bool found = find_rpath(&map);
        if (!found) {
            printf("No path found\n");
        }
        map_dtor(&map);
        return 0;
    }

    map_dtor(&map);
    return 0;
}
