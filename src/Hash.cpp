#include "Hash.h"

#include <iostream>
#include <cstring>
#include <functional>

// using namespace std;
#define HASH_DISK "Hash.cbd"

Hash::Hash()
{
  const std::string dataFilename = HASH_DISK;
  const std::string headerFilename = HASH_DISK "h";
  this->blockp = new Block(dataFilename.c_str(), 'o'); // Initialize writing block
  this->blockg = new Block(dataFilename.c_str(), 'r'); // Initialize reading block
  this->header = new Header(headerFilename);
}

Hash::~Hash()
{
  delete this->blockp;
  delete this->blockg;
}

void Hash::ins(const char *string)
{
  const Record *record = new Record(string);
  char id[7];
  memcpy(id,record->id,7);
  id[7]='\0';
  std::string idString(id);
  int idInt = std::stoi(idString);
  int hashPos = idInt % 10; //tamanho de record = 43
  // Retrieves file:
  std::fstream in(HASH_DISK, std::fstream::ate | std::fstream::in | std::fstream::out);
  // Fill remainder of file with null:
  int pos = hashPos + 1024*2*hashPos;
  while (in.tellg()< pos){
	  in <<  ' ';
  }
  



  // Goes to writing postiion:
  in.seekg(pos);
  in << std::endl;
  char * headerBucket = new char [10];
  in.read(headerBucket, 10);
  HeaderBucket *h = new HeaderBucket(headerBucket, pos + 1);

  
  in.seekg(h->getNextEmptyPosition(sizeof(Record)));
  in << *record;
  in.seekg(pos);
  in << std::endl;
  in << *h;
  std::cout<<h->getNextEmptyPosition()<<std::endl;

  delete [] headerBucket;

}

void Hash::flush()
{
  this->blockp->persist();
}

const Record *Hash::sel(const char *id, bool toDelete)
{
  std::string cpfString(id);
  this->pos = this->blockg->read(hashFunction(cpfString)/1000000000000000);
  std::cout<<cpfString<<std::endl<<hashFunction(cpfString)/1000000000000000<<std::endl;
  const Record *record;
  for (int i = 0; i < this->blockg->count(); i++)
  {
    record = this->blockg->get(i);
    bool found = 1;
    for (int j = 0; j < sizeof(record->id); j++)
    {
      if (record->id[j] != id[j])
      {
        found = 0;
        break;
      }
    }
    if (found)
    {
      if (toDelete)
      {
        // Replace the current register with 000's:
        this->blockg->nullify(i, this->pos, HASH_DISK);
        std::cout << "Deleted";
      }
      else
      {
        std::cout << "Found";
      }
      // Finishes printing:
      std::cout << " record " << *record << " in block position " << this->pos << std::endl;
      return record;
    }
  }
  std::cout << "No record with ID = " << id << std::endl;
  return nullptr;
}

std::vector<const Record *>Hash::selMultiple(const char **ids, const int quant)
{
  const Record *record;
  std::vector<const Record *>foundRecords;
  int found = 0;
  for (int n = 0; n < quant; n++)
  {
    std::string cpfString(ids[n]);
    this->pos = this->blockg->read(hashFunction(cpfString)/1000000000000000);
    for (int i = 0; i < this->blockg->count(); i++)
    {
      record = this->blockg->get(i);
      if (record->idcmp(ids[n]))
      {
        foundRecords.push_back(record);
        found++;
        break;
      }
    }
  }

  if(found > 0){
    std::cout << "All records found " << std::endl;
    return foundRecords;
  }
}

std::vector<const Record *>Hash::selRange(const char *idBegin, const char *idEnd)
{
  this->pos = this->blockg->read(0);
  const Record *record;
  std::vector<const Record *>foundRecords;
  int found = 0;
  do
  {
    for (int i = 0; i < this->blockg->count(); i++)
    {
      record = this->blockg->get(i);
      for (int j = 0; j < sizeof(record->id); j++)
      {
        if (record->idinrange(idBegin, idEnd))
        {
          foundRecords.push_back(record);
          found++;
          break;
        }
      }
    }
  } while ((this->pos = this->blockg->read(this->pos)) > 0);
  return foundRecords;
}

void Hash::del(const char *id)
{
  // Seek and destroy:oloo
  Hash::sel(id, true);
}
