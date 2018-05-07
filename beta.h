#ifndef BETA_H
#define BETA_H
#include "./expression.h"

class beta_reduction{
  bool stop;
  int gencount;
  public:
  beta_reduction(){}
  exp_ptr operator()(exp_ptr);
  exp_ptr step(exp_ptr);
  exp_ptr substitute(exp_ptr,const std::string &,exp_ptr);
  bool free_occurance(exp_ptr,const std::string &);
  std::string gensymbol();
};

#endif
