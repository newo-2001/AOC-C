#include <unity.h>

#include <aoc_lib/str.h>

#define str_size(s) (sizeof(s) - 1)

void tearDown() {}
void setUp() {}

void test_slice_from_cstr(void)
{
    str_t str = STR_SLICE("test");

    TEST_ASSERT_EQUAL_UINT(str_size("test"), str.length);
    TEST_ASSERT_EQUAL_MEMORY("test", str.data, str_size("test"));
}

void test_str_iterator(void)
{
    str_t str = STR_SLICE("test");

    size_t i = 0;
    for (const char* c = str_begin(str); c != str_end(str); c = str_next(c), i++)
    {
        TEST_ASSERT_EQUAL_CHAR(str.data[i], *c);
    }
}

void test_str_at(void)
{
    TEST_ASSERT_EQUAL_CHAR('c', str_at(STR_SLICE("abc"), 2));
}

void test_str_cmp(void)
{
    TEST_ASSERT_EQUAL_INT(0, str_cmp(STR_SLICE("test"), STR_SLICE("test")));
    TEST_ASSERT_LESS_THAN_INT(0, str_cmp(STR_SLICE("abc"), STR_SLICE("bc")));
    TEST_ASSERT_GREATER_THAN_INT(0, str_cmp(STR_SLICE("bc"), STR_SLICE("abc")));
}

void test_str_sub(void)
{
    str_t str = STR_SLICE("hello world");
    str_t substr = str_sub(str, str_size("he"), str_size("hello"));

    TEST_ASSERT_EQUAL_UINT(str_size("llo"), substr.length);
    TEST_ASSERT_EQUAL_MEMORY("llo", substr.data, str_size("llo"));
}

void test_str_find(void)
{
    str_t str = STR_SLICE("tseest");
    size_t offset;

    TEST_ASSERT_TRUE(str_find(str, STR_SLICE("es"), &offset));
    TEST_ASSERT_EQUAL_size_t(str_size("tse"), offset);

    TEST_ASSERT_TRUE(str_find(str, STR_SLICE(""), &offset));
    TEST_ASSERT_EQUAL_size_t(0, offset);

    TEST_ASSERT_TRUE(str_find(str, STR_SLICE("tseest"), &offset));
    TEST_ASSERT_EQUAL_size_t(0, offset);

    TEST_ASSERT_FALSE(str_find(str, STR_SLICE("te"), &offset));
    TEST_ASSERT_FALSE(str_find(str, STR_SLICE("tseestt"), &offset));
}

void test_str_contains(void)
{
    TEST_ASSERT_TRUE(str_contains(STR_SLICE("test"), STR_SLICE("st")));
    TEST_ASSERT_FALSE(str_contains(STR_SLICE("test"), STR_SLICE("a")));
}

void test_str_starts_with(void)
{
    TEST_ASSERT_TRUE(str_starts_with(STR_SLICE("test"), STR_SLICE("test")));
    TEST_ASSERT_TRUE(str_starts_with(STR_SLICE("test"), STR_SLICE("te")));
    TEST_ASSERT_TRUE(str_starts_with(STR_SLICE("test"), STR_SLICE("")));
    TEST_ASSERT_FALSE(str_starts_with(STR_SLICE("test"), STR_SLICE("a")));
}

void test_str_ends_with(void)
{
    TEST_ASSERT_TRUE(str_ends_with(STR_SLICE("test"), STR_SLICE("test")));
    TEST_ASSERT_TRUE(str_ends_with(STR_SLICE("test"), STR_SLICE("st")));
    TEST_ASSERT_TRUE(str_ends_with(STR_SLICE("test"), STR_SLICE("")));
    TEST_ASSERT_FALSE(str_ends_with(STR_SLICE("test"), STR_SLICE("a")));
}

void test_str_split(void)
{
    str_t str = STR_SLICE("My test string");
    str_t tokens[3] = { STR_SLICE("My te"), STR_SLICE(" "), STR_SLICE("ring") };

    str_t token;
    StrSpliterator it = str_split(str, STR_SLICE("st"));
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
    str_t str = STR_SLICE("my\ntest\nstring");
    str_t lines[3] = { STR_SLICE("my"), STR_SLICE("test"), STR_SLICE("string") };

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

    TEST_ASSERT_FALSE(str_parse_int(STR_SLICE(""), &result));
    TEST_ASSERT_FALSE(str_parse_int(STR_SLICE("x"), &result));
    TEST_ASSERT_FALSE(str_parse_int(STR_SLICE("--1"), &result));
    TEST_ASSERT_FALSE(str_parse_int(STR_SLICE("-"), &result));

    TEST_ASSERT_TRUE(str_parse_int(STR_SLICE("150"), &result));
    TEST_ASSERT_EQUAL_INT(150, result);

    TEST_ASSERT_TRUE(str_parse_int(STR_SLICE("-17"), &result));
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
    RUN_TEST(test_str_starts_with);
    RUN_TEST(test_str_ends_with);
    RUN_TEST(test_str_split);
    RUN_TEST(test_str_lines);
    RUN_TEST(test_str_parse_int);

    return UNITY_END();
}