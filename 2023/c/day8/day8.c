#include <stdio.h>
#include <string.h>

#define MAX_LINE 512

typedef struct node {
    char label[3];
    struct node *left;
    struct node *right;
} node;

int part1() {
    FILE *fptr = fopen("day8_demo.txt", "r");
    char *buf;
    size_t bufLength;

    // Parsing instructions

    buf = fgetln(fptr, &bufLength);

    size_t instructionCount = bufLength - 1;
    char instructions[instructionCount + 1];

    strncpy(instructions, buf, instructionCount);
    instructions[instructionCount] = '\0';

    printf("Instructions: %s\n", instructions);

    // Parse network and create a graph

    // Seek to the start of network
    fseek(fptr, 5, SEEK_SET);

    while ((buf = fgetln(fptr, &bufLength)) != NULL) {
        char nodeLabel[3];
        strncpy(nodeLabel, buf, 3);
    }

    fclose(fptr);

    return 0;
}

int part2() { return 0; }

// NOTE: solutions are incomplete
int main() {
    printf("Part 1: %d\n", part1());
    printf("Part 2: %d\n", part2());
    return 0;
}
