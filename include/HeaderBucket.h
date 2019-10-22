#include <string>
#include <fstream>
#include <list>

class HeaderBucket
{
private:
  int nextEmptyPos;
  bool full = false;

public:
  HeaderBucket(const char *string, int position);
  HeaderBucket(std::string headerBucket, int position);
  ~HeaderBucket();

  int getNextEmptyPosition();
  int getNextEmptyPosition(int insertedObject);
  void removeElement(int sizeElement);
  int isFull();
  friend std::ostream &operator<<(std::ostream &out, HeaderBucket &hb);
};