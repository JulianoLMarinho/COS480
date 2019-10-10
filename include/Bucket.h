#include <iostream>
#include <list>
#include <iterator>
#include "BlockHash.h"
#include "HeaderBucket.h"

using namespace std;

class Bucket
{
private:
    list<BlockHash>blocks;
    HeaderBucket headerBucket;

public:
    Bucket(int position);
    ~Bucket();

    friend ostream &operator<<(ostream &out, Bucket &hb);

};