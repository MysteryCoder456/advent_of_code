#ifndef _TYPES_H
#define _TYPES_H

typedef enum {
    HIGH_CARD = 0,
    ONE_PAIR = 1,
    TWO_PAIR = 2,
    THREE_OF_A_KIND = 3,
    FULL_HOUSE = 4,
    FOUR_OF_A_KIND = 5,
    FIVE_OF_A_KIND = 6,
} HandType;

typedef struct {
    char cards[5 + 1];
    HandType handType;
    unsigned int bid;
} Hand;

#endif
