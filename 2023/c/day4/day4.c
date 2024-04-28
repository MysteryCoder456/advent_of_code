#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 128
#define HEIGHT 193
#define WINNING_CARD_COUNT 10
#define MY_CARD_COUNT 25

int part1() {
    FILE *fptr = fopen("day4.txt", "r");
    char line[LINE_BUFFER_SIZE];

    int totalPoints = 0;

    while (fgets(line, LINE_BUFFER_SIZE, fptr)) {
        int winningCards[WINNING_CARD_COUNT];
        int myCards[MY_CARD_COUNT];

        char *colon = strstr(line, ":");
        char *pipe = strstr(line, "|");

        // Parsing both card piles
        for (int i = 0; i < WINNING_CARD_COUNT; i++) {
            winningCards[i] = atoi(&colon[3 * i + 2]);
        }
        for (int i = 0; i < MY_CARD_COUNT; i++) {
            myCards[i] = atoi(&pipe[3 * i + 2]);
        }

        int points = 0;

        // Checking for winning cards
        for (int i = 0; i < MY_CARD_COUNT; i++) {
            for (int j = 0; j < WINNING_CARD_COUNT; j++) {
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

int getTotalCardsFromLine(int cardNum, char grid[HEIGHT][LINE_BUFFER_SIZE],
                          int memoized[HEIGHT]) {
    if (memoized[cardNum - 1] != 0)
        return memoized[cardNum - 1];

    // printf("Processing card %d\n", cardNum);
    char *line = grid[cardNum - 1];

    int winningCards[WINNING_CARD_COUNT];
    int myCards[MY_CARD_COUNT];

    char *colon = strstr(line, ":");
    char *pipe = strstr(line, "|");

    // Parsing both card piles
    for (int i = 0; i < WINNING_CARD_COUNT; i++) {
        winningCards[i] = atoi(&colon[3 * i + 2]);
    }
    for (int i = 0; i < MY_CARD_COUNT; i++) {
        myCards[i] = atoi(&pipe[3 * i + 2]);
    }

    // Checking for winning cards
    int winningCardCount = 0;
    for (int i = 0; i < MY_CARD_COUNT; i++) {
        for (int j = 0; j < WINNING_CARD_COUNT; j++) {
            if (myCards[i] == winningCards[j]) {
                winningCardCount++;
            }
        }
    }

    // Get card counts from card copies that we won from the current card
    int totalCards = 1; // Includes the current card
    for (int i = 1; i <= winningCardCount; i++) {
        totalCards += getTotalCardsFromLine(cardNum + i, grid, memoized);
    }
    memoized[cardNum - 1] = totalCards;
    return totalCards;
}

int part2() {
    FILE *fptr = fopen("day4.txt", "r");
    char grid[HEIGHT][LINE_BUFFER_SIZE];

    // Read file into grid
    for (int i = 0; i < HEIGHT; i++)
        fgets(grid[i], LINE_BUFFER_SIZE, fptr);

    fclose(fptr);

    int totalCards = 0;
    int memoized[HEIGHT] = {0};

    for (int cardNum = 1; cardNum <= HEIGHT; cardNum++)
        totalCards += getTotalCardsFromLine(cardNum, grid, memoized);

    return totalCards;
}

int main() {
    printf("Part 1: %d\n", part1());
    printf("Part 2: %d\n", part2());
    return 0;
}
