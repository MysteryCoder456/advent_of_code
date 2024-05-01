#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

uint64_t arrayMin(uint64_t array[], int size) {
    int min = array[0];
    for (int i = 1; i < size; i++)
        if (array[i] < min)
            min = array[i];
    return min;
}

uint64_t mapRange(uint64_t value, uint64_t destStart, uint64_t sourceStart,
                  uint64_t rangeSize) {
    if (sourceStart <= value && value < sourceStart + rangeSize)
        return destStart + (value - sourceStart);
    else
        return value;
}

size_t getSeedsArray(uint64_t dest[], char *source) {
    int i = 0;
    char *token;

    while ((token = strsep(&source, " ")) != NULL) {
        dest[i] = atol(token);
        i++;
    }

    return i;
}

uint64_t part1() {
    FILE *fptr = fopen("day5.txt", "r");
    char lineBuffer[MAX_LINE];

    // Parse seeds list
    fgets(lineBuffer, MAX_LINE, fptr);
    char *seedsBuffer = &lineBuffer[7];
    uint64_t seeds[32];
    size_t seedCount = getSeedsArray(seeds, seedsBuffer);

    // Skip newline after seed list
    fgets(lineBuffer, MAX_LINE, fptr);

    // Parse map sections
    while (!feof(fptr)) {
        // Skip map heading
        fgets(lineBuffer, MAX_LINE, fptr);

        uint64_t ranges[64][3];
        int rangeCount = 0;

        // Parse ranges and store them
        fgets(lineBuffer, MAX_LINE, fptr);
        while (*lineBuffer != '\n' && !feof(fptr)) {
            char *rangeStr = strdup(lineBuffer);

            // Store each component of range
            for (int i = 0; i < 3; i++)
                ranges[rangeCount][i] = atol(strsep(&rangeStr, " "));

            free(rangeStr);
            fgets(lineBuffer, MAX_LINE, fptr);
            rangeCount++;
        }

        // Map each seed to ranges
        for (int i = 0; i < seedCount; i++) {
            for (int j = 0; j < rangeCount; j++) {
                uint64_t seed = seeds[i];
                uint64_t *range = ranges[j];

                uint64_t mappedSeed =
                    mapRange(seed, range[0], range[1], range[2]);

                if (seed != mappedSeed) {
                    seeds[i] = mappedSeed;
                    break;
                }
            }
        }
    }

    fclose(fptr);

    // Return minimum of mapped seeds
    return arrayMin(seeds, seedCount);
}

uint64_t part2() {
    // TODO
    return 0;
}

int main() {
    printf("Part 1: %lld\n", part1());
    printf("Part 2: %lld\n", part2());
    return 0;
}
