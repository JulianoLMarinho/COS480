#include "Header.h"
#include "Bucket.h"

#include <vector>

class Hash
{
private:
  Header* header;
  uint64_t pos;
  std::hash<std::string> hashFunction;
  int readBlocks = 0;
  int writeBlocks = 0;

public:
  Hash();
  ~Hash();
  void ins(const char *string);
  void insMulti(const char **string, const int quant);
  void flush();
  std::vector<const Record *>selMultiple(const int *cpfs, const int quant);
  std::vector<const Record *>selUHE(int uhe, const int quant, bool toDelete);
  std::vector<const Record *>selRange(int begin, int end);
  const Record* sel(const char *cpf, bool toDelete=false);
  const Record* sel(int id, bool toDelete=false);
  void printBlocks();
  void del(const char *cpf);
  void delUHE(int uhe);
  int getPositionByHash(int hash);
  void initDb();
};
