#include <iostream>
#include "Bucket.h"
 
using namespace std;

Bucket::Bucket()
{

}

Bucket::Bucket(const char *filename, int position)
{
    std::fstream file(filename, std::fstream::ate | std::fstream::in | std::fstream::out);
    file.seekp(position);
    position = position + 20;
    std::string line;
    getline(file, line);
    this->headerBucket = new HeaderBucket(line.substr(0, 20), position);
    // 29375 bucket size in disk
    // 1175 block size in disk
    // 100 blocks in a bucket
    int blockSize = 1175;
    for (int i = 0; i < 10; i++){
        string bt = line.substr(blockSize*i+20, blockSize*(i+1)+20);
        BlockHash *block = new BlockHash();
        this->readBlocks++;
        for (int j = 0; j < 25; j++){
            string l = bt.substr(j*47, (j+1)*47);
            char recChar[l.length() +1 ];
            strcpy(recChar, l.c_str());
            Record *rec = new Record(recChar);
            block->write(rec);
        };
        this->blocks.push_back(*block);      
    }
};//323 405-9939

Bucket::Bucket(std::fstream &file, const char *filename, int position)
{
    file.seekp(position);
    position = position + 20;
    std::string line;
    getline(file, line);
    this->headerBucket = new HeaderBucket(line.substr(0, 20), position);
    // 29375 bucket size in disk
    // 1175 block size in disk
    // 100 blocks in a bucket
    int blockSize = 1175;
    for (int i = 0; i < 10; i++){
        string bt = line.substr(blockSize*i+20, blockSize*(i+1)+20);
        if(blockSize*i+position > this->headerBucket->getNextEmptyPosition()){
            break;
        }
        BlockHash *block = new BlockHash();
        this->readBlocks++;
        for (int j = 0; j < 25; j++){
            string l = bt.substr(j*47, (j+1)*47);
            char recChar[l.length() +1 ];
            strcpy(recChar, l.c_str());
            Record *rec = new Record(recChar);
            block->write(rec);
        };
        this->blocks.push_back(*block);      
    }
};//323 405-9939

Bucket::Bucket(std::fstream &file, const char *filename, int position, HeaderBucket *header)
{
    file.seekp(position);
    position = position + 20;
    std::string line;
    getline(file, line);
    this->headerBucket = header;
    // 29375 bucket size in disk
    // 1175 block size in disk
    // 100 blocks in a bucket
    int blockSize = 1175;
    for (int i = 0; i < 10; i++){
        string bt = line.substr(blockSize*i+20, blockSize*(i+1)+20);
        if(blockSize*i+position > this->headerBucket->getNextEmptyPosition()){
            break;
        }
        BlockHash *block = new BlockHash();
        this->readBlocks++;
        for (int j = 0; j < 25; j++){
            string l = bt.substr(j*47, (j+1)*47);
            char recChar[l.length() +1 ];
            strcpy(recChar, l.c_str());
            Record *rec = new Record(recChar);
            block->write(rec);
        };
        this->blocks.push_back(*block);      
    }
};//323 405-9939

void Bucket::write(BlockHash *bh)
{
    BlockHash b = BlockHash();
    bh->t(b);
    
}