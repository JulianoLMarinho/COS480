#include <iostream>
#include <fstream>
#include <list>

#include "Heap.h"
#include "Sorted.h"
#include "Hash.h"

#define DATA_STRUCT Hash

using namespace std;

void printBlocks(DATA_STRUCT* db)
{
  cout << db->blockg->blocks_used << " read blocks used" << endl;
  cout << db->blockp->blocks_used << " write blocks used" << endl;
}

void initDb(DATA_STRUCT* db)
{
  string line;
  ifstream infile("../Data/csvreduzido.csv");
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
  db->ins("25,1 ,1  ,2017-01-01,46.05");
  db->flush();
  printBlocks(db);
}

void testInsertMult(DATA_STRUCT* db)
{
  const char **ids = (const char **)malloc(55);
  ids[0] = "20,1 ,1  ,2017-01-01,46.05";
  ids[1] = "21,1 ,1  ,2017-01-01,46.05";
  ids[2] = "22,1 ,1  ,2017-01-01,46.05";
  ids[3] = "23,1 ,1  ,2017-01-01,46.05";
  ids[4] = "24,1 ,1  ,2017-01-01,46.05";
  //db->insMulti(ids, 5);
  db->flush();
  printBlocks(db);
}

void testSelect(DATA_STRUCT* db)
{
  const char *id = " 1";
  db->sel(id);
  printBlocks(db);
}

void testSelectMultiple(DATA_STRUCT* db)
{
  const char **ids = (const char **)malloc(55);
  ids[0] = " 1";
  ids[1] = " 2";
  ids[2] = " 3";
  ids[3] = " 4";
  ids[4] = " 5";
  const std::vector<const Record *> records = db->selMultiple(ids, 5);
  for (int i = 0; i < records.size(); i++)
  {
    cout << "Registro " << i << ": " << records[i][0] << endl;
  }
  printBlocks(db);
}

void testSelectRange(DATA_STRUCT *db)
{
  const char *idBegin = " 1";
  const char *idEnd = "10";
  const std::vector<const Record *> records = db->selRange(idBegin, idEnd);
  for (int i = 0; i < records.size(); i++)
  {
    cout << "Registro " << i << ": " << records[i][0] << endl;
  }
  printBlocks(db);
}

void testSelectMultiUHE(DATA_STRUCT *db)
{
  const char *id = "20";
  // db->delMultiUHE(id);
  printBlocks(db);
  const char *idBegin = " 1";
  const char *idEnd = "10";
  //const std::vector<const Record *> records = db->selMultipleUHE(" 1");
  // for (int i = 0; i < records.size(); i++)
  // {
  //   cout << "Registro " << i << ": " << records[i][0] << endl;
  // }
  printBlocks(db);
}

void testDelMultiUHE(DATA_STRUCT *db)
{
  const char *uhe = " 1";
  //db->delMultiUHE(uhe);
  printBlocks(db);
}

void testDelete(DATA_STRUCT *db)
{
  const char *id = "20";
  db->del(id);
  printBlocks(db);
}

int main(int argc, char **argv)
{
  // g++ -I ../include/ Block.cpp Column.cpp  Header.cpp Heap.cpp Record.cpp Schema.cpp main.cpp -o main
  DATA_STRUCT db;

  // Init database
   initDb(&db);

  // Insert
  // testInsert(&db);
  // testInsertMult(&db);

  // Select
  // testSelect(&db);

  // Select multiple
  // testSelectMultiple(&db);

  // Select range
   testSelectRange(&db);
  // testSelectMultiUHE(&db);

  

  // Delete
  //testDelete(&db);
  //testSelect(&db);

  // testDelMultiUHE(&db);
}