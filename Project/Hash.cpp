#include "Hash.h"

unsigned int Hash::FNVHash32(const char* data, size_t size) {
  unsigned int hash = FNV_OFFSET_BASIS_32;
  for (size_t i = 0; i < size; ++i) {
    hash ^= data[i];
    hash *= FNV_PRIME_32;
  }
  return hash;
}
