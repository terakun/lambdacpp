#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>

class expression{};

class variable : public expression{
  std::string var;
  public:
  variable(const std::string &var):var(var){}
};

class abstraction : public expression{
  std::string var;
  const expression *M;
  public:
  abstraction(const std::string &var,const expression *M):var(var),M(M){}
};

class application : public expression{
  const expression *M1,*M2;
  public:
  application(const expression *M1,const expression *M2):M1(M1),M2(M2){}
};



#endif
