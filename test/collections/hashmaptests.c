#include <unity.h>

#include <aoc_lib/collections/hashmap.h>

void tearDown() {}
void setUp() {}

static HashMap new_str_map()
{
    HashMapOptions options = {
        .bucket_count = 3,
        .hash_function = hashmap_str_hash,
        .key_comparer = hashmap_str_eq
    };

    return hashmap_new(sizeof(const char*), sizeof(const char*), options);
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
    const char *key = "test", *value = "string";

    hashmap_insert(&map, &key, &value);
    
    const char* lookup = "test";
    TEST_ASSERT_TRUE_MESSAGE(hashmap_contains_key(map, &lookup), "Hashmap didn't contain expected key");

    const char* actual = *((const char**) hashmap_get(map, &lookup));
    TEST_ASSERT_EQUAL_STRING(value, actual);

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