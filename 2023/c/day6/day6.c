#include <stdio.h>
#include <stdlib.h>

int part1() {
    FILE *fptr = fopen("day6.txt", "r");

    char timesBuffer[64];
    char distancesBuffer[64];

    fgets(timesBuffer, 65, fptr);
    fgets(distancesBuffer, 65, fptr);
    fclose(fptr);

    // Solution
    int margin = 1;

    // Parse and process time and distance data
    for (int i = 0; i < 4; i++) {
        int t0 = atoi(&timesBuffer[9 + i * 7]);
        int record = atoi(&distancesBuffer[9 + i * 7]);
        int waysToBeat = 0;

        // Check all values from t = 1 to t = time - 1
        for (int t = 1; t < t0; t++) {
            int x0 = t * (t0 - t);
            waysToBeat += (int)(x0 > record);
        }

        margin *= waysToBeat;
    }

    return margin;
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
