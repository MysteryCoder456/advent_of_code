#include <stdio.h>
#include <string.h>

int stringStartsWithInt(char *string) {
    if (strncmp(string, "one", 3) == 0)
        return 1;
    else if (strncmp(string, "two", 3) == 0)
        return 2;
    else if (strncmp(string, "three", 5) == 0)
        return 3;
    else if (strncmp(string, "four", 4) == 0)
        return 4;
    else if (strncmp(string, "five", 4) == 0)
        return 5;
    else if (strncmp(string, "six", 3) == 0)
        return 6;
    else if (strncmp(string, "seven", 5) == 0)
        return 7;
    else if (strncmp(string, "eight", 5) == 0)
        return 8;
    else if (strncmp(string, "nine", 4) == 0)
        return 9;
    else
        return -1;
}

int part1() {
    // Open file
    FILE *fptr = fopen("day1.txt", "r");
    char line[100];

    // Solution
    int sum = 0;

    // Iterate over each line in file
    while (fgets(line, 100, fptr)) {
        int firstDigit = 0;
        int lastDigit = 0;

        size_t lineLen = strlen(line);

        // Retrieve the first and last digit in the line
        for (int i = 0; i < lineLen; i++) {
            int digit = line[i] - '0';

            if (digit > 0 && digit < 10) {
                // printf("%c -> %d\n", line[i], digit);

                if (firstDigit == 0)
                    firstDigit = digit;

                lastDigit = digit;
            }
        }

        int num = firstDigit * 10 + lastDigit;
        sum += num;

        // printf("%d\n", num);
    }

    fclose(fptr);
    return sum;
}

int part2() {
    // Open file
    FILE *fptr = fopen("day1.txt", "r");
    char line[100];

    // Solution
    int sum = 0;

    // Iterate over each line in file
    while (fgets(line, 100, fptr)) {
        int firstDigit = 0;
        int lastDigit = 0;

        size_t lineLen = strlen(line);

        // Retrieve the first and last digit in the line
        for (int i = 0; i < lineLen; i++) {
            int digit = line[i] - '0'; // Converts char to int

            if (digit < 1 || digit > 9)
                digit = stringStartsWithInt(line + i);

            if (digit != -1) {
                // printf("%c -> %d\n", line[i], digit);

                if (firstDigit == 0)
                    firstDigit = digit;

                lastDigit = digit;
            }
        }

        int num = firstDigit * 10 + lastDigit;
        sum += num;

        // printf("%d\n", num);
    }

    fclose(fptr);
    return sum;
}

int main() {
    printf("Part 1: %d\n", part1());
    printf("Part 2: %d\n", part2());
}
