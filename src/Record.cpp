#include <iostream>
#include "Record.h"

using namespace std;

std::ostream &print(std::ostream &out, const char *str, size_t sz, bool comma = true)
{
  for (size_t i = 0; i < sz; i++)
  {
    out << str[i];
    // printf("%c", str[i]);
  }
  if(comma)
    out << ',';
  return out;
  // printf("\n");
}

Record::Record(const char *string)
{
  // cout<<"CRIANDO UM RECORD"<<endl;
  // cout<<"String = "<<string<<endl;
  int idx = 0;
  memcpy(this->id, string, sizeof(this->id));
  //this->id[sizeof(this->id)] = '\0';
  idx += sizeof(this->id) + 1;
  // cout<<"id = "<<this->id<<endl;

  memcpy(this->UHE, string + idx, sizeof(this->UHE));
  //this->UHE[sizeof(this->UHE)] = '\0';
  idx += sizeof(this->UHE) + 1; 
  // cout<<"UHE = "<<this->UHE<<endl;


  memcpy(this->Cenario, string + idx, sizeof(this->Cenario));
  //this->UHE[sizeof(this->UHE)] = '\0';
  idx += sizeof(this->Cenario) + 1;
  // cout<<"Cenario = "<<this->Cenario<<endl;

  memcpy(this->Estagio, string + idx, sizeof(this->Estagio));
  //this->Estagio[sizeof(this->Estagio)] = '\0';
  idx += sizeof(this->Estagio) + 1;
  // cout<<"Estagio = "<<this->Estagio<<endl;

  memcpy(this->Geracao, string + idx, sizeof(this->Geracao));
  // std::cout<<"Geracao = "<<this->Geracao<<std::endl;
}

std::ostream &operator<<(std::ostream &out, const Record &r)
{
  print(out, r.id, sizeof(r.id));
  print(out, r.UHE, sizeof(r.UHE));
  print(out, r.Cenario, sizeof(r.Cenario));
  print(out, r.Estagio, sizeof(r.Estagio));
  print(out, r.Geracao, sizeof(r.Geracao), false);
  return out<< std::endl; //pra hashtablefuncionar eu vou mudar isso pra não ter esse endl
}

bool Record::operator<(const Record &r) const
{
  // std::cout << this->cpf << " " << r.cpf << std::endl;
  for (int i = 0; i < sizeof(this->id); i++)
  {
    if (this->id[i] < r.id[i])
    {
      return true;
    }
  }
  return false;
  // return (this->cpf < r.cpf);
}

size_t Record::csvcpy(char *dst, const char *src, size_t start, size_t sz)
{
  size_t end = start;
  size_t idx = -1;
  for (; end < start + sz; end++)
  {
    // std::cout << end << "/" << src[end] << std::endl;
    if (src[end] == ',')
    {
      idx = end - start;
      memcpy(dst, src + start, idx);
      break;
    }
  }
  if (idx == -1)
    memcpy(dst, src + start, end - start);
  else
    memset(dst + idx, 0x00, sz - idx);
  return end;
}

bool Record::idcmp(const char *id) const
{
  for (int j = 0; j < sizeof(this->id); j++)
  {
    if (this->id[j] != id[j])
    {
      return false;
    }
  }
  return true;
}

bool Record::uhecmp(const char *UHE) const
{
  for (int j = 0; j < sizeof(this->UHE); j++)
  {
    if (this->UHE[j] != UHE[j])
    {
      return false;
    }
  }
  return true;
}

bool Record::idinrange(const char *idBegin, const char *idEnd) const
{
  char id[sizeof(this->id)];
  memcpy(id,this->id,sizeof(this->id));

  if (strcmp(id,idBegin)>=0 && strcmp(id,idEnd)<0)
  {
    return true;
  }
  return false;
}