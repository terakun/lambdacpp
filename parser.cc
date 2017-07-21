#include <cassert>
#include "./parser.h"


void parser::operator()(const std::string &str){
  cur = 0;
  exp_str = str;
  exp = get_expression();
}

expression* parser::get_expression(){
  while(cur < exp_str.length()){
    char c = exp_str[cur];
    cur++ ;
    if(c == '\\'){
      return get_abst();
    }else if(isalpha(c)){

    }else if(c == '('){
      return get_expression();
    }
  }
}

expression* parser::get_var(){
  std::string varname;
  while(isalpha(exp_str[cur])){
    varname += exp_str[cur++];
  }
  return new variable(varname);
}

expression* parser::get_abst(){
  std::string varname ;
  while(isalpha(exp_str[cur])){
    varname += exp_str[cur++];
  }
  assert(exp_str[cur]=='.');
  return new abstraction(varname,get_expression());
}

expression* parser::get_app(){
  auto M1 = get_expression();
  assert(exp_str[cur]==' ');
  auto M2 = get_expression();
  return new application(M1,M2);
}

