#ifndef AOC_HASHSET_H
#define AOC_HASHSET_H

#include "hashmap.h"

/// @brief A set that contains unique elements.
/// Uniqueness is determined by hashing and comparing the elements.
/// This is a dynamic datastructure that can grow to accommodate for more data.
typedef struct HashSet
{
    HashMap map;
} HashSet;

/// @brief Options to specify how a HashSet is to be created,
/// to be used with `hashset_create_with_options`.
/// @param bucket_count The number of buckets to allocate.
/// @param key_comarer A function that determines if two keys are equal.
/// @param hash_function A function that hashes the keys.
typedef struct HashMapOptions HashSetOptions;

/// @return The default options for `hashset_create`.
inline static HashSetOptions hashset_default_options()
{
    return hashmap_default_options();
}

/// @brief Create a new hashset with the specified options.
/// @param item_size The size of the items.
/// @param options The options to use during construction.
/// @return The newly created hashset.
inline static HashSet hashset_create_with_options(size_t item_size, HashSetOptions options)
{
    return (HashSet) { .map = hashmap_create_with_options(item_size, 0, options) };
}

/// @brief Creates a new hashset with the default options.
/// @param item_size The size of the items.
/// @return The newly created hashset.
inline static HashSet hashset_create(size_t item_size)
{
    return hashset_create_with_options(item_size, hashset_default_options());
}

/// @brief Destory a hashset, freeing the underlying resources.
/// @param set The hashset to be destroyed.
inline static void hashset_destroy(HashSet set)
{
    hashmap_destroy(set.map);
}

/// @brief Return the size (or cardinality) of a hashset.
/// @param set The set to determine the size of.
/// @return The number of items in the set.
inline static size_t hashset_size(HashSet set)
{
    return hashmap_size(set.map);
}

/// @brief Inserts an item into a hashset.
/// @param set The set to insert into.
/// @param item A pointer to the item to insert.
/// @note If the item is already present in the set, nothing happens.
inline static void hashset_insert(HashSet* set, const void* item)
{
    hashmap_insert(&set->map, item, NULL);
}

/// @brief Removes a given item from the hashset.
/// @param set The set to remove the item from.
/// @param item A pointer to the item to be removed from the set.
/// @return Whether the item was found and removed from the set.
inline static bool hashset_remove(HashSet* set, const void* item)
{
    return hashmap_remove(&set->map, item);
}

/// @brief Determines if a hashset contains a given item.
/// @param set The hashset to check for occupancy.
/// @param item The item to check for.
/// @return Whether `set` contains `item`.
inline static bool hashset_contains(HashSet set, const void* item)
{
    return hashmap_contains_key(set.map, item);
}

#endif
