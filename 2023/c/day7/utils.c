#include "types.h"

int cardValue(char card) {
    switch (card) {
    case 'A':
        return 12;
    case 'K':
        return 11;
    case 'Q':
        return 10;
    case 'J':
        return 9;
    case 'T':
        return 8;
    case '9':
        return 7;
    case '8':
        return 6;
    case '7':
        return 5;
    case '6':
        return 4;
    case '5':
        return 3;
    case '4':
        return 2;
    case '3':
        return 1;
    case '2':
        return 0;
    }
    return -1;
}

HandType identifyHandType(char cards[5]) {
    int freq[13] = {0};
    int distinctCards = 0;
    int f;

    for (int i = 0; i < 5; i++) {
        int val = cardValue(cards[i]);
        freq[val]++;

        if (freq[val] == 1)
            distinctCards++;
    }

    switch (distinctCards) {
    case 1:
        return FIVE_OF_A_KIND;
    case 2:
        // Either FOUR_OF_A_KIND or FULL_HOUSE

        f = freq[cardValue(cards[0])];
        if (f == 1 || f == 4)
            return FOUR_OF_A_KIND;
        else if (f == 2 || f == 3)
            return FULL_HOUSE;

    case 3:
        // Either THREE_OF_A_KIND or TWO_PAIR

        for (int i = 0; i < 5; i++) {
            f = freq[cardValue(cards[i])];
            if (f == 3)
                return THREE_OF_A_KIND;
            else if (f == 2)
                return TWO_PAIR;
        }

    case 4:
        return ONE_PAIR;
    default:
        return HIGH_CARD;
    }
}

int compareHands(const void *hand1, const void *hand2) {
    Hand h1 = *(Hand *)hand1;
    Hand h2 = *(Hand *)hand2;

    if (h1.handType > h2.handType)
        return 1;
    if (h1.handType < h2.handType)
        return -1;

    for (int i = 0; i < 5; i++) {
        char c1 = h1.cards[i];
        int v1 = cardValue(c1);

        char c2 = h2.cards[i];
        int v2 = cardValue(c2);

        if (v1 > v2)
            return 1;
        if (v1 < v2)
            return -1;
    }

    return 0;
}
