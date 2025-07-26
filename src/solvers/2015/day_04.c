#include "../solvers.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <md5/md5.h>

static bool has_leading_zeros(const uint8_t* data, size_t zeros)
{
    for (size_t i = 0; i < zeros; i++)
    {
        uint8_t byte = data[i / 2];
        if ((i % 2 == 0 && (byte & 0xF0) != 0) || (i % 2 == 1 && (byte & 0xF) != 0)) return false;
    }

    return true;
}

static SolverResult first_hash_with_zeros(str_t input, size_t zeros)
{
    uint8_t digest[16];
    uint32_t suffix = 0;

    // TODO: use dynamic string
    char* key = malloc(input.length + 11);
    memcpy(key, input.data, input.length);

    do
    {
        snprintf(key + input.length, 11, "%d", ++suffix);
        hash_md5(&key[0], strlen(key), &digest[0]);
    } while (!has_leading_zeros(&digest[0], zeros));

    free(key);

    return (SolverResult){
        .type = RESULT_UNSIGNED_INT,
        .value.unsigned_int = suffix,
    };
}

SolverResult solve_2015_day_04_part_1(str_t input) { return first_hash_with_zeros(input, 5); }
SolverResult solve_2015_day_04_part_2(str_t input) { return first_hash_with_zeros(input, 6); }
