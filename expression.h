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
    return "\\" + symbol + "." + M->to_string() ;
  }
};

class application : public expression{
  public:
  expression *M1,*M2;
  application(expression *M1,expression *M2):expression(APP),M1(M1),M2(M2){}
  std::string to_string()const{
    std::string M1_str = M1->to_string();
    if(M1->type!=VAR){
      M1_str = "(" + M1_str + ")";
    }
    std::string M2_str = M2->to_string();
    if(M2->type!=VAR){
      M2_str = "(" + M2_str + ")";
    }

    return M1_str + " " + M2_str;
  }
};


#endif
