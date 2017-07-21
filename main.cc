#include <iostream>
#include "./parser.h"
#include "./expression.h"
#include "./beta.h"

int main(){
  std::string str = "(\\x->x x)(\\x->x x)";
  parser p;
  beta_reduction beta;
  auto res = p(str);
  std::cout << res->to_string() << std::endl;
  // std::cout << beta(res)->to_string() << std::endl;
  // while(true){
  //   std::cout << "> " ;
  //   if(!std::getline(std::cin,str)) break;
  //   std::cout << beta(p(str))->to_string() << std::endl;
  // }
  std::cout << std::endl;
  return 0;
}
