#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>

class expression{};

class variable : public expression{
  std::string var;
};

class abstraction : public expression{
  std::string var;
  expression *M;
}

class application : public expression{
  expression *M1,*M2;
}


#endif
