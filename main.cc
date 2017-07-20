#include <iostream>

int main(){
  std::string str;
  parser p;
  while(std::cin >> str){
    p(str);
    std::cout << p.to_string() << std::endl;
  }
  return 0;
}
