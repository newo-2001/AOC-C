#include <string.h>
#include <stdlib.h>
#include "../solvers.h"
#include "../../lib/hash.h"
#include "../../constants.h"

static bool has_leading_zeros(const uint8_t* data, size_t zeros)
{
    for (size_t i = 0; i < zeros; i++)
    {
        uint8_t byte = data[i / 2];
        if ((i % 2 == 0 && (byte & 0xF0) != 0) || (i % 2 == 1 && (byte & 0xF) != 0)) return false;
    }

    return true;
}

static int first_hash_with_zeros(const char* input, size_t zeros)
{
    uint8_t digest[16];
    int suffix = 0;

    size_t key_length = strlen(input);
    char* key = malloc(key_length + 10);
    memcpy(&key[0], input, key_length);

    do
    {
        itoa(++suffix, key + key_length, 10);
        hash_md5(&key[0], strlen(key), &digest[0]);
    } while (!has_leading_zeros(&digest[0], zeros));

    free(key);

    return suffix;
}

SolverResult solve_2015_day_04_part_1(const char* input)
{
    return (SolverResult) {
        .type = RESULT_INT,
        .integer_result = first_hash_with_zeros(input, 5)
    };
}

SolverResult solve_2015_day_04_part_2(const char* input)
{
    return (SolverResult) {
        .type = RESULT_INT,
        .integer_result = first_hash_with_zeros(input, 6)
    };
}
