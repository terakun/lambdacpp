#ifndef BETA_H
#define BETA_H
#include "./expression.h"

class beta_reduction{
  bool stop;
  public:
  beta_reduction(){}
  expression* operator()(expression *);
  expression* step(expression*);
  expression* substitute(expression*,const std::string &,expression*);
  bool free_occurance(expression *,const std::string &);
  std::string gensymbol();
};

#endif
