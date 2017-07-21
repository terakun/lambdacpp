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
  // virtual expression* simplify(const std);
};

class variable : public expression{
  std::string var;
  public:
  variable(const std::string &var):expression(VAR),var(var){}
  std::string to_string()const{
    return var;
  }
  expression* simplify(){
    return this;
  }
};

class abstraction : public expression{
  std::string var;
  const expression *M;
  public:
  abstraction(const std::string &var,const expression *M):expression(ABST),var(var),M(M){}
  std::string to_string()const{
    return "\\" + var + "." + M->to_string();
  }
  expression* simplify(){

  }
};

class application : public expression{
  const expression *M1,*M2;
  public:
  application(const expression *M1,const expression *M2):expression(APP),M1(M1),M2(M2){}
  std::string to_string()const{
    return M1->to_string() + " " + M2->to_string();
  }
};

// expression* simpify(){

#endif
