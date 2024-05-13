#include "types.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 32

int part1() {
    Hand hands[1024];
    size_t handCount = 0;

    // Parse hands and bids
    FILE *fptr = fopen("day7.txt", "r");
    char buffer[MAX_LINE + 1];

    while (fgets(buffer, MAX_LINE + 1, fptr)) {
        Hand newHand;
        strncpy(newHand.cards, buffer, 5);
        newHand.handType = identifyHandType(newHand.cards);
        newHand.bid = atoi(&buffer[6]);

        // printf("%s => %d\n", newHand.cards, newHand.handType);
        hands[handCount++] = newHand;
    }

    fclose(fptr);

    // Sort hands based on card value
    qsort(hands, handCount, sizeof(Hand), compareHands);

    unsigned int totalWinnings = 0;
    for (int i = 0; i < handCount; i++)
        totalWinnings += hands[i].bid * (i + 1);
    return totalWinnings;
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
