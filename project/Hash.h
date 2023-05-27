#ifndef HASH_HEADER
#define HASH_HEADER

#include <cstddef>

#define FNV_PRIME_32 16777619U
#define FNV_OFFSET_BASIS_32 2166136261U

namespace Hash {
  
  unsigned int FNVHash32(const char* data, size_t size); //FNV-1a alternate algorithm

}

#endif
