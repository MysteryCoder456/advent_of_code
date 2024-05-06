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

int numDigits(int num) {
    int digits = 0;
    while (num > 0) {
        num /= 10;
        digits++;
    }
    return digits;
}

int part2() {
    FILE *fptr = fopen("day6.txt", "r");

    char timeBuffer[64];
    char distanceBuffer[64];

    fgets(timeBuffer, 65, fptr);
    fgets(distanceBuffer, 65, fptr);
    fclose(fptr);

    // Parse combined data
    char t0Buffer[16];
    int t0Cursor = 0;

    char recordBuffer[16];
    int recordCursor = 0;

    for (int i = 0; i < 4; i++) {
        int time = atoi(&timeBuffer[9 + i * 7]);
        sprintf(&t0Buffer[t0Cursor], "%d", time);
        t0Cursor += numDigits(time);

        int distance = atoi(&distanceBuffer[9 + i * 7]);
        sprintf(&recordBuffer[recordCursor], "%d", distance);
        recordCursor += numDigits(distance);
    }

    // printf("%s\t%s\n", t0Buffer, recordBuffer);

    long long t0 = atoll(t0Buffer);
    long long record = atol(recordBuffer);

    // printf("%lld\t%lld\n", t0, record);

    // Process solution
    double discriminant = sqrt(t0 * t0 - 4 * record);
    double w1 = ceil((t0 + discriminant) / 2.0f);
    double w2 = floor((t0 - discriminant) / 2.0f);
    int waysToBeat = w1 - w2 - 1;

    // printf("D = %f\tw1 = %f\tw2 = %f\n", discriminant, w1, w2);
    return waysToBeat;
}

int main() {
    printf("Part 1: %d\n", part1());
    printf("Part 2: %d\n", part2());
    return 0;
}
