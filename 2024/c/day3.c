#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part_one() {
    FILE *fp = fopen("day3.txt", "r");
    char buffer[8192];

    const char *regex_pattern = "mul\\([0-9]{1,3},[0-9]{1,3}\\)";
    regex_t re;
    int errcode = regcomp(&re, regex_pattern, REG_EXTENDED);

    if (errcode != 0) {
        regerror(errcode, &re, buffer, 8192 - 1);
        printf("Regex compilation error: %s\n", buffer);
        return 0;
    }

    int sum = 0;
    regmatch_t match;

    while (fgets(buffer, 8192 - 1, fp)) {
        char *remaining_line = buffer;
        while (regexec(&re, remaining_line, 1, &match, 0) != REG_NOMATCH) {
            remaining_line += match.rm_so;

            int num1 = atoi(remaining_line + 4);
            strsep(&remaining_line, ",");
            int num2 = atoi(remaining_line);
            int prod = num1 * num2;
            sum += prod;

            /*printf("%d * %d = %d\n", num1, num2, prod);*/
        }
    }

    regfree(&re);
    fclose(fp);
    return sum;
}

int part_two() {
    FILE *fp = fopen("day3.txt", "r");
    char buffer[8192];

    const char *regex_pattern =
        "(mul\\([0-9]{1,3},[0-9]{1,3}\\))|do\\(\\)|don't\\(\\)";
    regex_t re;
    int errcode = regcomp(&re, regex_pattern, REG_EXTENDED);

    if (errcode != 0) {
        regerror(errcode, &re, buffer, 8192 - 1);
        printf("Regex compilation error: %s\n", buffer);
        return 0;
    }

    int sum = 0;
    bool mul_enabled = true;
    regmatch_t match;

    while (fgets(buffer, 8192 - 1, fp)) {
        char *remaining_line = buffer;
        while (regexec(&re, remaining_line, 1, &match, 0) != REG_NOMATCH) {
            remaining_line += match.rm_so;

            if (strncmp(remaining_line, "do()", 4) == 0) {
                mul_enabled = true;
                remaining_line += 4;
                continue;
            }
            if (strncmp(remaining_line, "don't()", 7) == 0) {
                mul_enabled = false;
                remaining_line += 7;
                continue;
            }

            if (!mul_enabled) {
                remaining_line += 3;
                continue;
            }

            int num1 = atoi(remaining_line + 4);
            strsep(&remaining_line, ",");
            int num2 = atoi(remaining_line);
            int prod = num1 * num2;
            sum += prod;

            /*printf("%d * %d = %d\n", num1, num2, prod);*/
        }
    }

    regfree(&re);
    fclose(fp);
    return sum;
}

int main() {
    printf("Part 1: %d\n", part_one());
    printf("Part 2: %d\n", part_two());
}
