#include <unity.h>

#include <aoc_lib/geometry.h>

void tearDown() {}
void setUp() {}

void test_unit_vectors(void)
{
    Direction directions[4] = { DIR_NORTH, DIR_EAST, DIR_SOUTH, DIR_WEST };
    Vec2 unit_vectors[4] = { { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 } };

    for (size_t i = 0; i < 4; i++)
    {
        Vec2 actual = dir_unit_vec(directions[i]);
        TEST_ASSERT_EQUAL_MEMORY(&unit_vectors[i], &actual, sizeof(Vec2));
    }
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_unit_vectors);

    return UNITY_END();
}