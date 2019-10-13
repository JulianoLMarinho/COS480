#include "Block.h"
#include "Header.h"

#include<vector>

class Sorted
{
private:
  uint64_t pos;
  bool sorted;

public:
  Block *blockp;
  Block *blockg;
  Header* header;

  Sorted();
  ~Sorted();

  void flush();

  void ins(const char *string);
  void insMulti(const char **record, const int quant);
  const Record *sel(const char *cpf, bool toDelete=false);
  std::vector<const Record *>selMultiple(const char **cpfs, const int quant);
  std::vector<const Record *>selMultipleUHE(const char *uhe, bool toDelete=false);
  std::vector<const Record *>selRange(const char *cpfBegin, const char *cpfEnd);
  void del(const char *cpf);
  void delMultiUHE(const char *uhe);

  void sort();
};
