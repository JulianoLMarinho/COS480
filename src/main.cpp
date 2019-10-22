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
  // cout << db->blockg->blocks_used << " read blocks used" << endl;
  // cout << db->blockp->blocks_used << " write blocks used" << endl;
}

void initDb(DATA_STRUCT* db)
{
  string line;
  ifstream infile("../Data/FixedSize_gh.csv");
  getline(infile, line);
  db->initDb();
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
  db->ins("5000000,001,001,2017-01-01,00000000000000046.05");
  db->flush();
  db->printBlocks();
}

void testInsertMult(DATA_STRUCT* db)
{
  const char **ids = (const char **)malloc(55);
  ids[0] = "5000002,001,001,2017-01-01,00000000000000046.05";
  ids[1] = "5000003,001,001,2017-01-01,00000000000000046.05";
  ids[2] = "5000004,001,001,2017-01-01,00000000000000046.05";
  ids[3] = "5000005,001,001,2017-01-01,00000000000000046.05";
  ids[4] = "5000006,001,001,2017-01-01,00000000000000046.05";
  db->insMulti(ids, 5);
  db->flush();
  db->printBlocks();
}

void testSelect(DATA_STRUCT* db)
{
  const char *id = "0001254";
  std::cout<<*db->sel(id)<<std::endl;;
  db->printBlocks();
}

void testSelectMultiple(DATA_STRUCT* db)
{
  int ids[5];
  ids[0] = 1;
  ids[1] = 542;
  ids[2] = 1230;
  ids[3] = 88;
  ids[4] = 52000;
  const std::vector<const Record *> records = db->selMultiple(ids, 5);
  for (int i = 0; i < records.size(); i++)
  {
    cout << "Registro " << i << ": " << records[i][0] << endl;
  }
  db->printBlocks();
}

void testSelectRange(DATA_STRUCT *db)
{
  int idBegin = 1;
  int idEnd = 1000;
  const std::vector<const Record *> records = db->selRange(idBegin, idEnd);
  for (int i = 0; i < records.size(); i++)
  {
    cout << "Registro " << i << ": " << records[i][0] << endl;
  }
  db->printBlocks();
}

void testSelectMultiUHE(DATA_STRUCT *db)
{
  const std::vector<const Record *> records = db->selUHE(1, 0, false);
  for (int i = 0; i < records.size(); i++)
  {
    cout << "Registro " << i << ": " << records[i][0] << endl;
  }
  db->printBlocks();
}

void testDelMultiUHE(DATA_STRUCT *db)
{
  int uhe = 1;
  db->delUHE(uhe);
  db->printBlocks();
}

void testDelete(DATA_STRUCT *db)
{
  const char *id = "0045202";
  db->del(id);
  db->printBlocks();
}

void testDeleteUHE(DATA_STRUCT *db)
{
  int uhe = 1;
  db->delUHE(uhe);
  db->printBlocks();
}

int main(int argc, char **argv)
{
  // g++ -I ../include/ Block.cpp Column.cpp  Header.cpp Heap.cpp Record.cpp Schema.cpp main.cpp -o main
  DATA_STRUCT db;

  // Init database
  // initDb(&db);

  // Insert
  // std::cout<<"Teste inserção de 1 registro"<<std::endl;
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
  // testDeleteUHE(&db);
  // testDelete(&db);
  // testSelect(&db);

  testDelMultiUHE(&db);
  return 1;
}