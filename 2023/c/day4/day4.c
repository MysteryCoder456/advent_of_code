#include <stdio.h>
#include <stdlib.h>

#define LINE_BUFFER_SIZE 128

int part1() {
    FILE *fptr = fopen("day4.txt", "r");
    char line[LINE_BUFFER_SIZE];

    int totalPoints = 0;

    while (fgets(line, LINE_BUFFER_SIZE, fptr)) {
        int winningCards[10];
        int myCards[25];

        for (int i = 0; i < 10; i++) {
            winningCards[i] = atoi(&line[3 * i + 10]);
        }
        for (int i = 0; i < 25; i++) {
            myCards[i] = atoi(&line[3 * i + 42]);
        }

        int points = 0;

        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 10; j++) {
                if (myCards[i] == winningCards[j]) {
                    points = points > 0 ? points * 2 : 1;
                    break;
                }
            }
        }

        totalPoints += points;
    }

    fclose(fptr);
    return totalPoints;
}

int part2() {
    // TODO
    return 0;
}

int main() {
    printf("Part 1: %d\n", part1());
    printf("Part 2: %d\n", part2());
    return 0;
}
