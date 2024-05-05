#include <pthread.h>
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

// Part 2 stuff below

uint64_t ranges[7][64][3];
int rangeCounts[7];

typedef struct {
    uint64_t start;
    uint64_t size;
} inner_arg;

void *innerThread(void *thread_arg) {
    inner_arg *arg = thread_arg;
    uint64_t *minLocation = malloc(sizeof(uint64_t));
    *minLocation = UINT64_MAX;

    for (uint64_t seed = arg->start; seed < arg->start + arg->size; seed++) {
        uint64_t mappedSeed = seed;

        // if (seed % 10000000 == 0)
        //     printf("processing seed %lld\n", seed);

        // Sections
        for (int i = 0; i < 7; i++) {
            int rangeCount = rangeCounts[i];

            // Ranges
            for (int j = 0; j < rangeCount; j++) {
                uint64_t *range = ranges[i][j];
                uint64_t seedBefore = mappedSeed;
                mappedSeed = mapRange(mappedSeed, range[0], range[1], range[2]);

                if (mappedSeed != seedBefore)
                    break;
            }
        }

        if (mappedSeed < *minLocation)
            *minLocation = mappedSeed;
    }

    free(arg);
    return minLocation;
}

uint64_t part2() {
    FILE *fptr = fopen("day5.txt", "r");
    char lineBuffer[MAX_LINE];

    // Skip to first map section
    fgets(lineBuffer, MAX_LINE, fptr);
    fgets(lineBuffer, MAX_LINE, fptr);

    int section = 0;

    // Parse map sections
    while (!feof(fptr)) {
        // Skip map heading
        fgets(lineBuffer, MAX_LINE, fptr);

        int rangeCount = 0;

        // Parse ranges and store them
        fgets(lineBuffer, MAX_LINE, fptr);
        while (*lineBuffer != '\n' && !feof(fptr)) {
            char *rangeStr = strdup(lineBuffer);

            // Store each component of range
            for (int k = 0; k < 3; k++)
                ranges[section][rangeCount][k] = atol(strsep(&rangeStr, " "));

            free(rangeStr);
            fgets(lineBuffer, MAX_LINE, fptr);
            rangeCount++;
        }

        rangeCounts[section] = rangeCount;
        section++;
    }

    // Seek to beginning of file and get seed ranges list
    fseek(fptr, 0, 0);
    fgets(lineBuffer, MAX_LINE, fptr);
    fclose(fptr);
    char *seedsBuffer = &lineBuffer[7];

    // Parse seed ranges and find minimum location value
    pthread_t handles[16];
    size_t handle_count = 0;
    char *first;
    while ((first = strsep(&seedsBuffer, " ")) != NULL) {
        char *second = strsep(&seedsBuffer, " ");

        uint64_t start = atol(first);
        uint64_t size = atol(second);
        // printf("processing seed range %lld : %lld\n", start, size);

        // Thread arguments
        inner_arg *arg = malloc(sizeof(inner_arg));
        arg->start = start;
        arg->size = size;

        // Create thread to process seeds
        pthread_t t;
        pthread_create(&t, NULL, innerThread, arg);
        handles[handle_count] = t;
        handle_count++;
    }

    uint64_t minLocation = UINT64_MAX;
    for (int i = 0; i < handle_count; i++) {
        int *location;
        pthread_join(handles[i], (void **)&location);

        if (*location < minLocation)
            minLocation = *location;

        free(location);
    }
    return minLocation;
}

int main() {
    printf("Part 1: %lld\n", part1());
    printf("Part 2: %lld\n", part2());
    return 0;
}
