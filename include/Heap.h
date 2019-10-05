#include "Block.h"
#include "Header.h"

#include <vector>

class Heap
{
private:
  uint64_t pos; // Reading block position in the file

public:
  Block *blockp;
  Block *blockg;
  Header* header;

  Heap();
  ~Heap();

  void flush();

  void ins(const char *record);
  const Record *sel(const char *id, bool toDelete=false);
  std::vector<const Record *>selMultiple(const char **ids, const int quant);
  std::vector<const Record *>selRange(const char *idBegin, const char *idEnd);
  void del(const char *id);
};
