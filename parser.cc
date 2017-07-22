#include <cassert>
#include "./parser.h"

/*

EXPRESSION = FACTOR FACTOR
| \SYMBOL->EXPRESSION
| SYMBOL

FACTOR = '(' EXPRESSION ')' | SYMBOL
 */
expression* parser::operator()(const std::string &str){
  cur = 0;
  exp_str = str;
  exp = read_expression();
  return exp;
}

expression* parser::read_factor(){
  if(exp_str[cur] != '(') return read_var();
  cur++;
  auto tmp = read_expression();
  assert(exp_str[cur] == ')');
  cur++;
  return tmp;
}

expression* parser::read_expression(){
  expression *e = nullptr;
  expression *tmp = nullptr;
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
        e = new application(e,tmp);
      }else{
        e = tmp;
      }
      tmp = nullptr;
    }
  }
  return e;
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
  assert(exp_str[cur]=='-');
  cur++;
  assert(exp_str[cur]=='>');
  cur++;
  return new abstraction(symbol,read_expression());
}
