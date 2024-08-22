#include "../solvers.h"
#include "../../constants.h"
#include "../../lib/collections/hashset.h"
#include <strings.h>

static inline bool is_vowel(char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

static inline bool is_nice(const char* str)
{
    const char* naughty_strings[] = { "ab", "cd", "pq", "xy" };
    for (size_t i = 0; i < sizeof(naughty_strings) / sizeof(const char*); i++)
    {
        if (strstr(str, naughty_strings[i])) return false;
    }

    size_t vowels = 0, duplicates = 0;

    char c;
    while ((c = *(str++)))
    {
        vowels += is_vowel(c);
        duplicates += *str == c;
    }

    return vowels >= 3 && duplicates > 0;
}

SolverResult solve_2015_day_05_part_1(char* input)
{
    size_t nice_strings = 0;
    strtok(input, "\n");

    do
    {
        nice_strings += (int) is_nice(input);
    } while ((input = strtok(NULL, "\n")));

    return (SolverResult) {
        .type = RESULT_INT,
        .integer_result = (int) nice_strings
    };
}

// Don't ask me how this thing works..
static bool is_nice_v2(const char* str)
{
    HashSet seen_pairs = hashset_new(sizeof(char[2]), 100);
    size_t length = strlen(str);

    bool seen_pair_twice = false;
    bool seen_triplet = false;
    bool prev_same = false;

    for (size_t i = 0; i < length - 1; i++)
    {
        seen_triplet |= i < length - 2 && str[i] == str[i + 2];

        if (!seen_pair_twice)
        {
            if (str[i] == str[i + 1])
            {
                if (prev_same)
                {
                    prev_same = false;
                    continue;
                }

                prev_same = true;
            }
            else
            {
                prev_same = false;
            }

            if (hashset_contains(seen_pairs, &str[i]))
            {
                seen_pair_twice = true;
            }

            hashset_insert(&seen_pairs, &str[i]);
        }

        if (seen_triplet && seen_pair_twice) return true;
    }

    return false;
}

SolverResult solve_2015_day_05_part_2(char* input)
{
    size_t nice_strings = 0;
    strtok(input, "\n");

    do
    {
        nice_strings += is_nice_v2(input);;
    } while ((input = strtok(NULL, "\n")));

    return (SolverResult) {
        .type = RESULT_INT,
        .integer_result = (int) nice_strings
    };
}