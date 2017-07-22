#include <memory>
#include "./beta.h"

exp_ptr beta_reduction::operator()(exp_ptr exp){
  auto tmp = exp;
  int cnt = 0;
  do{
    stop = true;
    std::cout << cnt++ << ": " << tmp->to_string() << std::endl;
    tmp = step(tmp);
  }while(!stop);
  return tmp;
}

exp_ptr beta_reduction::step(exp_ptr exp){
  switch(exp->type){
    case expression::VAR:
      return exp;
      break;
    case expression::ABST:
      {
        auto abst = std::dynamic_pointer_cast<abstraction>(exp);
        return std::make_shared<abstraction>(abst->symbol,step(abst->M));
        break;
      }
    case expression::APP:
      {
        auto app = std::dynamic_pointer_cast<application>(exp);
        if(app->M1->type==expression::ABST){
          auto abst = std::dynamic_pointer_cast<abstraction>(app->M1);
          return substitute(abst->M,abst->symbol,app->M2);
        }else{
          return std::make_shared<application>(step(app->M1),step(app->M2));
        }
        break;
      }
    default:
      std::cerr << "something wrong!" << std::endl;
      std::abort();
      break;
  }
}

exp_ptr beta_reduction::substitute(exp_ptr exp,const std::string &symbol,exp_ptr exp2){
  switch(exp->type){
    case expression::VAR:
      {
        auto var = std::dynamic_pointer_cast<variable>(exp);
        if(var -> symbol == symbol){
          stop = false;
          return exp2;
        }else{
          return var;
        }
        break;
      }
    case expression::ABST:
      {
        auto abst = std::dynamic_pointer_cast<abstraction>(exp);
        if(symbol == abst->symbol){ 
          return abst;
        }else{
          if(!free_occurance(exp2,abst->symbol)){
            return std::make_shared<abstraction>(abst->symbol,substitute(abst->M,symbol,exp2));
          }else{
            auto new_symbol = gensymbol();
            return std::make_shared<abstraction>(new_symbol,substitute(substitute(abst->M,abst->symbol,std::make_shared<variable>(new_symbol)),symbol,exp2));
          }
        }
      }
      break;
    case expression::APP:
      {
        auto app = std::dynamic_pointer_cast<application>(exp);
        return std::make_shared<application>(substitute(app->M1,symbol,exp2),substitute(app->M2,symbol,exp2));
        break;
      }
    default:
      std::cerr << "something wrong!" << std::endl;
      std::abort();
      break;
  }

}

bool beta_reduction::free_occurance(exp_ptr exp,const std::string &symbol){
  switch(exp->type){
    case expression::VAR:
      {
        auto var = std::dynamic_pointer_cast<variable>(exp);
        if(var -> symbol == symbol) return true;
        else false;
        break;
      }
    case expression::ABST:
      {
        auto abst = std::dynamic_pointer_cast<abstraction>(exp);
        if(abst -> symbol == symbol) return false;
        else return free_occurance(abst->M,symbol);
        break;
      }
    case expression::APP:
      {
        auto app = std::dynamic_pointer_cast<application>(exp);
        return free_occurance(app->M1,symbol) | free_occurance(app->M2,symbol);
      }
    default:
      std::cerr << "something wrong!" << std::endl;
      std::abort();
      break;
  }

}

std::string beta_reduction::gensymbol(){
  static int count = 0;
  return "d" + std::to_string(count++);
}

