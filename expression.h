#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
#include <iostream>

class expression{
  public:
  enum type_e{
    VAR,
    ABST,
    APP
  }type;
  
  expression(type_e t):type(t){}
  virtual std::string to_string()const = 0;
  friend expression* simplify(expression*);
  friend expression* substitute(expression*,const std::string&,expression*);
};

class variable : public expression{
  public:
  std::string symbol;
  variable(const std::string &symbol):expression(VAR),symbol(symbol){}
  std::string to_string()const{
    return symbol;
  }
};

class abstraction : public expression{
  public:
  std::string symbol;
  expression *M;
  abstraction(const std::string &symbol,expression *M):expression(ABST),symbol(symbol),M(M){}
  std::string to_string()const{
    return "\\" + symbol + ".(" + M->to_string() + ")";
  }
};

class application : public expression{
  public:
  expression *M1,*M2;
  application(expression *M1,expression *M2):expression(APP),M1(M1),M2(M2){}
  std::string to_string()const{
    return M1->to_string() + " " + M2->to_string();
  }
};

bool free_occurance(expression *,const std::string &);
#endif
