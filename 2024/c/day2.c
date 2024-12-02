#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_levels(int levels[], size_t size, bool safe, int direction) {
    for (int i = 0; i < size; i++)
        printf("%d ", levels[i]);
    printf("- %s %d\n", safe ? "safe" : "unsafe", direction);
}

int find_general_direction(int levels[], size_t size) {
    int decreasing = 0;
    int increasing = 0;

    for (int i = 1; i < size; i++) {
        int diff = levels[i] - levels[i - 1];

        if (diff < 0)
            decreasing++;
        else if (diff > 0)
            increasing++;
    }

    return increasing >= decreasing ? 1 : -1;
}

bool is_level_safe(int level1, int level2, int dir) {
    int diff = level2 - level1;

    if (diff == 0)
        return false;

    int local_dir = abs(diff) / diff;

    // Check if all levels follow the initial direction and their
    // difference is between 1 and 3
    return (local_dir == dir && abs(diff) >= 1 && abs(diff) <= 3);
}

int part_one() {
    FILE *fp = fopen("day2.txt", "r");
    char buffer[64];

    int safe_count = 0;

    while (fgets(buffer, 64 - 1, fp) != NULL) {
        int levels[32];
        size_t levels_size = 0;

        // Parse each line into a list of levels
        char *buf_copy = strdup(buffer);
        char *level_str;
        while ((level_str = strsep(&buf_copy, " ")) != NULL)
            levels[levels_size++] = atoi(level_str);

        // Determine whether list is "safe"
        int dir = find_general_direction(levels, levels_size);
        bool safe = true;
        for (int i = 1; i < levels_size; i++)
            safe = safe && is_level_safe(levels[i - 1], levels[i], dir);
        safe_count += (int)safe;
    }

    fclose(fp);
    return safe_count;
}

// FIXME: need to fix some edge cases, seems to work on most data I throw at it
// except the actual input though :(
int part_two() {
    FILE *fp = fopen("day2.txt", "r");
    char buffer[64];

    int safe_count = 0;

    while (fgets(buffer, 64 - 1, fp) != NULL) {
        int levels[16];
        size_t levels_size = 0;

        // Parse each line into a list of levels
        char *buf_copy = strdup(buffer);
        char *level_str;
        while ((level_str = strsep(&buf_copy, " ")) != NULL)
            levels[levels_size++] = atoi(level_str);

        // Find and remove the first unsafe level
        int dir = find_general_direction(levels, levels_size);
        int unsafe_index = -1;
        for (int i = 1; i < levels_size; i++) {
            if (!is_level_safe(levels[i - 1], levels[i], dir)) {
                if (i > 2 && is_level_safe(levels[i - 2], levels[i], dir) ||
                    i < levels_size - 1 &&
                        is_level_safe(levels[i], levels[i + 1], dir))
                    unsafe_index = i - 1;
                else
                    unsafe_index = i;

                break;
            }
        }

        // If no unsafe level is found, the list is safe
        if (unsafe_index == -1) {
            print_levels(levels, levels_size, true, dir);
            safe_count++;
            continue;
        }

        // If there is an unsafe level, remove it and check if the list is safe
        // without it

        for (int i = unsafe_index; i < levels_size - 1; i++)
            levels[i] = levels[i + 1];
        levels_size--;

        dir = find_general_direction(levels, levels_size);
        bool safe = true;
        for (int i = 1; i < levels_size; i++)
            safe = safe && is_level_safe(levels[i - 1], levels[i], dir);
        safe_count += (int)safe;
        print_levels(levels, levels_size, safe, dir);
    }

    fclose(fp);
    return safe_count;
}

int main() {
    printf("Part 1: %d\n", part_one());
    printf("Part 2: %d\n", part_two());
}
