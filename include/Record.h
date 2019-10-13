#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <iostream>
#include <cstring>

class Record
{
private:
  size_t csvcpy(char *dst, const char *src, size_t start, size_t sz);
// //UHE,Cenário,Estágio,Geração
// this->schema.addColumn(Column("UHE",          "CHAR"));
//     this->schema.addColumn(Column("Cenario",      "CHAR",   3));
//     this->schema.addColumn(Column("Estagio",      "CHAR",   10));
//     this->schema.addColumn(Column("Geracao",      "FLOAT"));
public:
  char UHE[3], id[7]; //ALTERAR DE ACORDO COM O TAMANHO  DO ID NO
  char Cenario[3], Estagio[10];
  char Geracao[20];

  const static int EXTRA_CHARACTERS_PER_LINE = 5;

  Record(const char string[]);
  bool idcmp(const char *id) const;
  bool uhecmp(const char *uhe) const;
  bool idinrange(const char *id1, const char *id2) const;

  friend std::ostream &operator<<(std::ostream &out, const Record &r);
  bool operator<(const Record &r) const;
};

#endif