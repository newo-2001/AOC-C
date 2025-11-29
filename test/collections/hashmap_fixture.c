#include "hashmap_fixture.h"

int hash_identity(const void* data, size_t data_size)
{
    (void) data_size;
    return *((int*) data);
}

HashMap create_single_bucket_map()
{
    HashMapOptions options;
    options.bucket_count = 1;
    options.hash_function = hash_identity;

    return hashmap_create_with_options(sizeof(int), sizeof(int), options);
}