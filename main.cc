#include <iostream>
#include "./parser.h"
#include "./expression.h"
#include "./beta.h"

int main(){
  std::string str;
  parser p;
  beta_reduction beta;
  while(std::getline(std::cin,str)){
    std::cout << beta(p(str))->to_string() << std::endl;
  }
  return 0;
}
