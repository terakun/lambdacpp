#include <iostream>
#include "./parser.h"
#include "./expression.h"


int main(){
  variable x("x");
  std::cout << x.to_string() << std::endl;
  std::cout << free_occurance(&x,"x") << std::endl;
  abstraction e1("x",&x);
  std::cout << e1.to_string() << std::endl;
  std::cout << free_occurance(&e1,"x") << std::endl;
  application e2(&x,&e1);
  std::cout << e2.to_string() << std::endl;
  std::cout << free_occurance(&e2,"x") << std::endl;
  return 0;
}
