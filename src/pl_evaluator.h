#ifndef __PL_EVALUATOR_H__
#define __PL_EVALUATOR_H__

#include "pl_ast.h"
#include "system_state.h"
#include "constate.h"


class pl_evaluator
{

public:


	// void copy_policychecker_state();
	
	void* eval_snap(pl_ast_node * root, system_state * old_snap, system_state * new_snap, std::string* ret_type);
	
	bool prop_check(pl_ast_node * root, system_state* old_snap, system_state * new_snap);
		
};


#endif 
