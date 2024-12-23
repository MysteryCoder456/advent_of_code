#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int directions[8][2] = {{1, 0},  {1, 1},   {0, 1},  {-1, 1},
                        {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

bool strcmpdir(char *str, int strlen, int w, int h, char cmpstr[w * h + 1],
               int x, int y, int dir[2]) {
    if (x < 0 || x >= w || y < 0 || y >= h)
        return false;

    int dx = dir[0];
    int dy = dir[1];

    for (int i = 0; i < strlen; i++) {
        int nx = x + dx * i;
        int ny = y + dy * i;

        if (nx < 0 || nx >= w || ny < 0 || ny >= h)
            return false;

        int idx = ny * w + nx;
        if (cmpstr[idx] != str[i]) {
            return false;
        }
    }

    return true;
}

int part_one() {
    FILE *fp = fopen("day4.txt", "r");
    char buffer[256];

    // Count the number of lines
    int line_count = 0;
    while (fgets(buffer, 256 - 1, fp) != NULL)
        line_count++;
    fseek(fp, 0, SEEK_SET);

    // Read the lines into a 2D-char array
    int line_length = strlen(buffer) - 1;
    char chars[line_count * line_length + 1];
    int i = 0;
    while (fgets(buffer, 256 - 1, fp) != NULL) {
        strncpy(chars + (i * line_length), buffer, line_length + 1);
        i++;
    }

    int xmas_count = 0;
    for (int y = 0; y < line_count; y++) {
        for (int x = 0; x < line_length; x++) {
            for (int i = 0; i < 8; i++) {
                int *dir = directions[i];
                if (strcmpdir("XMAS", 4, line_length, line_count, chars, x, y,
                              dir))
                    xmas_count++;
            }
        }
    }

    fclose(fp);
    return xmas_count;
}

int part_two() {
    FILE *fp = fopen("day4.txt", "r");
    char buffer[256];

    // Count the number of lines
    int line_count = 0;
    while (fgets(buffer, 256 - 1, fp) != NULL)
        line_count++;
    fseek(fp, 0, SEEK_SET);

    // Read the lines into a 2D-char array
    int line_length = strlen(buffer) - 1;
    char chars[line_count * line_length + 1];
    int i = 0;
    while (fgets(buffer, 256 - 1, fp) != NULL) {
        strncpy(chars + (i * line_length), buffer, line_length + 1);
        i++;
    }

    int xmas_count = 0;
    for (int y = 0; y < line_count; y++) {
        for (int x = 0; x < line_length; x++) {
            if (strcmpdir("MAS", 3, line_length, line_count, chars, x, y,
                          (int[]){1, 1}) &&
                strcmpdir("MAS", 3, line_length, line_count, chars, x, y + 2,
                          (int[]){1, -1}))
                xmas_count++;

            if (strcmpdir("MAS", 3, line_length, line_count, chars, x, y,
                          (int[]){-1, 1}) &&
                strcmpdir("MAS", 3, line_length, line_count, chars, x, y + 2,
                          (int[]){-1, -1}))
                xmas_count++;

            if (strcmpdir("MAS", 3, line_length, line_count, chars, x, y,
                          (int[]){1, 1}) &&
                strcmpdir("MAS", 3, line_length, line_count, chars, x + 2, y,
                          (int[]){-1, 1}))
                xmas_count++;

            if (strcmpdir("MAS", 3, line_length, line_count, chars, x, y,
                          (int[]){1, -1}) &&
                strcmpdir("MAS", 3, line_length, line_count, chars, x + 2, y,
                          (int[]){-1, -1}))
                xmas_count++;
        }
    }

    fclose(fp);
    return xmas_count;
}

int main() {
    printf("Part 1: %d\n", part_one());
    printf("Part 2: %d\n", part_two());
}
