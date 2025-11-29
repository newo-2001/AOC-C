#include <unity.h>

#include <aoc_lib/slice.h>

void tearDown() {}
void setUp() {}

void test_stack_slice(void)
{
    int items[] = { 1, 2, 3 };
    slice_t slice = STACK_SLICE(int, items);

    int expectedLength = sizeof(items) / sizeof(int);
    TEST_ASSERT_EQUAL_INT_ARRAY(items, slice.data, expectedLength);
    TEST_ASSERT_EQUAL_size_t(expectedLength, slice.length);
    TEST_ASSERT_EQUAL_size_t(sizeof(int), slice.item_size);
}

void test_slice_iter(void)
{
    int items[] = { 1, 2 };
    slice_t slice = STACK_SLICE(int, items);

    int* it = slice_start(slice);

    TEST_ASSERT_EQUAL_INT(*it, 1);
    TEST_ASSERT_EQUAL(it, slice_start(slice));
    TEST_ASSERT_NOT_EQUAL(it, slice_end(slice));

    it = slice_next(slice, it);
    TEST_ASSERT_EQUAL_INT(*it, 2);
    TEST_ASSERT_NOT_EQUAL(it, slice_start(slice));
    TEST_ASSERT_NOT_EQUAL(it, slice_start(slice));

    it = slice_next(slice, it);
    TEST_ASSERT_NOT_EQUAL(it, slice_start(slice));
    TEST_ASSERT_EQUAL(it, slice_end(slice));
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_stack_slice);
    RUN_TEST(test_slice_iter);

    return UNITY_END();
}