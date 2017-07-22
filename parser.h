#ifndef PARSER_H
#define PARSER_H
#include "./expression.h"

class parser{
  exp_ptr exp;
  int cur;
  std::string exp_str;

  exp_ptr read_expression();
  exp_ptr read_var();
  exp_ptr read_abst();

  public:
  parser(){}
  exp_ptr operator()(const std::string &); 
  exp_ptr get_exp(){ return exp; }
};


#endif
