#include <iostream>
#include "./parser.h"
#include "./expression.h"
#include "./beta.h"

int main(){
  std::string str;
  parser p;
  beta_reduction beta;
  while(true){
    std::cout << "> " ;
    if(!std::getline(std::cin,str)) break;
    std::cout << beta(p(str))->to_string() << std::endl;
  }
  std::cout << std::endl;
  return 0;
}
