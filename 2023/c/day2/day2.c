#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_LEN 256
#define CUBE_DELIMITER ",;"

int part1() {
    FILE *fptr = fopen("day2.txt", "r");
    char line[LINE_BUFFER_LEN];

    int sum = 0;

    // Iterating lines
    while (fgets(line, LINE_BUFFER_LEN, fptr)) {
        int gameId = atoi(line + 5);
        bool possible = true;

        // Adding 8 to get rid of "Game X:"
        char *cube = strtok(line + 8, CUBE_DELIMITER);

        // Iterating cubes in a line
        while (cube != NULL) {
            int numCubes = atoi(cube);
            char *spacePtr;

            if (*cube == ' ')
                spacePtr = strchr(cube + 1, ' ');
            else
                spacePtr = strchr(cube, ' ');

            // printf("'%s' = %d,%c\n", cube, numCubes, *(spacePtr + 1));

            switch (*(spacePtr + 1)) {
            case 'r':
                possible = possible && numCubes <= 12;
                break;
            case 'g':
                possible = possible && numCubes <= 13;
                break;
            case 'b':
                possible = possible && numCubes <= 14;
                break;
            }

            cube = strtok(NULL, CUBE_DELIMITER);
        }

        if (possible)
            sum += gameId;
        // else
        //     printf("Game %d is impossible\n", gameId);
    }

    fclose(fptr);
    return sum;
}

int part2() {
    FILE *fptr = fopen("day2.txt", "r");
    char line[LINE_BUFFER_LEN];

    int sum = 0;

    // Iterating lines
    while (fgets(line, LINE_BUFFER_LEN, fptr)) {
        int maxes[] = {0, 0, 0};

        // Adding 8 to get rid of "Game X:"
        char *cube = strtok(line + 8, CUBE_DELIMITER);

        // Iterating cubes in a line
        while (cube != NULL) {
            int numCubes = atoi(cube);
            char *spacePtr;

            if (*cube == ' ')
                spacePtr = strchr(cube + 1, ' ');
            else
                spacePtr = strchr(cube, ' ');

            switch (*(spacePtr + 1)) {
            case 'r':
                if (numCubes > maxes[0])
                    maxes[0] = numCubes;
                break;
            case 'g':
                if (numCubes > maxes[1])
                    maxes[1] = numCubes;
                break;
            case 'b':
                if (numCubes > maxes[2])
                    maxes[2] = numCubes;
                break;
            }

            cube = strtok(NULL, CUBE_DELIMITER);
        }

        sum += maxes[0] * maxes[1] * maxes[2];
    }

    fclose(fptr);
    return sum;
}

int main() {
    printf("Part 1: %d\n", part1());
    printf("Part 2: %d\n", part2());
    return 0;
}
