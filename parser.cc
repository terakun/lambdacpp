#include <cassert>
#include "./parser.h"

exp_ptr parser::operator()(const std::string &s){
  cur = 0;
  str = s;
  exp = read_expression();
  return exp;
}

exp_ptr parser::read_expression(){
  exp_ptr e;
  exp_ptr tmp;
  while(cur < str.length()&&str[cur]!=')'){
    char c = str[cur];
    switch(c){
      case '\\':
        cur++;
        tmp = read_abst();
        break;
      case ' ':
        cur++;
        break;
      case '(':
        cur++;
        tmp = read_expression();
        assert(str[cur] == ')');
        cur++;
        break;
      default:
        if(isalpha(c)){
          tmp = read_var();
        }else{
          std::cerr << "something wrong!" << std::endl;
          std::abort();
        }
        break;
    }

    if(tmp!=nullptr){
      if(e!=nullptr){
        e.reset(new application(e,tmp));
      }else{
        e = tmp;
      }
      tmp.reset();
    }
  }
  return e;
}

exp_ptr parser::read_var(){
  std::string symbol;
  while(cur<str.size()&&isalpha(str[cur])){
    symbol += str[cur++];
  }
  return std::make_shared<variable>(symbol);
}

exp_ptr parser::read_abst(){
  std::string symbol;
  while(cur<str.size()&&isalpha(str[cur])){
    symbol += str[cur++];
  }
  assert(str[cur]=='-');
  cur++;
  assert(str[cur]=='>');
  cur++;
  return std::make_shared<abstraction>(symbol,read_expression());
}

