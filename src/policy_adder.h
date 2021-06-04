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
    bool add_policy(string raw_policy); 
    bool monitor(sys_state st);
    



    //destructor: frees all the dynamically allocated memory 
    ~policy_engine();
};

class invariant_engine{
    vector<ast_node*> invariant_asts;
    vector<vector<pair<string,void*>>> corrective_actions;
    pltl_parser * formula_parser;
    vector<pltl_evaluator*> invariant_evaluators;
    vector<time_t> invariant_timers;

public:
    invariant_engine();
    bool add_invariant(string invariant, string actions);
    vector<pair<string,void*>> test_invariants(sys_state st);
    pair<string,void*> parse_action(string action_string);
    vector<string> split_string(string input, char delimiter);
    ~invariant_engine();
};

#endif 
