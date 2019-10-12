#include <iostream>
#include <ostream>
#include <list>
#include <iterator>
#include "BlockHash.h"
#include "HeaderBucket.h"

using namespace std;

class Bucket
{
private:
    HeaderBucket * headerBucket;
    

public:
    std::list<BlockHash> blocks;
    int readBlocks = 0;
    int writeBlocks = 0;
    Bucket();
    Bucket(const char *filename, int position);
    Bucket(std::fstream &file, const char *filename, int position);
    Bucket(std::fstream &file, const char *filename, int position, HeaderBucket *header);
    ~Bucket();

    void write(BlockHash *bh);
    friend std::ostream &operator<<(std::ostream &out, Bucket &hb);

};