#ifndef AOC_HASH_H
#define AOC_HASH_H

#include "stdint.h"

int hash_djb2(void* data, size_t size);
void hash_md5(void* data, size_t size, uint8_t* result);

#endif