#include "storage.h"

#include <EEPROM.h>
#include "config.h"
#include "serial.h"
#include "hash.h"

Storage::StorageHeader header{ 0 };

void Storage::Init() {
  EEPROM.begin(EEPROM_MAX_SIZE);
  
  EEPROM.get(0, header);

  if (header.magic != STORAGE_MAGIC) {
     SERIAL_PRINTLN("Creating new storage header...");
     header.magic = STORAGE_MAGIC;
     header.entryCount = 0;
     EEPROM.put(0, header);
     EEPROM.commit();
  }else {
    SERIAL_PRINTLN("Storage found.");
  }
}

bool Storage::Exists(const char* entryName) {
  unsigned int hash = Hash::FNVHash32(entryName, strlen(entryName));
  for (size_t i = 0; i < header.entryCount; ++i) {
    if (header.entries[i].name == hash)
      return true;
  }
  return false;
}

unsigned int Storage::GetEntryCount() {
  return header.entryCount;
}

Storage::StorageEntry Storage::CreateEntry(const char* entryName, size_t size) {
  if (Exists(entryName))
    return OpenEntry(entryName);
    
  unsigned int hash = Hash::FNVHash32(entryName, strlen(entryName));

  StorageEntry newEntry{ 0 };
  newEntry.name = hash;
  newEntry.address = header.entries[header.entryCount - 1].address + header.entries[header.entryCount - 1].size;
  newEntry.size = size;

  header.entries[header.entryCount] = newEntry;
  ++header.entryCount;

  EEPROM.put(0, header);
  EEPROM.commit();

  return newEntry;
}

Storage::StorageEntry Storage::OpenEntry(const char* entryName) {
  unsigned int hash = Hash::FNVHash32(entryName, strlen(entryName));
  for (size_t i = 0; i < header.entryCount; ++i) {
    if (header.entries[i].name == hash)
      return header.entries[i];
  }
  return Storage::StorageEntry{ 0 };
}

bool Storage::DeleteEntry(const char* entryName) {
  if (!Exists(entryName))
    return true;

  unsigned int hash = Hash::FNVHash32(entryName, strlen(entryName));
  
  size_t entryIdx = 0;

  for (entryIdx = 0; entryIdx < header.entryCount; ++entryIdx) {
    if (header.entries[entryIdx].name == hash)
      break;
  }

  if (entryIdx == header.entryCount - 1) {
    --header.entryCount;
    EEPROM.put(0, header);
    EEPROM.commit();
    return true;
  }

  memcpy(&header.entries[entryIdx], &header.entries[entryIdx + 1], sizeof(StorageEntry) * (header.entryCount - entryIdx - 1));
  --header.entryCount;
  EEPROM.put(0, header);
  EEPROM.commit();
}

int Storage::Read(StorageEntry entry, char* data, size_t size) {
  if (size > entry.size) {
    for (size_t i = 0; i < entry.size; ++i)
      data[i] = EEPROM.read(entry.address + i);
    return entry.size;
  }else {
    for (size_t i = 0; i < size; ++i)
      data[i] = EEPROM.read(entry.address + i);
    return size;
  }
}

int Storage::Write(StorageEntry entry, char* data, size_t size) {
  if (size > entry.size) {
    for (size_t i = 0; i < entry.size; ++i)
      EEPROM.write(entry.address + i, data[i]);
    EEPROM.commit();
    return entry.size;
  }else {
    for (size_t i = 0; i < size; ++i)
      EEPROM.write(entry.address + i, data[i]);
    EEPROM.commit();
    return size;
  }
}
