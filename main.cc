#include <iostream>
#include "./parser.h"
#include "./expression.h"


int main(){
  variable s("s");
  variable z("z");
  abstraction e1("z",&z);
  abstraction zero("s",&e1);

  variable n("n");
  application e2(&n,&s);
  application e3(&e2,&z);
  application e4(&s,&e3);
  abstraction e5("z",&e4);
  abstraction e6("s",&e5);
  abstraction succ("n",&e6);
  application succzero(&succ,&zero);
  expression *exp = &succzero;
  std::cout << exp->to_string() << std::endl;
  char c;
  while(std::cin>>c&&c=='s'){
    exp = simplify(exp);
    std::cout << exp->to_string() << std::endl;
  }
    
  std::string str;
  parser p;
  while(std::cin >> str){
    p(str);
  }
  return 0;
}
