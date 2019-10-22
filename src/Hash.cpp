#include "Hash.h"

#include <iostream>
#include <cstring>
#include <functional>

// using namespace std;
#define HASH_DISK "Hash.cbd"
#define BUCKET_NUMBERS 100
#define BLOCK_SIZE 1175
#define BLOCK_NUMBER 100

Hash::Hash()
{
  const std::string dataFilename = HASH_DISK;
  const std::string headerFilename = HASH_DISK "h";
  this->readBlocks = 0;
  this->writeBlocks = 0;
}

Hash::~Hash()
{

}

void Hash::ins(const char *string)
{
  const Record *record = new Record(string);
  char id[7];
  memcpy(id,record->id,7);
  id[7]='\0';
  std::string idString(id);
  int idInt = std::stoi(idString);
  //int hashPos = idInt % 10;//1000; //tamanho de record = 43
   // Retrieves file:
  std::fstream in(HASH_DISK, std::fstream::ate | std::fstream::in | std::fstream::out);
  // Fill remainder of file with null:
  int pos = getPositionByHash(idInt);
  while (in.tellg()< pos){
	  in <<  ' ';
  }
  // Goes to writing postiion:
  in.seekg(pos);
  in << std::endl;
  char * headerBucket = new char [20];
  in.read(headerBucket, 20);
  HeaderBucket *h = new HeaderBucket(headerBucket, pos + 1);
  //Bucket *b = new Bucket(in, HASH_DISK, pos + 1, h);
  if(h->isFull()){
    std::cout<<"O Bucket da posição "<<pos<<" está cheio. Record "<<*record<<" não inserido."<<std::endl;
  } else {
    in.seekg(h->getNextEmptyPosition(sizeof(Record)));
    in << *record;
    in.seekg(pos);
    in << std::endl;
    in << *h;
    this->writeBlocks++;
    //b->insertRecord(record);
  }
  // in.seekg(pos);
  // in<<endl;
  // in<<"teste";
  // std::cout<<h->getNextEmptyPosition()<<std::endl;
  // b->persist(in, pos);
  delete [] headerBucket;
  in.close();

}

int Hash::getPositionByHash(int idInt){
  int hashPos = idInt % BUCKET_NUMBERS;
  return hashPos + 20 + BLOCK_SIZE*BLOCK_NUMBER*hashPos;
}

void Hash::flush()
{
  // this->blockp->persist();
}

const Record* Hash::sel(const char *id, bool toDelete)
{
  std::string idString(id);
  int idInt = std::stoi(idString);
  // int hashPos = idInt % 10;
  return this->sel(idInt, toDelete);
}

const Record* Hash::sel(int id, bool toDelete)
{
  // int hashPos = idInt % 10;
  int pos = getPositionByHash(id);
  bool found = false;
  std::fstream file(HASH_DISK, std::fstream::ate | std::fstream::in | std::fstream::out);
  Bucket * bck = new Bucket(file, HASH_DISK, pos+1);
  std::list<BlockHash>::iterator it;
  for (it = bck->blocks.begin(); it != bck->blocks.end(); ++it)
  {
    std::list<Record>::iterator rec;
    for (rec = it->recordList.begin(); rec != it->recordList.end(); ++rec){
      rec->id[7]='\0';
      std::string idStringTeste(rec->id);
      this->readBlocks += bck->readBlocks;
      if(std::stoi(idStringTeste) == id){
        // std::cout<<"Found "<<*rec<<" "<<endl;
        if(toDelete){
          found = true;
          it->recordList.erase(rec);
          bck->headerBucket->removeElement(sizeof(Record));
          break;
        } else {
          return &(*rec);
        }
      }
    }
    if(found){
      break;
    }
  }
  if (found){
    bck->persist(file, pos);
    this->writeBlocks += bck->writeBlocks;
  }
  return nullptr;
}

std::vector<const Record *>Hash::selMultiple(const int *ids, const int quant)
{
  std::vector<const Record *>t;
  int found = 0;
  for (int n = 0; n < quant; n++)
  {
  const Record* rt = this->sel(ids[n], false);
      if(rt!=nullptr){
        t.push_back(rt);
      }
  }
  std::vector<const Record *>::iterator it;

  for(it=t.begin(); it != t.end(); ++it){
    std::cout<<**it<<std::endl;
  }
  return t;
}

std::vector<const Record *>Hash::selRange(int begin, int end)
{
  std::vector<const Record *> t;
  for(int i = begin; i<=end; i++){
    const Record* rt = this->sel(i, false);
      if(rt!=nullptr){
        t.push_back(rt);
      }
  }
  std::vector<const Record *>::iterator it;

  for(it=t.begin(); it != t.end(); ++it){
    std::cout<<**it<<std::endl;
  }
  return t;
}

std::vector<const Record *>Hash::selUHE(int uhe, const int quant, bool toDelete)
{
  this->readBlocks = 0;
  std::vector<const Record *>results;
  for(int i = 0; i < BLOCK_NUMBER; i++)
  {
    // int hashPos = idInt % 10;
    int pos = getPositionByHash(i);
    bool found = false;
    std::fstream file(HASH_DISK, std::fstream::ate | std::fstream::in | std::fstream::out);
    Bucket * bck = new Bucket(file, HASH_DISK, pos+1);
    this->readBlocks += bck->readBlocks;
    std::list<BlockHash>::iterator it;
    for (it = bck->blocks.begin(); it != bck->blocks.end(); ++it)
    {
      std::list<Record>::iterator rec;
      for (rec = it->recordList.begin(); rec != it->recordList.end(); ++rec){
        rec->UHE[3]='\0';
        
        // rec->id[7]='\0';
        std::string uheStringTeste(rec->UHE);
        if(std::stoi(uheStringTeste) == uhe){
          if(toDelete){
            found = true;
            rec = it->recordList.erase(rec);
            bck->headerBucket->removeElement(sizeof(Record));
            continue;
          }
          // std::cout<<"Found "<<*rec<<" "<<endl;
          results.push_back(&*rec);
        }
      }
    }
    if(toDelete && found){
      bck->persist(file, pos);
      this->writeBlocks += bck->writeBlocks;
    }
  }
  return results;
}

void Hash::del(const char *id)
{
  // Seek and destroy:oloo
  Hash::sel(id, true);
}

void Hash::delUHE(int uhe)
{
  // Seek and destroy:oloo
  Hash::selUHE(uhe, 0,true);
}

void Hash::initDb(){
  int j = (BLOCK_NUMBER*BLOCK_SIZE+20)*BUCKET_NUMBERS;
  std::fstream in(HASH_DISK);
  for(int i = 0; i<9999999; i++){
    in<<' ';
  }
  in.close();
}

void Hash::printBlocks(){
  std::cout<<this->readBlocks<<" blocos de leitura lidos"<<std::endl;
  std::cout<<this->writeBlocks<<" blcos de escrita escritos"<<std::endl;
  this->readBlocks = 0;
  this->writeBlocks = 0;
}

void Hash::insMulti(const char **string, const int quant)
{
  for (int i = 0; i < quant; i++){
    ins(string[i]);
  }
}
