#include <iostream>
#include "Bucket.h"
#include <iomanip>

 
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
    for (int i = 0; i < 100; i++){
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
    for (int i = 0; i < 100; i++){
        if(line.size() > 0 && line.find_first_not_of(' ') != std::string::npos){
            string bt = line.substr(blockSize*i+20, blockSize*(i+1)+20);
            if(blockSize*i+position > this->headerBucket->getNextEmptyPosition() || !(bt.find_first_not_of(' ') != std::string::npos)){
                break;
            }
            BlockHash *block = new BlockHash();
            this->readBlocks++;
            for (int j = 0; j < 25; j++){
                string l = bt.substr(j*47, (j+1)*47);
                if(!(l.find_first_not_of(' ') == std::string::npos)){
                    char recChar[l.length() +1 ];
                    strcpy(recChar, l.c_str());
                    Record *rec = new Record(recChar);
                    block->write(rec);
                }                
            };
            this->blocks.push_back(*block);      
        }        
    }
};//323 405-9939

void Bucket::write(BlockHash *bh)
{
    BlockHash b = BlockHash();
    bh->t(b);    
}

void Bucket::insertRecord(const Record *r){
    std::list<BlockHash>::iterator bh;
    bool skip = false;
    do{
        for(bh = this->blocks.begin(); bh != this->blocks.end(); ++bh){
            if(bh->recordList.size() < 25){
                this->headerBucket->getNextEmptyPosition(sizeof(Record));
                bh->recordList.push_back(*r);
                skip = true;
                break;
            }
        }
        if(skip) break;
        if(this->blocks.size() < 25) {
            BlockHash *b = new BlockHash();
            this->blocks.push_back(*b);
        }
    }while (this->blocks.size()<=25);   
}

void Bucket::persist(std::fstream &file, int pos){
    file.seekg(pos);
    file<<endl;
    file<<*this->headerBucket;
    // file<<"0000001,001,001,2017-01-01,000000000000000046.0";
    // file.fill(' ');
    // file.setf(std::ios_base::internal, std::ios_base::adjustfield);
    // file << std::setw(10);

    std::list<BlockHash>::iterator bh;
    for(bh = this->blocks.begin(); bh != this->blocks.end(); ++bh){
        file<<*bh;
    }
}