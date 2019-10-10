#include "HeaderBucket.h"
#include <iostream>
#include <iomanip>




HeaderBucket::HeaderBucket(const char *string, int position)
{
    std::string nextPosString(string, 20);
    try{
        this->nextEmptyPos = stoi(nextPosString.substr(10, 10));
        this->full = (this->nextEmptyPos + 20) - position > 29375 ? true : false;
    } catch (...){
        this->nextEmptyPos = position+20;
        this->full = false;
    }
};

int HeaderBucket::getNextEmptyPosition() 
{
    // std::ostringstream ostr;
    // ostr.fill('0');
    // ostr.setf(std::ios_base::internal, std::ios_base::adjustfield);
    // ostr << std::setw(10) << this->nextEmptyPos;
    // std::cout << ostr.str() << std::endl;

    return this->nextEmptyPos;
}

int HeaderBucket::getNextEmptyPosition(int insertedObject) 
{
    int oldPos = this->nextEmptyPos + 0;
    this->nextEmptyPos = this->nextEmptyPos+insertedObject+4;
    return oldPos;
}

std::ostream &operator<<(std::ostream &out, HeaderBucket &hb)
{
    out << hb.isFull();
    out.fill('0');
    out.setf(std::ios_base::internal, std::ios_base::adjustfield);
    out << std::setw(9) << 0;
    out.fill('0');
    out.setf(std::ios_base::internal, std::ios_base::adjustfield);
    out << std::setw(10) << hb.getNextEmptyPosition();
  return out;
}

int HeaderBucket::isFull(){
    return this->full ? 1 : 0;
}