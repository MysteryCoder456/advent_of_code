#include <math.h>
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

        // Simpler iterative approach
        // int waysToBeat = 0;
        // for (int t = 1; t < t0; t++) {
        //     int x0 = t * (t0 - t);
        //     waysToBeat += (int)(x0 > record);
        // }
        // margin *= waysToBeat;

        // Faster & slightly more complicated solution using quadratics
        double discriminant = sqrt(t0 * t0 - 4 * record);
        double w1 = ceil((t0 + discriminant) / 2.0f);
        double w2 = floor((t0 - discriminant) / 2.0f);
        int waysToBeat = w1 - w2 - 1;
        // printf("%d\n", waysToBeat);
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
