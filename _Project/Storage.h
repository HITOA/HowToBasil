#ifndef STORAGE_HEADER
#define STORAGE_HEADER

#include <cstddef>

#define STORAGE_MAGIC 0x43EFB12AU
#define MAX_ENTRY_COUNT 16

namespace Storage {

  struct StorageEntry {
    unsigned int name;
    size_t address;
    size_t size;
  };

  struct StorageHeader {
    unsigned int magic;
    unsigned int entryCount;
    StorageEntry entries[MAX_ENTRY_COUNT];
  };

  void Init();
  unsigned int GetEntryCount();
  bool Exists(const char* entryName);
  StorageEntry CreateEntry(const char* entryName, size_t size);
  StorageEntry OpenEntry(const char* entryName);
  bool DeleteEntry(const char* entryName);
  int Read(StorageEntry entry, char* data, size_t size);
  int Write(StorageEntry entry, char* data, size_t size);
  
}

#endif
