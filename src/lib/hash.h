#ifndef AOC_HASH_H
#define AOC_HASH_H

#include "stddef.h"
#include "stdint.h"

typedef int HashFunction(const void* data, size_t size);

int hash_djb2(const void* data, size_t size);
void hash_md5(const void* data, size_t size, uint8_t* result);

#endif