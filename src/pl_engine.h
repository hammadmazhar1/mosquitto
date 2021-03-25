#ifndef __PL_ENGINE_H__
#define __PL_ENGINE_H__
# include "headers.h"
# include "ast_util.h"
# include "system_state.h"

# include "pl_ast.h"
# include "pl_parser.h"
# include "pl_evaluator.h"

class pl_engine
{
    vector<pl_ast_node*> prop_asts ;
    vector<std::string> prop_names; 
    pl_parser *formula_parser ; 
    pl_evaluator* prop_evaluator ; 

public:
    //constructor: creates a parser and initializes the other data-structures. 
    pl_engine();
    bool add_prop( char * raw_prop, std::string prop_name);
    sys_state eval_props(system_state * old_state, system_state * new_state);
    bool add_prop_file(char* prop_file);


    //destructor: frees all the dynamically allocated memory 
    ~pl_engine();
};



#endif 