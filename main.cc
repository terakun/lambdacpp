#include <iostream>
#include "./parser.h"
#include "./expression.h"


int main(){
  variable x("x");
  variable y("y");
  abstraction f("x",&x);
  application g(&f,&f);
  
  std::string str;
  while(std::cin >> str){

  }
  return 0;
}
