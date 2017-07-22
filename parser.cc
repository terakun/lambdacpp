#include <cassert>
#include "./parser.h"

/*

EXPRESSION = FACTOR FACTOR
| \SYMBOL->EXPRESSION
| SYMBOL

FACTOR = '(' EXPRESSION ')' | SYMBOL
 */
exp_ptr parser::operator()(const std::string &str){
  cur = 0;
  exp_str = str;
  exp = read_expression();
  return exp;
}

exp_ptr parser::read_factor(){
  if(exp_str[cur] != '(') return read_var();
  cur++;
  auto tmp = read_expression();
  assert(exp_str[cur] == ')');
  cur++;
  return tmp;
}

exp_ptr parser::read_expression(){
  exp_ptr e;
  exp_ptr tmp;
  while(cur < exp_str.length()&&exp_str[cur]!=')'){
    char c = exp_str[cur];
    if(c == '\\'){
      cur++;
      tmp = read_abst();
    }else if(isalpha(c)){
      tmp = read_var();
    }else if(c == ' '){
      cur++;
    }else if(c == '('){
      tmp = read_factor();
    }  
    if(tmp!=nullptr){
      if(e!=nullptr){
        e.reset(new application(e,tmp));
      }else{
        e = tmp;
      }
      tmp = nullptr;
    }
  }
  return e;
}

exp_ptr parser::read_var(){
  std::string symbol;
  while(cur<exp_str.size()&&isalpha(exp_str[cur])){
    symbol += exp_str[cur++];
  }
  return exp_ptr(new variable(symbol));
}

exp_ptr parser::read_abst(){
  std::string symbol;
  while(cur<exp_str.size()&&isalpha(exp_str[cur])){
    symbol += exp_str[cur++];
  }
  assert(exp_str[cur]=='-');
  cur++;
  assert(exp_str[cur]=='>');
  cur++;
  return exp_ptr(new abstraction(symbol,read_expression()));
}
