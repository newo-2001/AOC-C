#define DEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/strutils.h"
#include "constants.h"
#include "solvers/solvers.h"

char* read_file(const char* path);

int main()
{
    Solver solvers[] = {
        solve_2015_day_01_part_1,
        solve_2015_day_01_part_2,
        solve_2015_day_02_part_1,
        solve_2015_day_02_part_2,
        solve_2015_day_03_part_1,
        solve_2015_day_03_part_2
    };

    const size_t NUM_SOLVERS = sizeof(solvers) / sizeof(Solver);

    for (size_t i = 0; i < NUM_SOLVERS; i++)
    {
        Solver solver = solvers[i];
        int year = 2015 + i / 49;
        int day = 1 + (i % 49) / 2;
        int part = 1 + (i % 49 % 2);

        char input_path[sizeof("inputs/2015/day_01.txt")];
        sprintf_s(&input_path[0], sizeof(input_path), "inputs/%i/day_%02i.txt", year, day);
        
        char* input = read_file(input_path);
        if (!input) return -1;

        SolverResult result = solver(input);
        free(input);

        char solution_path[sizeof("solutions/2015/day_01.txt")];
        sprintf_s(&solution_path[0], sizeof(solution_path), "solutions/%i/day_%02i.txt", year, day);

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
        switch (result.type)
        {
            case RESULT_INT:
            {
                size_t length = result.integer_result / 10 + 3;
                result_str = malloc(sizeof(char) * length);
                sprintf_s(result_str, length, "%d", result.integer_result);
                break;
            }
            case RESULT_STRING:
            case RESULT_STATIC_STRING:
                result_str = (char*) result.string_result;
                break;
            case RESULT_ERR:
            case RESULT_STATIC_ERR:
            {
                size_t length = strlen(result.string_result) + sizeof("Error(\"\")");
                result_str = malloc(length),
                sprintf_s(result_str, length, "Error(\"%s\")", result.string_result);

                if (result.type == RESULT_ERR)
                {
                    free(result.string_result);
                }

                break;
            }
        };

        if (!strcmp(result_str, solution))
        {
            printf("[%i-%02i-%i] [PASS] %s\n", year, day, part, result_str);
        }
        else
        {
            fprintf(stderr, "[%i-%02i-%i] [FAIL] got %s, expected: %s\n", year, day, part, result_str, solution);
        }

        free(result_str);
    }
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

    char* buffer = (char*) malloc(sizeof(char) * length);
    size_t read = fread_s(buffer, length, sizeof(char), length - 1, file);
    buffer[read] = '\0';

    fclose(file);

    return buffer;
}