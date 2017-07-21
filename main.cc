#include <iostream>
#include "./parser.h"
#include "./expression.h"


int main(){
  variable x("x");
  variable y("y");
  application e1(&x,&y);
  abstraction e2("y",&e1);
  abstraction e3("x",&e2);
  application e4(&e3,&y);
  std::cout << e4.to_string() << std::endl;
  auto simplified_e4 = simplify(&e4);
  std::cout << simplified_e4->to_string() << std::endl;
    
  std::string str;
  parser p;
  while(std::cin >> str){
    p(str);
  }
  return 0;
}
