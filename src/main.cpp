#include <iostream>
#include <fstream>
#include <list>

#include "Heap.h"
#include "Sorted.h"
#include "Hash.h"

#define DATA_STRUCT Heap

using namespace std;

void printBlocks(DATA_STRUCT* db)
{
  cout << db->blockg->blocks_used << " read blocks used" << endl;
  cout << db->blockp->blocks_used << " write blocks used" << endl;
}

void initDb(DATA_STRUCT* db)
{
  string line;
  ifstream infile("../Data/FixedSize_csvreduzido.csv");
  getline(infile, line);
  if (infile.is_open())
  {
    while (getline(infile, line))
    {
      db->ins(line.c_str());
    }
    infile.close();
    db->flush();
  }
  printBlocks(db);
}

void testInsert(DATA_STRUCT* db)
{
  db->ins("0000025,001,001,2017-01-01,00000000000000046.05");
  db->flush();
  printBlocks(db);
}

void testInsertMult(DATA_STRUCT* db)
{
  const char **ids = (const char **)malloc(55);
  ids[0] = "0000020,001,001,2017-01-01,00000000000000046.05";
  ids[1] = "0000021,001,001,2017-01-01,00000000000000046.05";
  ids[2] = "0000022,001,001,2017-01-01,00000000000000046.05";
  ids[3] = "0000023,001,001,2017-01-01,00000000000000046.05";
  ids[4] = "0000024,001,001,2017-01-01,00000000000000046.05";
  db->insMulti(ids, 5);
  db->flush();
  printBlocks(db);
}

void testSelect(DATA_STRUCT* db)
{
  const char *id = "0000004";
  db->sel(id);
  printBlocks(db);
}

void testSelectMultiple(DATA_STRUCT* db)
{
  const char **ids = (const char **)malloc(55);
  ids[0] = "0000001";
  ids[1] = "0000002";
  ids[2] = "0000003";
  ids[3] = "0000004";
  ids[4] = "0000005";
  const std::vector<const Record *> records = db->selMultiple(ids, 5);
  for (int i = 0; i < records.size(); i++)
  {
    cout << "Registro " << i << ": " << records[i][0] << endl;
  }
  printBlocks(db);
}

void testSelectRange(DATA_STRUCT *db)
{
  const char *idBegin = "0000001";
  const char *idEnd = "0000010";
  const std::vector<const Record *> records = db->selRange(idBegin, idEnd);
  for (int i = 0; i < records.size(); i++)
  {
    cout << "Registro " << i << ": " << records[i][0] << endl;
  }
  printBlocks(db);
}

void testSelectMultiUHE(DATA_STRUCT *db)
{
  const std::vector<const Record *> records = db->selMultipleUHE(" 1");
  for (int i = 0; i < records.size(); i++)
  {
    cout << "Registro " << i << ": " << records[i][0] << endl;
  }
  printBlocks(db);
}

void testDelMultiUHE(DATA_STRUCT *db)
{
  const char *uhe = "001";
  db->delMultiUHE(uhe);
  printBlocks(db);
}

void testDelete(DATA_STRUCT *db)
{
  const char *id = "0000020";
  db->del(id);
  printBlocks(db);
}

int main(int argc, char **argv)
{
  // g++ -I ../include/ Block.cpp Column.cpp  Header.cpp Heap.cpp Record.cpp Schema.cpp main.cpp -o main
  DATA_STRUCT db;

  // Init database
  // initDb(&db);

  // Insert
  // testInsert(&db);
  // testInsertMult(&db);

  // Select
  // testSelect(&db);

  // Select multiple
  // testSelectMultiple(&db);

  // Select range
  // testSelectRange(&db);
  // testSelectMultiUHE(&db);

  

  // Delete
  //testDelete(&db);
  //testSelect(&db);

  testDelMultiUHE(&db);
}