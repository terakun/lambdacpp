#include "./expression.h"

std::string gensymbol(){
  static int count = 0;
  return "g" + std::to_string(count++);
}
expression* simplify(expression* exp){
  switch(exp->type){
    case expression::VAR:
      return exp;
      break;
    case expression::ABST:
      {
        auto abst = dynamic_cast<abstraction*>(exp);
        return new abstraction(abst->var,simplify(abst->M));
        break;
      }
    case expression::APP:
      {
        auto app = dynamic_cast<application*>(exp);
        if(app->M1->type==expression::ABST){
          auto abst = dynamic_cast<abstraction*>(app->M1);
          return substitute(abst->M,abst->var,app->M2);
        }
        break;
      }
    default:
      std::cerr << "something wrong!" << std::endl;
      std::abort();
      break;
  }
}


expression* substitute(expression* exp,const std::string &varname,expression* exp2){
  switch(exp->type){
    case expression::VAR:
      {
        auto var = dynamic_cast<variable*>(exp);
        if(var -> var == varname){
          return exp2;
        }else{
          return var;
        }
        break;
      }
    case expression::ABST:
      {
        auto abst = dynamic_cast<abstraction*>(exp);
        auto new_varname = gensymbol();
        return new abstraction(new_varname,substitute(substitute(abst->M,abst->var,new variable(new_varname)),varname,exp2));
      }
      break;
    case expression::APP:
      {
        auto app = dynamic_cast<application*>(exp);
        return new application(substitute(app->M1,varname,exp2),substitute(app->M2,varname,exp2));
        break;
      }
    default:
      std::cerr << "something wrong!" << std::endl;
      std::abort();
      break;
  }
}
