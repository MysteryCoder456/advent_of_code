#include <stdio.h>
#include <stdlib.h>

int digitCount(int num) {
    int count = 0;
    while (num > 0) {
        num = num / 10;
        count++;
    }
    return count;
}

// Sorts an array of numbers using selection sort.
void sort(int arr[], size_t length) {
    for (int i = 0; i < length; i++) {
        // Find minimum
        int minIdx = i;
        int min = arr[minIdx];
        for (int j = i + 1; j < length; j++) {
            if (arr[j] < min) {
                minIdx = j;
                min = arr[j];
            }
        }

        // Swap with first element in unsorted region
        int temp = arr[i];
        arr[i] = min;
        arr[minIdx] = temp;
    }
}

int part_one() {
    FILE *fp = fopen("day1.txt", "r");
    char buffer[64];

    // Count the number of lines
    int lineCount = 0;
    while (fgets(buffer, 64 - 1, fp) != NULL)
        lineCount++;

    // Create the two number lists

    int list1[lineCount], size1 = 0;
    int list2[lineCount], size2 = 0;
    fseek(fp, 0, 0);

    while (fgets(buffer, 64 - 1, fp) != NULL) {
        int firstNum = atoi(buffer);
        list1[size1++] = firstNum;

        list2[size2++] = atoi(buffer + digitCount(firstNum) + 3);
    }

    // Sort the lists
    sort(list1, lineCount);
    sort(list2, lineCount);

    // Calculate sum of differences
    int diff = 0;
    for (int i = 0; i < lineCount; i++)
        diff += abs(list1[i] - list2[i]);

    fclose(fp);
    return diff;
}

int part_two() {
    FILE *fp = fopen("day1.txt", "r");
    char buffer[64];

    // Count the number of lines
    int lineCount = 0;
    while (fgets(buffer, 64 - 1, fp) != NULL)
        lineCount++;

    // Create the two number lists

    int list1[lineCount], size1 = 0;
    int list2[lineCount], size2 = 0;
    fseek(fp, 0, 0);

    while (fgets(buffer, 64 - 1, fp) != NULL) {
        int firstNum = atoi(buffer);
        list1[size1++] = firstNum;

        list2[size2++] = atoi(buffer + digitCount(firstNum) + 3);
    }

    // Calculate similarity score
    int similarity = 0;
    for (int i = 0; i < lineCount; i++)
        for (int j = 0; j < lineCount; j++)
            if (list2[j] == list1[i])
                similarity += list1[i];

    fclose(fp);
    return similarity;
}

int main() {
    printf("Part 1: %d\n", part_one());
    printf("Part 2: %d\n", part_two());
}
