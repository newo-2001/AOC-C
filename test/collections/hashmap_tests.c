#include <unity.h>

#include <aoc_lib/str.h>

#include "hashmap_fixture.h"

void tearDown() {}
void setUp() {}

static HashMap create_str_map()
{
    HashMapOptions options = {
        .bucket_count = 3,
        .hash_function = hashmap_hash_str,
        .key_comparer = hashmap_eq_str,
    };

    return hashmap_create_with_options(sizeof(str_t), sizeof(str_t), options);
}

void test_new_hashmap_is_empty(void)
{
    HashMap map = hashmap_create(0, 0);

    TEST_ASSERT_EQUAL_size_t(0, hashmap_size(map));

    hashmap_destroy(map);
}

void test_hashmap_doesnt_contain_invalid_key(void)
{
    HashMap map = hashmap_create(sizeof(int), sizeof(int));
    int key = 1, value = 1;

    hashmap_insert(&map, &key, &value);
    key = 2;

    TEST_ASSERT_FALSE_MESSAGE(hashmap_contains_key(map, &key), "Hashmap contained unexpected key");

    hashmap_destroy(map);
}

void test_hashmap_contains_valid_key(void)
{
    HashMap map = hashmap_create(sizeof(int), sizeof(int));
    int key = 1, value = 2;

    hashmap_insert(&map, &key, &value);
    TEST_ASSERT_TRUE_MESSAGE(hashmap_contains_key(map, &key), "Hashmap didn't contain expected key");
    TEST_ASSERT_EQUAL_INT(value, (*(int*) hashmap_get(map, &key)));

    hashmap_destroy(map);
}

void test_hashmap_contains_valid_string_key(void)
{
    HashMap map = create_str_map();
    str_t key = STR_SLICE("test"), value = STR_SLICE("string");

    hashmap_insert(&map, &key, &value);

    str_t lookup = STR_SLICE("test");
    TEST_ASSERT_TRUE_MESSAGE(hashmap_contains_key(map, &lookup), "Hashmap didn't contain expected key");

    str_t actual = *((str_t*) hashmap_get(map, &lookup));
    TEST_ASSERT_EQUAL_size_t(value.length, actual.length);
    TEST_ASSERT_EQUAL_MEMORY(value.data, actual.data, value.length);

    hashmap_destroy(map);
}

void test_hashmap_insert_existing_key(void)
{
    HashMap map = hashmap_create(sizeof(int), sizeof(int));

    int key = 1, value = 1;
    hashmap_insert(&map, &key, &value);

    value = 2;
    hashmap_insert(&map, &key, &value);

    int actual = *((int*) hashmap_get(map, &key));
    TEST_ASSERT_EQUAL_INT(value, actual);
    TEST_ASSERT_EQUAL_size_t(1, hashmap_size(map));

    hashmap_destroy(map);
}

void test_hashmap_insert_remove_single_bucket(void)
{
    HashMapOptions options = hashmap_default_options();
    options.bucket_count = 1;

    HashMap map = hashmap_create_with_options(sizeof(int), sizeof(int), options);

    int key = 1, value = 1;
    hashmap_insert(&map, &key, &value);

    key = 2, value = 2;
    hashmap_insert(&map, &key, &value);

    TEST_ASSERT_EQUAL_size_t(2, hashmap_size(map));

    key = 1;
    TEST_ASSERT_TRUE_MESSAGE(hashmap_remove(&map, &key), "Hashmap didn't contain expected key");
    TEST_ASSERT_FALSE_MESSAGE(hashmap_remove(&map, &key), "Hashmap contained unexpected key");

    hashmap_destroy(map);
}

void test_hashmap_insert_remove_multiple_buckets(void)
{
    HashMapOptions options = hashmap_default_options();
    options.hash_function = hash_identity;
    options.bucket_count = 2;

    HashMap map = hashmap_create_with_options(sizeof(int), sizeof(int), options);

    int key = 1, value = 1;
    hashmap_insert(&map, &key, &value);

    key = 2, value = 2;
    hashmap_insert(&map, &key, &value);

    TEST_ASSERT_EQUAL_size_t(2, hashmap_size(map));

    TEST_ASSERT_TRUE_MESSAGE(hashmap_remove(&map, &key), "Hashmap didn't contain expected key");
    TEST_ASSERT_EQUAL_size_t(1, hashmap_size(map));

    TEST_ASSERT_FALSE_MESSAGE(hashmap_remove(&map, &key), "Hashmap contained unexpected key");
    TEST_ASSERT_EQUAL_size_t(1, hashmap_size(map));

    hashmap_destroy(map);
}

void test_hashmap_iterate(void)
{
    HashMapOptions options = hashmap_default_options();
    options.hash_function = hash_identity;
    options.bucket_count = 3;

    HashMap map = hashmap_create_with_options(sizeof(int), sizeof(int), options);

    int key = 0, value = 1;
    hashmap_insert(&map, &key, &value);

    key = 2, value = 3;
    hashmap_insert(&map, &key, &value);

    HashMapIter iter = hashmap_iter(map);
    HashMapEntry* entry = hashmap_iter_next(&iter);
    TEST_ASSERT_EQUAL_INT(0, *((int*) entry->key));
    TEST_ASSERT_EQUAL_INT(1, *((int*) entry->value));
    TEST_ASSERT_NOT_EQUAL_HEX64(NULL, entry);

    entry = hashmap_iter_next(&iter);
    TEST_ASSERT_EQUAL_INT(2, *((int*) entry->key));
    TEST_ASSERT_EQUAL_INT(3, *((int*) entry->value));
    TEST_ASSERT_NOT_EQUAL_HEX64(NULL, entry);

    entry = hashmap_iter_next(&iter);
    TEST_ASSERT_EQUAL_HEX64(NULL, entry);

    hashmap_destroy(map);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_new_hashmap_is_empty);

    RUN_TEST(test_hashmap_doesnt_contain_invalid_key);
    RUN_TEST(test_hashmap_contains_valid_key);
    RUN_TEST(test_hashmap_contains_valid_string_key);

    RUN_TEST(test_hashmap_insert_existing_key);

    RUN_TEST(test_hashmap_insert_remove_single_bucket);
    RUN_TEST(test_hashmap_insert_remove_multiple_buckets);

    RUN_TEST(test_hashmap_iterate);

    return UNITY_END();
}