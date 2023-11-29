#include <stdio.h>

void reverseAlgorithm(int row, int col, int value) {
    // Calculate the binary representation of the value
    int binary[4];
    for (int i = 0; i < 4; i++) {
        binary[i] = value % 2;
        value /= 2;
    }

    // Determine the walls based on binary representation
    int topWall = binary[0];
    int rightWall = binary[1];
    int bottomWall = binary[2];
    int leftWall = binary[3];

    // Output the results
    printf("Triangle at coordinates (%d, %d) has:\n", row, col);
    printf("Top Wall: %s\n", topWall ? "Present" : "Not Present");
    printf("Right Wall: %s\n", rightWall ? "Present" : "Not Present");
    printf("Bottom Wall: %s\n", bottomWall ? "Present" : "Not Present");
    printf("Left Wall: %s\n", leftWall ? "Present" : "Not Present");
}

int main() {
    // Example usage
    reverseAlgorithm(6, 7, 5); // Change the coordinates and value as needed
    return 0;
}
