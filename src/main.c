#define SKIP_SLOW_SOLVERS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>

#include <aoc_lib/strutils.h>

#include "solvers/solvers.h"
#include "timer.h"

char* read_file(const char* path);

int hash_day(unsigned int year, unsigned int day)
{
    return day * 50 + year;
}

int main()
{
    Solver solvers[] = { solve_2015_day_01_part_1, solve_2015_day_01_part_2,
                         solve_2015_day_02_part_1, solve_2015_day_02_part_2,
                         solve_2015_day_03_part_1, solve_2015_day_03_part_2,
                         solve_2015_day_04_part_1, SLOW_SOLVER(solve_2015_day_04_part_2),
                         solve_2015_day_05_part_1, solve_2015_day_05_part_2,
                         solve_2015_day_06_part_1, solve_2015_day_06_part_2,
                         solve_2015_day_07_part_1, solve_2015_day_07_part_2,
                         solve_2015_day_08_part_1, solve_2015_day_08_part_2 };

    const size_t NUM_SOLVERS = sizeof(solvers) / sizeof(Solver);

    int last_day_hash = 0;
    char* input = NULL;

    for (unsigned int i = 0; i < NUM_SOLVERS; i++)
    {
        Solver solver = solvers[i];

        unsigned int year = 2015 + i / 49;
        unsigned int day = 1 + (i % 49) / 2;
        unsigned int part = 1 + (i % 49 % 2);

        char puzzle_id[sizeof("2015-01-1")];
        sprintf(&puzzle_id[0], "%i-%02i-%i", year, day, part);

        if (!solver)
        {
            printf("[%s] [SKIP] Skipping due to long execution time\n", puzzle_id);
            continue;
        }

        int day_hash = hash_day(year, day);
        if (last_day_hash != day_hash)
        {
            if (input) free(input);
            last_day_hash = day_hash;

            char input_path[sizeof("inputs/2015/day_01.txt")];
            snprintf(&input_path[0], sizeof(input_path), "inputs/%i/day_%02i.txt", year, day);

            input = read_file(input_path);
            if (!input) return -1;
        }

        timer_start();
        SolverResult result = solver(STR_SLICE(input));
        Duration duration = timer_stop();

        char solution_path[sizeof("solutions/2015/day_01.txt")];
        snprintf(&solution_path[0], sizeof(solution_path), "solutions/%i/day_%02i.txt", year, day);

        char* solutions = read_file(solution_path);
        if (!solutions) return -1;

        char* solution = strtok(solutions, ";");
        if (!solution || (part == 2 && !(solution = strtok(NULL, ";"))))
        {
            fprintf(stderr, "Failed to parse solution for %i-%02i-%i\n", year, day, part);
            return -1;
        }

        while (is_whitespace(*solution)) solution++;

        char* result_str = NULL;
        size_t length;
        switch (result.type)
        {
            case RESULT_UNSIGNED_INT:
                length = result.value.unsigned_int / 10 + 3;
                result_str = malloc(sizeof(char) * length);
                snprintf(result_str, length, "%" PRIu64, result.value.unsigned_int);
                break;
            case RESULT_SIGNED_INT:
                length = result.value.signed_int / 10 + 3;
                result_str = malloc(sizeof(char) * length);
                snprintf(result_str, length, "%" PRIi64, result.value.signed_int);
                break;
            case RESULT_DYNAMIC_STRING:
            case RESULT_STATIC_STRING:
                result_str = result.value.string;
                break;
            case RESULT_DYNAMIC_ERR:
            case RESULT_STATIC_ERR:
            {
                size_t str_len = strlen(result.value.string) + sizeof("Error(\"\")");
                result_str = malloc(str_len);
                snprintf(result_str, str_len, "Error(\"%s\")", result.value.string);

                if (result.type == RESULT_DYNAMIC_ERR)
                {
                    free(result.value.string);
                }

                break;
            }
        }

        if (!strcmp(result_str, solution))
        {
            printf("[%s] [PASS] [%02u.%03d:%03d] %s\n", puzzle_id, duration.seconds, duration.millis, duration.micros,
                   result_str);
        }
        else
        {
            fprintf(stderr, "[%s] [FAIL] got %s, expected: %s\n", puzzle_id, result_str, solution);
        }

        free(solutions);

        if (result.type != RESULT_STATIC_STRING)
        {
            free(result_str);
        }
    }

    if (input) free(input);
}

char* read_file(const char* path)
{
    FILE* file = fopen(path, "r");
    if (!file)
    {
        fprintf(stderr, "Failed to open file: %s\n", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(sizeof(char) * (length + 1));
    size_t read = fread(buffer, sizeof(char), length, file);
    buffer[read] = '\0';

    fclose(file);

    return buffer;
}