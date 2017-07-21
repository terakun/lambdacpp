#include <cassert>
#include "./parser.h"

expression* parser::operator()(const std::string &str){
  cur = 0;
  exp_str = str;
  exp = read_expression();
  return exp;
}

expression* parser::read_expression(){
  while(cur < exp_str.length()){
    char c = exp_str[cur];
    cur++ ;
    if(c == '\\'){
      return read_abst();
    }else if(isalpha(c)){
      read_var();
      if(exp_str[cur]==' '){

      }
    }else if(c == '('){
      return read_expression();
    }else if(c == ' '){
      
    }
  }
}

expression* parser::read_var(){
  std::string symbol;
  while(isalpha(exp_str[cur])){
    symbol += exp_str[cur++];
  }
  return new variable(symbol);
}

expression* parser::read_abst(){
  std::string symbol ;
  while(isalpha(exp_str[cur])){
    symbol += exp_str[cur++];
  }
  assert(exp_str[cur]=='.');
  return new abstraction(symbol,read_expression());
}

expression* parser::read_app(){
  auto M1 = read_expression();
  assert(exp_str[cur]==' ');
  auto M2 = read_expression();
  return new application(M1,M2);
}

