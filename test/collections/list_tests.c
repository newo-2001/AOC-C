#include <unity.h>

#include <aoc_lib/collections/list.h>

void tearDown() {}
void setUp() {}

void test_new_list_is_empty(void)
{
    List list = list_create(sizeof(char));
    TEST_ASSERT_EQUAL_size_t(0, list.size);
    list_destroy(list);
}

void test_list_reserve_exact(void)
{
    List list = list_create(sizeof(char));

    list_reserve_exact(&list, 25);
    TEST_ASSERT_EQUAL_size_t(25, list.capacity);

    list_reserve_exact(&list, 2);
    TEST_ASSERT_EQUAL_size_t(2, list.capacity);

    list_destroy(list);
}

void test_list_append(void)
{
    List list = list_create(sizeof(int));

    int originalItems[] = { 1, 2 };
    list_append(&list, STACK_SLICE(int, originalItems));

    int newItems[] = { 3, 4 };
    list_append(&list, STACK_SLICE(int, newItems));

    int expectedItems[] = { 1, 2, 3, 4 };
    size_t expectedLength = sizeof(expectedItems) / sizeof(int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expectedItems, list.data, expectedLength);
    TEST_ASSERT_EQUAL_size_t(expectedLength, list.size);

    list_destroy(list);
}

void test_list_push_get(void)
{
    List list = list_create(sizeof(int));

    int item = 2;
    list_push(&list, &item);

    TEST_ASSERT_EQUAL_INT(*((int*) list_get(list, 0)), 2);

    list_destroy(list);
}

void test_list_as_array(void)
{
    List list = list_create(sizeof(int));

    int items[] = { 1, 2 };
    list_append(&list, STACK_SLICE(int, items));

    slice_t slice = list_as_slice(list);

    int expectedLength = sizeof(items) / sizeof(int);
    TEST_ASSERT_EQUAL_INT_ARRAY(items, slice.data, expectedLength);
    TEST_ASSERT_EQUAL_size_t(expectedLength, slice.length);
    TEST_ASSERT_EQUAL_size_t(sizeof(int), slice.item_size);

    list_destroy(list);
}

void test_list_iter(void)
{
    int items[] = { 1, 2 };
    List list = list_create(sizeof(int));
    list_append(&list, STACK_SLICE(int, items));

    int* it = list_start(list);

    TEST_ASSERT_EQUAL_INT(*it, 1);
    TEST_ASSERT_EQUAL(it, list_start(list));
    TEST_ASSERT_NOT_EQUAL(it, list_end(list));

    it = list_next(list, it);
    TEST_ASSERT_EQUAL_INT(*it, 2);
    TEST_ASSERT_NOT_EQUAL(it, list_start(list));
    TEST_ASSERT_NOT_EQUAL(it, list_start(list));

    it = list_next(list, it);
    TEST_ASSERT_NOT_EQUAL(it, list_start(list));
    TEST_ASSERT_EQUAL(it, list_end(list));

    list_destroy(list);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_new_list_is_empty);
    RUN_TEST(test_list_reserve_exact);
    RUN_TEST(test_list_append);
    RUN_TEST(test_list_push_get);
    RUN_TEST(test_list_as_array);
    RUN_TEST(test_list_iter);

    return UNITY_END();
}