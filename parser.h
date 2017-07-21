#ifndef PARSER_H
#define PARSER_H
#include "./expression.h"

class parser{
  expression *exp;
  int cur;
  std::string exp_str;
  public:
  parser(){}
  void operator()(const std::string &); 
  expression* get_expression();
  expression* get_var();
  expression* get_abst();
  expression* get_app();
};


#endif
