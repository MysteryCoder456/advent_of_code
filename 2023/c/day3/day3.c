#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

#define WIDTH 140
#define HEIGHT 140

int posToIndex(int x, int y) { return y * (WIDTH + 1) + x; }

// Gets the number of digits in a number
int numDigits(int num) {
    int digits = 0;

    while (num > 0) {
        num = num / 10;
        digits++;
    }

    return digits;
}

int part1() {
    FILE *fptr = fopen("day3.txt", "r");

    // Read the entire file into a single string without line breaks
    char content[(WIDTH + 1) * HEIGHT];
    char line[256];
    char *end = content;
    while (fgets(line, WIDTH + 2, fptr)) {
        end = stpncpy(end, line, WIDTH + 1);
    }

    fclose(fptr);

    // printf("%s\n", content);
    // printf("%ld\n", strlen(content));

    int sum = 0;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int idx = posToIndex(x, y);
            char ch = content[idx];

            // Skip character if it isn't a digit
            if (!isdigit(ch))
                continue;

            bool isPart = false;
            int num = atoi(&content[idx]);
            int digits = numDigits(num);

            // Checking neighboring characters
            for (int i = 0; i < digits; i++) {
                // Top
                if (y > 0) {
                    bool top = content[posToIndex(x + i, y - 1)] != '.';
                    isPart = isPart || top;
                }

                // Bottom
                if (y < HEIGHT - 1) {
                    bool bot = content[posToIndex(x + i, y + 1)] != '.';
                    isPart = isPart || bot;
                }

                // Left
                if (i == 0 && x > 0) {
                    bool left = content[posToIndex(x - 1, y)] != '.';
                    isPart = isPart || left;

                    if (y > 0) {
                        bool topLeft = content[posToIndex(x - 1, y - 1)] != '.';
                        isPart = isPart || topLeft;
                    }

                    if (y < HEIGHT - 1) {
                        bool botLeft = content[posToIndex(x - 1, y + 1)] != '.';
                        isPart = isPart || botLeft;
                    }
                }

                // Right
                if (i == digits - 1 && x + i < WIDTH - 1) {
                    bool right = content[posToIndex(x + i + 1, y)] != '.';
                    isPart = isPart || right;

                    if (y > 0) {
                        bool topRight =
                            content[posToIndex(x + i + 1, y - 1)] != '.';
                        isPart = isPart || topRight;
                    }

                    if (y < HEIGHT - 1) {
                        bool botRight =
                            content[posToIndex(x + i + 1, y + 1)] != '.';
                        isPart = isPart || botRight;
                    }
                }
            }

            if (isPart) {
                // printf("%d is a part\n", num);
                sum += num;
            }

            x += digits - 1;
        }
        // printf("Current sum (y = %d) = %d\n", y, sum);
    }

    return sum;
}

int part2() {
    FILE *fptr = fopen("day3.txt", "r");
    char grid[HEIGHT][WIDTH + 2];

    for (int i = 0; i < HEIGHT; i++) {
        fgets(&grid[i], WIDTH + 2, fptr);
    }

    fclose(fptr);

    int dirs[8][2] = {
        {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1},
    };
    int sum = 0;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            char ch = grid[y][x];

            if (ch != '*')
                continue;

            int firstPos[] = {-1, -1};
            int secondPos[] = {-1, -1};
            int numsFound = 0;

            // Check neighboring characters
            for (int i = 0; i < 8; i++) {
                int *dir = dirs[i];
                int nx = x + dir[1];
                int ny = y + dir[0];
                bool inBounds = nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT;

                if (isdigit(grid[ny][nx]) && inBounds) {
                    while (nx > 0 && isdigit(grid[ny][nx - 1])) {
                        nx--;
                    }

                    if (nx == firstPos[1] && ny == firstPos[0] ||
                        nx == secondPos[1] && ny == secondPos[0])
                        continue;

                    if (numsFound == 0) {
                        firstPos[0] = ny;
                        firstPos[1] = nx;
                    } else if (numsFound == 1) {
                        secondPos[0] = ny;
                        secondPos[1] = nx;
                    }
                    numsFound++;
                }
            }

            if (numsFound != 2)
                continue;

            // Parse found numbers
            int firstNum = atoi(&grid[firstPos[0]][firstPos[1]]);
            int secondNum = atoi(&grid[secondPos[0]][secondPos[1]]);

            // Find gear ratio
            int ratio = firstNum * secondNum;
            sum += ratio;

            // printf("x=%d\ty=%d\t%dx%d=%d\n", x, y, firstNum, secondNum,
            // ratio);
        }
    }

    return sum;
}

int main() {
    printf("Part 1: %d\n", part1());
    printf("Part 2: %d\n", part2());
    return 0;
}
