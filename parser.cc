#include <cassert>
#include "./parser.h"

expression* parser::operator()(const std::string &str){
  cur = 0;
  exp_str = str;
  exp = read_expression();
  return exp;
}

expression* parser::read_expression(){
  expression *tmp = nullptr;

  while(cur < exp_str.length()&&exp_str[cur]!=')'){
    char c = exp_str[cur];
    std::cout << c << " " << cur << std::endl;

    if(c == '\\'){
      cur++;
      tmp = read_abst();
    }else if(isalpha(c)){
      tmp = read_var();
    }else if(c == '('){
      cur++;
      tmp = read_expression();
    }else if(c == ' '){
      cur++;
    }

    if(cur < exp_str.length()&&exp_str[cur]!=')'&&tmp!=nullptr){
      std::cout << "tmp:" << tmp->to_string() << " tmp type:" << tmp->type << " " << exp_str[cur] << std::endl;
      return new application(tmp,read_expression());
    }
  }
  cur++;
  return tmp;
}

expression* parser::read_var(){
  std::string symbol;
  while(cur<exp_str.size()&&isalpha(exp_str[cur])){
    symbol += exp_str[cur++];
  }
  std::cout << "read_var:" << cur << std::endl;
  return new variable(symbol);
}

expression* parser::read_abst(){
  std::string symbol;
  while(cur<exp_str.size()&&isalpha(exp_str[cur])){
    symbol += exp_str[cur++];
  }
  assert(exp_str[cur]=='-');
  cur++;
  assert(exp_str[cur]=='>');
  cur++;
  return new abstraction(symbol,read_expression());
}
