#include <iostream>
#include "./parser.h"
#include "./expression.h"


int main(){
  variable x("x");
  variable y("y");
  abstraction f("x",&x);
  application g(&f,&y);
  
  std::cout << g.to_string() << std::endl;
  auto simplified_g = simplify(&g);
  std::cout << simplified_g->to_string() << std::endl;
    
  std::string str;
  parser p;
  while(std::cin >> str){
    p(str);
  }
  return 0;
}
