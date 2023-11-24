# Get the filename from the command line argument
# Usage: make FILE=<filename without extension>
FILE ?= example

# Compiler to use
CC := gcc

# Compilation flags
CFLAGS := -g 

# Source file directory
SRC_DIR := src

# Binary output directory
BIN_DIR := bin

# Build rule
$(BIN_DIR)/$(FILE): $(SRC_DIR)/$(FILE).c
	$(CC) $(CFLAGS) $< -o $@

# run the program
run: $(BIN_DIR)/$(FILE)
	./$(BIN_DIR)/$(FILE)
