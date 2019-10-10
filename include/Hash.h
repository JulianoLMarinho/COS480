#include "BlockHash.h"
#include "Header.h"
#include "HeaderBucket.h"

#include <vector>

class Hash
{
private:
  Header* header;
  uint64_t pos;
  std::hash<std::string> hashFunction;

public:
  BlockHash *blockp;
  BlockHash *blockg;
  Hash();
  ~Hash();
  void ins(const char *string);
  void flush();
  std::vector<const Record *>selMultiple(const char **cpfs, const int quant);
  std::vector<const Record *>selRange(const char *cpfBegin, const char *cpfEnd);
  const Record *sel(const char *cpf, bool toDelete=false);
  void del(const char *cpf);
  int getPositionByHash(int hash);
};
