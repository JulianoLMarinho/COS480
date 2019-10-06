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
  void insMulti(const char **record, const int quant);
  const Record *sel(const char *id, bool toDelete=false);
  std::vector<const Record *>selMultiple(const char **ids, const int quant);
  std::vector<const Record *>selMultipleUHE(const char *uhe);
  std::vector<const Record *>selRange(const char *idBegin, const char *idEnd);
  void del(const char *id);
};
