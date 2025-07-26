#include <unity.h>

#include <aoc_lib/collections/list.h>

void tearDown() {}
void setUp() {}

void test_new_list_is_empty(void)
{
    List list = list_new(sizeof(char));
    TEST_ASSERT_EQUAL_size_t(0, list.size);
    list_destroy(list);
}

void test_list_reserve_exact(void)
{
    List list = list_new_options(sizeof(char), list_default_options());

    list_reserve_exact(&list, 25);
    TEST_ASSERT_EQUAL_size_t(25, list.capacity);

    list_reserve_exact(&list, 3);
    TEST_ASSERT_EQUAL_size_t(3, list.capacity);

    list_destroy(list);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_new_list_is_empty);
    RUN_TEST(test_list_reserve_exact);

    return UNITY_END();
}