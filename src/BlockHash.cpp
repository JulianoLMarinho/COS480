#include "BlockHash.h"


BlockHash::BlockHash(const char *filename, const char mode)
{
  
}

BlockHash::BlockHash()
{
  this->reset();
}

BlockHash::~BlockHash()
{
  this->persist();      // Persists block in disk
  delete this->records; // Delete record array
  //this->file.close();   // Close opened file (disk)
}

const Record *BlockHash::get(const int idx)
{
  return this->records[idx];
}

uint32_t BlockHash::count()
{
  return this->n_r; // Return number of records in this
}

void BlockHash::write(const Record *r, const int pos)
{
  // if (sizeof(Record) * (this->n_r + 1) > BlockHash::MAX_SIZE || pos >= 0)
  // {                  // If block is full
  //   this->persist(pos); // Persists block in disk
  // }
  // this->records[this->n_r] = r; // Write record in records member
  this->recordList.push_back(*r);
  this->n_r++;                  // Increment number of records
}

int BlockHash::read(const int pos)
{
  this->blocks_used++;
  // std::cout << "Pos = " << pos << std::endl;
  this->reset();
  //this->file.seekg(pos);
  std::string line;
  // if (!std::getline(this->file, line))
  // {
  //   // std::cout << "error" << std::endl;
  //   if (this->file.eof())
  //     return 0;
  //   else
  //     return -1;
  // }
  // try {
  // } catch (...) {
  // }
}


void BlockHash::persist(const int pos)
{
  // this->blocks_used++; // Increment number of write blocks used
  // for (uint32_t i = 0; i < this->n_r; i++)
  // {                                    // For each record
  //   if (pos>=0){
  //     this->file.seekp(pos);
  //   }
  //   this->file << *(this->records[i]);  // Write this in disk
  //   delete this->records[i];           // Delete the block's record
  //   this->records[i] = nullptr;        // Set block's record pointer to null
  // }
  // this->file.flush(); // Reload file with new records
  // this->reset();    // Reset block
}

void BlockHash::reset()
{

  this->n_r = 0; 
}

// Replaces register in registers[reg] with a bunch of 000's. Then writes to file in pos +- offset:
void BlockHash::nullify(int reg, int pos, const char* path){
    // This is the null register that will replace the one we will delete:
    // const char allZeroChar[] = "0000000,000,000,0000-00-00,11111111111111";
    // Record *record = new Record(allZeroChar);
    // std::cout<<*record->Estagio<<std::endl;
    // delete (this->records[reg]);  // Frees space occupied by old record
    // this->records[reg] = record;  // Replaces that specific record with all 0, essentially deleting it

    // // Custom-persist block to file. We write the whole block, which includes the modified register:
    // std::fstream zeroFile;
    // zeroFile.open(path);
    // std::cout<<pos<<std::endl;
    // zeroFile.seekp(pos);  // pos was passed to us by the Select function so we know where to write
    // // Writes all records belonging to this block:
    // for (int i = 0; i < this->count(); i++){
    //     zeroFile << records[i][0];
    //     zeroFile.flush();
    // }
}

void BlockHash::t(BlockHash& other)
{
  other.recordList = this->recordList;
}
