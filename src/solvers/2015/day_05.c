#include "../solvers.h"

#include <stdlib.h>
#include <stdbool.h>

#include <aoc_lib/collections/hashset.h>

static inline bool is_vowel(char c) { return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; }

static inline bool is_nice(str_t str)
{
    str_t naughty_strings[] = {SLICE("ab"), SLICE("cd"), SLICE("pq"), SLICE("xy")};
    for (size_t i = 0; i < sizeof(naughty_strings) / sizeof(str_t); i++)
    {
        if (str_contains(str, naughty_strings[i])) return false;
    }

    size_t vowels = 0, duplicates = 0;
    const char* prev = NULL;

    for (const char* c = str_begin(str); c != str_end(str); c++)
    {
        vowels += is_vowel(*c);

        if (prev)
        {
            duplicates += *prev == *c;
        }

        prev = c;
    }

    return vowels >= 3 && duplicates > 0;
}

SolverResult solve_2015_day_05_part_1(str_t input)
{
    uint32_t nice_strings = 0;

    str_t line;
    StrSpliterator it = str_lines(input);
    while (str_split_next(&it, &line))
    {
        nice_strings += is_nice(line);
    }

    return (SolverResult){
        .type = RESULT_UNSIGNED_INT,
        .value.unsigned_int = nice_strings,
    };
}

// Don't ask me how this thing works..
static bool is_nice_v2(str_t str)
{
    HashSet seen_pairs = hashset_new(sizeof(char[2]), hashmap_default_options());

    bool seen_pair_twice = false;
    bool seen_triplet = false;
    bool prev_same = false;

    for (size_t i = 0; i < str.length - 1; i++)
    {
        seen_triplet |= i < str.length - 2 && str_at(str, i) == str_at(str, i + 2);

        if (!seen_pair_twice)
        {
            if (str_at(str, i) == str_at(str, i + 1))
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

            if (hashset_contains(seen_pairs, &str.data[i]))
            {
                seen_pair_twice = true;
            }

            hashset_insert(&seen_pairs, &str.data[i]);
        }

        if (seen_triplet && seen_pair_twice)
        {
            hashset_destroy(seen_pairs);
            return true;
        }
    }

    hashset_destroy(seen_pairs);

    return false;
}

SolverResult solve_2015_day_05_part_2(str_t input)
{
    uint32_t nice_strings = 0;

    str_t line;
    StrSpliterator it = str_lines(input);
    while (str_split_next(&it, &line))
    {
        nice_strings += is_nice_v2(line);
    }

    return (SolverResult){
        .type = RESULT_UNSIGNED_INT,
        .value.unsigned_int = nice_strings,
    };
}