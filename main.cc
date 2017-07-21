#include <iostream>
#include "./parser.h"
#include "./expression.h"
#include "./beta.h"

int main(){
  variable s("s");
  variable z("z");
  application e0(&s,&z);
  abstraction e1("z",&e0);
  abstraction one("s",&e1);

  variable n("n");
  application e2(&n,&s);
  application e3(&e2,&z);
  application e4(&s,&e3);
  abstraction e5("z",&e4);
  abstraction e6("s",&e5);
  abstraction succ("n",&e6);
  application succzero(&succ,&one);
  expression *exp = &succzero;
  std::cout << exp->to_string() << std::endl;
  char c;
  beta_reduction beta;
  exp = beta(exp);
  std::cout << exp->to_string() << std::endl;
    
  std::string str;
  parser p;
  while(std::cin >> str){
    std::cout << beta(p(str))->to_string() << std::endl;
  }
  return 0;
}
