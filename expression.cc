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
        return new abstraction(abst->symbol,simplify(abst->M));
        break;
      }
    case expression::APP:
      {
        auto app = dynamic_cast<application*>(exp);
        if(app->M1->type==expression::ABST){
          auto abst = dynamic_cast<abstraction*>(app->M1);
          return substitute(abst->M,abst->symbol,app->M2);
        }else{
          return new application(simplify(app->M1),simplify(app->M2));
        }
        break;
      }
    default:
      std::cerr << "something wrong!" << std::endl;
      std::abort();
      break;
  }
}

expression* substitute(expression* exp,const std::string &symbol,expression* exp2){
  switch(exp->type){
    case expression::VAR:
      {
        auto var = dynamic_cast<variable*>(exp);
        if(var -> symbol == symbol){
          return exp2;
        }else{
          return var;
        }
        break;
      }
    case expression::ABST:
      {
        auto abst = dynamic_cast<abstraction*>(exp);
        auto new_symbol = gensymbol();
        return new abstraction(new_symbol,substitute(substitute(abst->M,abst->symbol,new variable(new_symbol)),symbol,exp2));
      }
      break;
    case expression::APP:
      {
        auto app = dynamic_cast<application*>(exp);
        return new application(substitute(app->M1,symbol,exp2),substitute(app->M2,symbol,exp2));
        break;
      }
    default:
      std::cerr << "something wrong!" << std::endl;
      std::abort();
      break;
  }
}

bool free_occurance(expression *exp,const std::string &symbol){
  switch(exp->type){
    case expression::VAR:
      {
        auto var = dynamic_cast<variable*>(exp);
        if(var -> symbol == symbol) return true;
        break;
      }
    case expression::ABST:
      {
        auto abst = dynamic_cast<abstraction*>(exp);
        if(abst -> symbol == symbol) return false;
        else return free_occurance(abst->M,symbol);
        break;
      }
    case expression::APP:
      {
        auto app = dynamic_cast<application*>(exp);
        return free_occurance(app->M1,symbol) | free_occurance(app->M2,symbol);
      }
    default:
      std::cerr << "something wrong!" << std::endl;
      std::abort();
      break;
  }
}

