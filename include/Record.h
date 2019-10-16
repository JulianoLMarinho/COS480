#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <iostream>
#include <cstring>

class Record
{
private:
  size_t csvcpy(char *dst, const char *src, size_t start, size_t sz);
public:
  char UHE[3], id[7]; //ALTERAR DE ACORDO COM O TAMANHO  DO ID NO
  char Cenario[3], Estagio[10];
  // char Geracao[20];
  char Geracao[];

  Record(const char string[]);
  bool idcmp(const char *id) const;
  bool uhecmp(const char *uhe) const;
  bool idinrange(const char *id1, const char *id2) const;

  friend std::ostream &operator<<(std::ostream &out, const Record &r);
  bool operator<(const Record &r) const;
};

#endif