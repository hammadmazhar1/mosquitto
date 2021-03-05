# include "policy_adder.h"

    //constructor: creates a parser and initializes the other data-structures. 
policy_engine::policy_engine()
{
    error_message_without_return("entering constructor");
    formula_parser = (pltl_parser*) malloc(sizeof(pltl_parser)) ; 
    error_message_without_return("created formula parser");
    policy_asts.clear(); 
    error_message_without_return("cleared policy asts");
    policy_evaluators.clear(); 
    error_message_without_return("cleared evaluators");
}

bool policy_engine::add_policy(char * raw_policy)
{
    ast_node * fast = new ast_node() ;
    if(!fast)
    {
        fprintf(stderr,"couldn't allocate space for ast root inside add_policy <policy_adder.h>\n");
        return false; 
    }
        
    fast = formula_parser->parse_formula_to_ast(raw_policy, fast) ; 
    if(!fast){
        fprintf(stderr,"couldn't allocate space for ast root inside add_policy <policy_adder.h>\n");
        return false; 

    }
    policy_asts.push_back(fast) ; 
    int policy_size = formula_parser->getGlobalIndex();

    pltl_evaluator * peval = new pltl_evaluator(policy_size); 
    if(!peval)
    {
        fprintf(stderr,"Cannot allocate space for pltl evaluator inside add_policy <policy_adder.h>\n") ; 
        return false; 
    }
    policy_evaluators.push_back(peval) ; 

    assert(policy_evaluators.size() == policy_asts.size()); 

    return true ; 
}

bool policy_engine::monitor(sys_state st)
{
    std::size_t sz = policy_asts.size(); 
    for(std::size_t i = 0 ; i < sz ; ++i)
    {
        if(!policy_evaluators[i]->policy_check(policy_asts[i], &st)) return false;  
    }
    for(std::size_t i = 0 ; i < sz; ++i)
        policy_evaluators[i]->copy_policychecker_state(); 
    return true; 
}




    //destructor: frees all the dynamically allocated memory 
policy_engine::~policy_engine()
{
    free(formula_parser); 
    int sz = (int) policy_asts.size();
    for(int i = 0 ;i < sz ; ++i) free_tree(policy_asts[i]) ; 
    policy_asts.clear(); 
    for(int i = 0 ; i < sz; ++i) delete policy_evaluators[i];
    policy_evaluators.clear();  
}
