#include <unity.h>

#include <aoc_lib/collections/hashmap.h>
#include <aoc_lib/slice.h>

void tearDown() {}
void setUp() {}

static HashMap new_str_map()
{
    HashMapOptions options = {
        .bucket_count = 3,
        .hash_function = hashmap_hash_str,
        .key_comparer = hashmap_eq_str,
    };

    return hashmap_new(sizeof(str_t), sizeof(str_t), options);
}

void test_new_hashmap_is_empty(void)
{
    HashMap map = hashmap_new(0, 0, hashmap_default_options());

    TEST_ASSERT_EQUAL_size_t(0, hashmap_size(map));

    hashmap_destroy(map);
}

void test_hashmap_doesnt_contain_invalid_key(void)
{
    HashMap map = hashmap_new(sizeof(int), sizeof(int), hashmap_default_options());
    int key = 1, value = 1;

    hashmap_insert(&map, &key, &value);
    key = 2;

    TEST_ASSERT_FALSE_MESSAGE(hashmap_contains_key(map, &key), "Hashmap contained unexpected key");

    hashmap_destroy(map);
}

void test_hashmap_contains_valid_key(void)
{
    HashMap map = hashmap_new(sizeof(int), sizeof(int), hashmap_default_options());
    int key = 1, value = 2;

    hashmap_insert(&map, &key, &value);
    TEST_ASSERT_TRUE_MESSAGE(hashmap_contains_key(map, &key), "Hashmap didn't contain expected key");
    TEST_ASSERT_EQUAL_INT(value, (*(int*)hashmap_get(map, &key)));

    hashmap_destroy(map);
}

void test_hashmap_contains_valid_string_key(void)
{
    HashMap map = new_str_map();
    str_t key = SLICE("test"), value = SLICE("string");

    hashmap_insert(&map, &key, &value);

    str_t lookup = SLICE("test");
    TEST_ASSERT_TRUE_MESSAGE(hashmap_contains_key(map, &lookup), "Hashmap didn't contain expected key");

    str_t actual = *((str_t*)hashmap_get(map, &lookup));
    TEST_ASSERT_EQUAL_size_t(value.length, actual.length);
    TEST_ASSERT_EQUAL_MEMORY(value.data, actual.data, value.length);

    hashmap_destroy(map);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_new_hashmap_is_empty);
    RUN_TEST(test_hashmap_doesnt_contain_invalid_key);
    RUN_TEST(test_hashmap_contains_valid_key);
    RUN_TEST(test_hashmap_contains_valid_string_key);

    return UNITY_END();
}