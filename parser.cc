#include <cassert>
#include "./parser.h"

expression* parser::operator()(const std::string &str){
  cur = 0;
  exp_str = str;
  exp = read_expression();
  return exp;
}

expression* parser::read_expression(){
  expression *tmp;
  while(cur < exp_str.length()){
    char c = exp_str[cur];
    // std::cout << c << std::endl;
    if(c == '\\'){
      cur++;
      return read_abst();
    }else if(isalpha(c)){
      tmp = read_var();
    }else if(c == '('){
      cur++;
      tmp = read_expression();
      assert(exp_str[cur]==')');
      cur++;
    }else if(c == ' '){
      cur++;
      return new application(tmp,read_expression());
    }else if(c == ')'){
      return tmp;
    }
  }
  return tmp;
}

expression* parser::read_var(){
  std::string symbol;
  while(cur<exp_str.size()&&isalpha(exp_str[cur])){
    symbol += exp_str[cur++];
  }
  return new variable(symbol);
}

expression* parser::read_abst(){
  std::string symbol;
  while(cur<exp_str.size()&&isalpha(exp_str[cur])){
    symbol += exp_str[cur++];
  }
  assert(exp_str[cur]=='.');
  cur++;
  return new abstraction(symbol,read_expression());
}

expression* parser::read_app(){
  auto M1 = read_expression();
  assert(exp_str[cur]==' ');
  auto M2 = read_expression();
  return new application(M1,M2);
}

