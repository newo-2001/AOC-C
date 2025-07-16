#include "../solvers.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <md5/md5.h>

#include <aoc_lib/constants.h>

static bool has_leading_zeros(const uint8_t* data, size_t zeros)
{
    for (size_t i = 0; i < zeros; i++)
    {
        uint8_t byte = data[i / 2];
        if (
            (i % 2 == 0 && (byte & 0xF0) != 0) ||
            (i % 2 == 1 && (byte & 0xF) != 0)
        ) return false;
    }

    return true;
}

static SolverResult first_hash_with_zeros(const char* input, size_t zeros)
{
    uint8_t digest[16];
    uint32_t suffix = 0;

    size_t key_length = strlen(input);
    char* key = malloc(key_length + 11);
    memcpy(&key[0], input, key_length);

    do
    {
        snprintf(key + key_length, 11, "%d", ++suffix);
        //itoa(++suffix, key + key_length, 10);
        hash_md5(&key[0], strlen(key), &digest[0]);
    } while (!has_leading_zeros(&digest[0], zeros));

    free(key);

    return (SolverResult) {
        .type = RESULT_UNSIGNED_INT,
        .value.unsigned_int = suffix
    };
}

SolverResult solve_2015_day_04_part_1(const char* input)
{
    return first_hash_with_zeros(input, 5);
}

SolverResult solve_2015_day_04_part_2(const char* input)
{
    return first_hash_with_zeros(input, 6);
}
