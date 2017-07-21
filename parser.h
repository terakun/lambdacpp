#ifndef PARSER_H
#define PARSER_H
#include "./expression.h"

class parser{
  expression *exp;
  int cur;
  std::string exp_str;

  expression* read_expression();
  expression* read_var();
  expression* read_abst();

  public:
  parser(){}
  expression* operator()(const std::string &); 
  expression* get_exp(){ return exp; }
};


#endif
