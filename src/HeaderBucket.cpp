#include "HeaderBucket.h"
#include <iostream>
#include <iomanip>




HeaderBucket::HeaderBucket(const char *string, int position)
{
    std::string nextPosString(string, 10);
    if(!(string[4] == ' ')){
        this->nextEmptyPos = stoi(nextPosString);
    } else {
        this->nextEmptyPos = position+10;
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
    out.fill('0');
    out.setf(std::ios_base::internal, std::ios_base::adjustfield);
    out << std::setw(10) << hb.getNextEmptyPosition();
  return out;
}