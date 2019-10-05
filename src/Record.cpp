#include "Record.h"


std::ostream &print(std::ostream &out, const char *str, size_t sz)
{
  for (size_t i = 0; i < sz; i++)
  {
    out << str[i];
    // printf("%c", str[i]);
  }
  out << ',';
  return out;
  // printf("\n");
}

Record::Record(const char *string)
{
  std::cout<<"string"<<std::endl;
  std::cout<<string<<std::endl;
  int idx = 0;
  memcpy(this->id, string, sizeof(this->id));
  idx += sizeof(this->id) + 1;

  memcpy(this->UHE, string + idx, sizeof(this->UHE));
  idx += sizeof(this->UHE) + 1;
  
  memcpy(this->Cenario, string + idx, sizeof(this->Cenario));
  idx += sizeof(this->Cenario) + 1;

  //idx = this->csvcpy(this->Cenario, string, idx, sizeof(this->Cenario)) + 1;

  memcpy(this->Estagio, string + idx, sizeof(this->Estagio));
  idx += sizeof(this->Estagio) + 1;
  std::cout<<"Antes do stof"<<std::endl;
  std::cout<<string<<std::endl;
  std::cout<<idx<<std::endl;
  std::cout<<string + idx<<std::endl;
  std::cout<<this->id<<std::endl;
  std::cout<<this->UHE<<std::endl;
  std::cout<<this->Cenario<<std::endl;

  this->Geracao = std::stof(string + idx);
  std::cout<<"Depois do stof"<<std::endl;

}

std::ostream &operator<<(std::ostream &out, const Record &r)
{
  print(out, r.id, sizeof(r.id));
  print(out, r.UHE, sizeof(r.UHE));
  print(out, r.Cenario, sizeof(r.Cenario));
  print(out, r.Estagio, sizeof(r.Estagio));
  return out << r.Geracao << std::endl;
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
  for (int j = 0; j < 11; j++)
  {
    if (this->id[j] != id[j])
    {
      return false;
    }
  }
  return true;
}

bool Record::idinrange(const char *idBegin, const char *idEnd) const
{
  char id[3];
  memcpy(id,this->id,2);
  id[2]='\0';
  if (strcmp(id,idBegin)>0 && strcmp(id,idEnd)<0)
  {
    return true;
  }
  return false;
}