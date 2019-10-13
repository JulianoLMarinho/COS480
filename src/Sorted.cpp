#include "Sorted.h"

#include <iostream>
#include <cstring>
#include <list>
#include <math.h>

#define SORTED_DISK "Sorted.cbd"

Sorted::Sorted()
{
  const std::string dataFilename = SORTED_DISK;
  const std::string headerFilename = SORTED_DISK"h";
  this->blockp = new Block(dataFilename.c_str(), 'w');
  this->blockg = new Block(dataFilename.c_str(), 'r');
  this->header = new Header(headerFilename);
  this->sort();
  this->sorted = true;
}

Sorted::~Sorted()
{
  delete this->blockp;
  delete this->blockg;
}

void Sorted::flush()
{
  this->blockp->persist();
  this->header->write();
  if (this->sorted == false){
    std::cout<<"Chamei o sort()"<<std::endl;
    this->sort();
    std::cout<<"Saí do sort()"<<std::endl;
    this->sorted = true;
  }
}



void Sorted::ins(const char *string)
{
  const Record *record = new Record(string); // Initialize record to be inserted
  this->blockp->write(record);               // Write record in writing block
  this->sorted = false;
}

void Sorted::insMulti(const char **string, const int quant)
{
  for (int i = 0; i < quant; i++){
    ins(string[i]);
  }
}

const Record *Sorted::sel(const char *id, bool toDelete)
{
  if (!this->sorted) {
    this->sort();
    this->sorted = true;
  }
  int64_t start = 0;
  int64_t end = this->blockg->recordsInFile(SORTED_DISK)-1;
  const Record *record;
  do
  {
    int64_t middle = ceil(((end - start) / 2))+start;
    this->pos = this->blockg->read(Block::convertRecordPos2FilePos(middle));
    record = this->blockg->get(0);
    if(record->idcmp(id)){
      if (toDelete){
        // Replace the current register with 000's:
        this->blockg->nullify(0, Block::convertRecordPos2FilePos(middle), SORTED_DISK);
        std::cout << "Deleted";
      }
      else{
        std::cout<<"Found";
      }
      // Finishes printing:
      std::cout << " record " << *record << " in block position " << 0 << " line " << middle+1 << std::endl;
      return record;
    }
    for (int j = 0; j < sizeof(record->id); j++)
    {
      if (record->id[j] > id[j])
      {
        end = middle;
        break;
      }
      if (record->id[j] < id[j])
      {
        start = middle+1;
        break;
      }
    }
  } while (start != end);
  std::cout << "No record with id = " << id << std::endl;
  return nullptr;
}

std::vector<const Record *>Sorted::selMultiple(const char **ids, const int quant)
{
  std::vector<const Record*>foundRecords;
  for (int i = 0; i < quant; i++)
  {
    foundRecords.push_back(Sorted::sel(ids[i]));        
  }
  return foundRecords;
}

std::vector<const Record *>Sorted::selRange(const char *idBegin, const char *idEnd)
{
  this->pos = this->blockg->read(0);
  const Record *record;
  std::vector<const Record*>foundRecords;
  int found = 0;
  
  // do
  // {
  //   for (int i = 0; i < this->blockg->count(); i++)
  //   {
  //     record = this->blockg->get(i);
  //     for (int j = 0; j < sizeof(record->id); j++)
  //     {
  //       if (record->idinrange(idBegin, idEnd))
  //       {
  //         foundRecords.push_back(record);  
  //         found++;
  //         break;
  //       }
  //     }
  //   }
  // } while ((this->pos = this->blockg->read(this->pos)) > 0);
  // return foundRecords;
}

void Sorted::del(const char *id)
{
  // Seek and destroy:
  Sorted::sel(id, true);
}

void Sorted::sort() {
  std::string line;
  std::ifstream outputFile(SORTED_DISK, std::ios_base::in);
  std::list<Record> records;
  if (outputFile.is_open()) {
    while (std::getline(outputFile, line)){
      Record r(line.c_str());
      records.push_back(r);
    }
    outputFile.close();
  }
  records.sort();
  std::ofstream sortedOutputFile(SORTED_DISK, std::ios_base::out);
  for (std::list<Record>::iterator it = records.begin(); it != records.end(); it++) {
    sortedOutputFile << *it;
  }
}

std::vector<const Record *>Sorted::selMultipleUHE(const char *uhe, bool toDelete)
{
  this->pos = 0;
  const Record *record;
  std::vector<const Record *>foundRecords;
  int found = 0;
  do
  {
    int t = this->blockg->read(this->pos);

    for (int i = 0; i < this->blockg->count(); i++)
    {
      record = this->blockg->get(i);
      if(record->uhecmp(uhe))
      {
        foundRecords.push_back(record);
        found++;
        
        if (toDelete)
        {
          std::cout << " record " << *record << " in block position " << i << std::endl;
          // Replace the current register with 000's:
          this->blockg->nullify(i, this->pos, SORTED_DISK);
          std::cout << "Deleted" << std::endl;
        }
      }
    }
    this->pos = t == -1 ? 0 : t;
  } while (this->pos > 0);
  if (found > 0)
    std::cout << found << " records found " << std::endl;
  else
    std::cout << "Not all records found " << std::endl;
  return foundRecords;
}

void Sorted::delMultiUHE(const char *uhe)
{
  // Seek and destroy:
  Sorted::selMultipleUHE(uhe, true);
}