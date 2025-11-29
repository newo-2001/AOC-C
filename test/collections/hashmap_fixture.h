#ifndef AOC_TESTS_HASHMAP_FIXTURE
#define AOC_TESTS_HASHMAP_FIXTURE

#include <aoc_lib/collections/hashmap.h>

int hash_identity(const void* data, size_t size);

HashMap create_single_bucket_map();

#endif