#include <unity.h>

#include <aoc_lib/slice.h>

#define str_size(s) (sizeof(s) - 1)

void tearDown() {}
void setUp() {}

void test_slice_from_cstr(void)
{
    str_t str = SLICE("test");

    TEST_ASSERT_EQUAL_UINT(str_size("test"), str.length);
    TEST_ASSERT_EQUAL_MEMORY("test", str.data, str_size("test"));
}

void test_str_iterator(void)
{
    str_t str = SLICE("test");

    size_t i = 0;
    for (char* c = str_begin(str); c != str_end(str); c = str_next(c), i++)
    {
        TEST_ASSERT_EQUAL_CHAR(str.data[i], *c);
    }
}

void test_str_at(void) { TEST_ASSERT_EQUAL_CHAR('c', str_at(SLICE("abc"), 2)); }

void test_str_cmp(void)
{
    TEST_ASSERT_EQUAL_INT(0, str_cmp(SLICE("test"), SLICE("test")));
    TEST_ASSERT_LESS_THAN_INT(0, str_cmp(SLICE("abc"), SLICE("bc")));
    TEST_ASSERT_GREATER_THAN_INT(0, str_cmp(SLICE("bc"), SLICE("abc")));
}

void test_str_sub(void)
{
    str_t str = SLICE("hello world");
    str_t substr = str_sub(str, str_size("he"), str_size("hello"));

    TEST_ASSERT_EQUAL_UINT(str_size("llo"), substr.length);
    TEST_ASSERT_EQUAL_MEMORY("llo", substr.data, str_size("llo"));
}

void test_str_find(void)
{
    str_t str = SLICE("tseest");
    size_t offset;

    TEST_ASSERT_TRUE(str_find(str, SLICE("es"), &offset));
    TEST_ASSERT_EQUAL_size_t(str_size("tse"), offset);

    TEST_ASSERT_TRUE(str_find(str, SLICE(""), &offset));
    TEST_ASSERT_EQUAL_size_t(0, offset);

    TEST_ASSERT_TRUE(str_find(str, SLICE("tseest"), &offset));
    TEST_ASSERT_EQUAL_size_t(0, offset);

    TEST_ASSERT_FALSE(str_find(str, SLICE("te"), &offset));
    TEST_ASSERT_FALSE(str_find(str, SLICE("tseestt"), &offset));
}

void test_str_contains(void)
{
    TEST_ASSERT_TRUE(str_contains(SLICE("test"), SLICE("st")));
    TEST_ASSERT_FALSE(str_contains(SLICE("test"), SLICE("a")));
}

void test_str_split(void)
{
    str_t str = SLICE("My test string");
    str_t tokens[3] = {SLICE("My te"), SLICE(" "), SLICE("ring")};

    str_t token;
    StrSpliterator it = str_split(str, SLICE("st"));
    for (size_t i = 0; i < sizeof(tokens) / sizeof(str_t); i++)
    {
        str_t expected = tokens[i];

        TEST_ASSERT_TRUE(str_split_next(&it, &token));
        TEST_ASSERT_EQUAL_UINT(expected.length, token.length);
        TEST_ASSERT_EQUAL_MEMORY(expected.data, token.data, expected.length);
    }

    TEST_ASSERT_FALSE(str_split_next(&it, &token));
}

void test_str_lines(void)
{
    str_t str = SLICE("my\ntest\nstring");
    str_t lines[3] = {SLICE("my"), SLICE("test"), SLICE("string")};

    str_t line;
    StrSpliterator it = str_lines(str);
    for (size_t i = 0; i < sizeof(lines) / sizeof(str_t); i++)
    {
        str_t expected = lines[i];

        TEST_ASSERT_TRUE(str_split_next(&it, &line));
        TEST_ASSERT_EQUAL(expected.length, line.length);
        TEST_ASSERT_EQUAL_MEMORY(expected.data, line.data, expected.length);
    }

    TEST_ASSERT_FALSE(str_split_next(&it, &line));
}

void test_str_parse_int(void)
{
    int result;

    TEST_ASSERT_FALSE(str_parse_int(SLICE(""), &result));
    TEST_ASSERT_FALSE(str_parse_int(SLICE("x"), &result));
    TEST_ASSERT_FALSE(str_parse_int(SLICE("--1"), &result));
    TEST_ASSERT_FALSE(str_parse_int(SLICE("-"), &result));

    TEST_ASSERT_TRUE(str_parse_int(SLICE("150"), &result));
    TEST_ASSERT_EQUAL_INT(150, result);

    TEST_ASSERT_TRUE(str_parse_int(SLICE("-17"), &result));
    TEST_ASSERT_EQUAL(-17, result);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_slice_from_cstr);
    RUN_TEST(test_str_iterator);
    RUN_TEST(test_str_at);
    RUN_TEST(test_str_cmp);
    RUN_TEST(test_str_sub);
    RUN_TEST(test_str_find);
    RUN_TEST(test_str_contains);
    RUN_TEST(test_str_split);
    RUN_TEST(test_str_lines);
    RUN_TEST(test_str_parse_int);

    return UNITY_END();
}