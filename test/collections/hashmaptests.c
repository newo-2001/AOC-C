#include <unity.h>

#include <aoc_lib/collections/hashmap.h>

void tearDown()
{
}

void setUp()
{
}

void test_new_hashmap_is_empty(void)
{
    HashMap map = hashmap_new(0, 0, hashmap_default_options());

    UNITY_TEST_ASSERT_EQUAL_UINT(0, hashmap_size(map), __LINE__, "Hashmap was not empty");

    hashmap_destroy(map);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_new_hashmap_is_empty);

    return UNITY_END();
}