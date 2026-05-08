#include <assert.h>

#include <aoc_lib/geometry.h>
#include <aoc_lib/collections/hashset.h>

#include "../solvers.h"

static inline Direction parse_direction(char direction)
{
    switch (direction)
    {
        case '^':
            return DIR_NORTH;
        case '>':
            return DIR_EAST;
        case 'v':
            return DIR_SOUTH;
        case '<':
            return DIR_WEST;
        default:
            assert(false);
            return 0;
    }
}

SolverResult solve_2015_day_03_part_1(str_t input)
{
    Vec2 position = { 0, 0 };
    HashSet visited = hashset_create(sizeof(Vec2));

    for (const char* c = str_begin(input); c != str_end(input); c++)
    {
        hashset_insert(&visited, &position);

        Direction direction = parse_direction(*c);
        position = vec2_addv(position, dir_unit_vec(direction));
    }

    size_t size = hashset_size(visited);
    hashset_destroy(visited);

    return (SolverResult) {
        .type = RESULT_UNSIGNED_INT,
        .value.unsigned_int = size,
    };
}

SolverResult solve_2015_day_03_part_2(str_t input)
{
    HashSet visited = hashset_create(sizeof(Vec2));
    Vec2 santa_pos = { 0, 0 };
    Vec2 robo_santa_pos = { 0, 0 };

    for (const char* c = str_begin(input); c != str_end(input); c++)
    {
        hashset_insert(&visited, &santa_pos);
        hashset_insert(&visited, &robo_santa_pos);

        santa_pos = vec2_addv(santa_pos, dir_unit_vec(parse_direction(*c)));

        if (c == str_end(input)) break;
        c++;

        robo_santa_pos = vec2_addv(robo_santa_pos, dir_unit_vec(parse_direction(*c)));
    }

    size_t size = hashset_size(visited);
    hashset_destroy(visited);

    return (SolverResult) { .type = RESULT_UNSIGNED_INT, .value.unsigned_int = size };
}