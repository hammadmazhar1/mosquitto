#ifndef __POLICYADDER_H__
#define __POLICYADDER_H__
# include "headers.h"
# include "ast_util.h"
# include "parser.h"
# include "evaluator.h"

class policy_engine
{
    vector<ast_node*> policy_asts ; 
    pltl_parser *formula_parser ; 
    vector<pltl_evaluator*> policy_evaluators ; 

public:
    //constructor: creates a parser and initializes the other data-structures. 
    policy_engine();
    bool add_policy(char * raw_policy);
    bool monitor(sys_state st);



    //destructor: frees all the dynamically allocated memory 
    ~policy_engine();
};



#endif 
