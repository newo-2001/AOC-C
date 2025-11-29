#ifndef AOC_HASHMAP_H
#define AOC_HASHMAP_H

#include <stddef.h>
#include <stdbool.h>

#include "../hash.h"

/// @brief A debug formatter for hashmap values.
/// To be with `hashmap_dbg`.
/// It should print a formatted version of `*data`.
typedef void HashMapDebugFormatter(const void* data, size_t size);

/// @brief A key comparer function for a hashmap.
/// To be used as `HashMapOptions::key_comparer`.
/// It should return `*a == *b`.
typedef bool HashMapKeyComparer(const void* a, const void* b, size_t key_size);

/// @brief A key-value-pair in a hashmap.
typedef struct HashMapEntry
{
    void* key;
    void* value;
} HashMapEntry;

/// @brief A HashMap entry.
typedef struct HashMapNode
{
    HashMapEntry entry;
    struct HashMapNode* next;
} HashMapNode;

/// @brief A hashmap acts as a key-value store backed by a hashing function.
/// This is a dynamic datastructure that can grow to accommodate for more data.
typedef struct HashMap
{
    size_t size;
    size_t key_size;
    size_t value_size;

    size_t bucket_count;
    HashMapNode** buckets;

    HashMapKeyComparer* key_comparer;
    HashFunction* hash_function;
} HashMap;

/// @brief Options to specify how a hashmap is to be created,
/// to be used with `hashmap_create_with_options`.
/// @param bucket_count The number of buckets to allocate.
/// @param key_comarer A function that determines if two keys are equal.
/// @param hash_function A function that hashes the keys.
typedef struct HashMapOptions
{
    size_t bucket_count;

    HashMapKeyComparer* key_comparer;
    HashFunction* hash_function;
} HashMapOptions;

/// @brief An iterator over a hashmap.
/// Created by `hashmap_begin`, to be used with `hashmap_next`.
typedef struct HashMapIter
{
    HashMap map;

    size_t bucket_index;
    HashMapNode* node;
} HashMapIter;

/// @return The default options for `hashmap_create`.
HashMapOptions hashmap_default_options();

/// @brief Create a new hashmap with the specified options.
/// @param key_size The size of the keys.
/// @param value_size The size of the values.
/// @param options The options to use during construction.
/// @return The newly created HashMap.
HashMap hashmap_create_with_options(size_t key_size, size_t value_size, HashMapOptions options);

/// @brief Creates a new hashmap with the default options.
/// @param key_size The size of the keys.
/// @param value_size The size of the values.
/// @return The newly created HashMap.
inline static HashMap hashmap_create(size_t key_size, size_t value_size)
{
    return hashmap_create_with_options(key_size, value_size, hashmap_default_options());
}

/// @brief Destory a hashmap, freeing the underlying resources.
/// @param map The map to be destroyed.
void hashmap_destroy(HashMap map);

/// @brief Inserts a key-value-pair into a hashmap.
/// @param map The map to insert into.
/// @param key A pointer to the key to insert.
/// @param value A pointer to the value to insert at the specified key.
/// @note If the key is already present in the map, it will be overridden.
void hashmap_insert(HashMap* map, const void* key, const void* value);

/// @brief Removes a given key from the hashmap.
/// @param map The map to remove the key from.
/// @param key A pointer to the key to be removed from the map.
/// @return Whether the key was found and removed from the map.
bool hashmap_remove(HashMap* map, const void* key);

/// @brief Gets the value for a given key in a hashmap.
/// @param map The hashmap to use.
/// @param key A pointer to the key for which the value should be looked up.
/// @return A pointer to the value at `key` or `NULL` if it is not found.
void* hashmap_get(HashMap map, const void* key);

/// @brief Creates an iterator over a hashmap, to be used with `hashmap_next`.
/// @param map The hashmap to iterate over.
/// @return An iterator that iterates over the hashmap.
/// @note Changing the hashmap in any way invalidates any existing iterator.
HashMapIter hashmap_iter(HashMap map);

/// @brief Advanced the hashmap iterator.
/// @param iter The hashmap iterator to advance.
/// @return The next element in the hashmap, or `NULL` if there is none.
HashMapEntry* hashmap_iter_next(HashMapIter* iter);

/// @brief Debug print the contents of a hashmap.
/// @param map The map to print.
/// @param key_formatter The formatting function for printing keys.
/// @param value_formatter The formatting function for printing values.
void hashmap_dbg(HashMap map, HashMapDebugFormatter key_formatter, HashMapDebugFormatter value_formatter);

/// @brief Debug formatter for printing binary data in hex.
/// To be used with `hashmap_dbg`.
void hashmap_dbg_fmt_hex(const void* data, size_t size);

/// @brief Debug formatter for printing `str_t` values.
/// To be used with `hashmap_dbg`.
void hashmap_dbg_fmt_str(const void* data, size_t size);

/// @brief Equality comparer for `str_t` values.
/// To be used as `HashMapOptions::key_comparer`
bool hashmap_eq_str(const void* a, const void* b, size_t key_size);

/// @brief Hash function for `str_t` values.
/// To be used as `HashMapOptions::hash_function`.
int hashmap_hash_str(const void* data, size_t size);

/// @brief Determines if a hashmap contains a given key.
/// @param map The hashmap to check for occupancy.
/// @param key The key to check for.
/// @return Whether `map` contains `key`.
static inline bool hashmap_contains_key(HashMap map, const void* key)
{
    return hashmap_get(map, key) != NULL;
}

/// @brief Return the size (or cardinality) of a hashmap.
/// @param map The map to determine the size of.
/// @return The number of items in the map.
static inline size_t hashmap_size(HashMap map)
{
    return map.size;
}

#endif