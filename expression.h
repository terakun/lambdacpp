#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
#include <iostream>

class expression{
  protected:
  enum type_e{
    VAR,
    ABST,
    APP
  }type;
  public:
  
  expression(type_e t):type(t){}
  virtual std::string to_string()const  = 0;
  friend expression* simplify(expression*);
  friend expression* substitute(expression*,const std::string&,expression*);
};

class variable : public expression{
  public:
  std::string var;
  variable(const std::string &var):expression(VAR),var(var){}
  std::string to_string()const{
    return var;
  }
};

class abstraction : public expression{
  public:
  std::string var;
  expression *M;
  abstraction(const std::string &var,expression *M):expression(ABST),var(var),M(M){}
  std::string to_string()const{
    return "\\" + var + "." + M->to_string();
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

#endif
