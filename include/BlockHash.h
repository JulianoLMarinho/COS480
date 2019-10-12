#include "Record.h"
#include <stdint.h>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <algorithm>

typedef uint32_t uint32_t;

class BlockHash
{
private:
  
  const Record **records; // List of this->records
  uint32_t n_r;           // Number of this->records

  void reset();   // Empty this

public:
  std::list<Record> recordList;

  //std::fstream file;      // Disk file
  static const int64_t MAX_SIZE = 1075; // Size of block

  uint32_t blocks_used; // Number of hits

  BlockHash(const char *filename, const char mode); // Block constructor
  BlockHash();
  ~BlockHash();                                     // Block destructor

  const Record *get(const int idx); // Return ptr to idx record
  uint32_t count();                 // Return number of this->records
  void t(BlockHash& other);
  void write(const Record *r, const int pos=-1);     // Write Record r in this
  int read(const int offset); // Populate the block with N records starting from offset
  void nullify(int reg, int pos, const char* path); // Replaces register in registers[reg] with a bunch of 000's. Then writes to file in pos +- offset
  void persist(const int pos=-1); // Write this in disk file and reset this
};