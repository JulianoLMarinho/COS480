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
  Bucket *b = new Bucket(in, HASH_DISK, pos + 1, h);
  if(h->isFull()){
    std::cout<<"O Bucket da posição "<<pos<<" está cheio. Record "<<*record<<" não inserido."<<std::endl;
  } else {
    in.seekg(h->getNextEmptyPosition(sizeof(Record)));
    in << *record;
    in.seekg(pos);
    in << std::endl;
    in << *h;
  }
  
  // std::cout<<h->getNextEmptyPosition()<<std::endl;

  delete [] headerBucket;

}

int Hash::getPositionByHash(int idInt){
  int hashPos = idInt % 10;
  return hashPos + 20 + 1175*100*hashPos;
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
      if(rec->id[0] == '0' && std::stoi(idStringTeste) == id){
        // std::cout<<"Found "<<*rec<<" "<<endl;
        // std::cout<<bck->readBlocks<<" blocks were lidos"<<std::endl;
        this->readBlocks += bck->readBlocks;
        return &(*rec);
      }
    }
    
    // bool found = 1;
    // for (int j = 0; j < sizeof(record->id); j++)
    // {
    //   if (record->id[j] != id[j])
    //   {
    //     found = 0;
    //     break;
    //   }
    // }
    // if (found)
    // {
    //   if (toDelete)
    //   {
    //     // Replace the current register with 000's:
    //     this->blockg->nullify(i, this->pos, HASH_DISK);
    //     std::cout << "Deleted";
    //   }
    //   else
    //   {
    //     std::cout << "Found";
    //   }
    //   // Finishes printing:
    //   std::cout << " record " << *record << " in block position " << this->pos << std::endl;
    //   return record;
    // }
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
  std::cout<<t.size()<<" Records were found"<<std::endl;
  std::cout<<this->readBlocks<<" read blocks"<<std::endl;
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
  std::cout<<t.size()<<" Records were found"<<std::endl;
  std::cout<<this->readBlocks<<" read blocks"<<std::endl;
  return t;
}

void Hash::del(const char *id)
{
  // Seek and destroy:oloo
  Hash::sel(id, true);
}
