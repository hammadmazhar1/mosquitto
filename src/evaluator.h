#ifndef __EVALUATOR_H__
#define __EVALUATOR_H__

# include "headers.h" 
# include "ast.h" 
# include "constate.h"
#include "system_state.h"

class pltl_evaluator
{
	int aSize ; 
	bool *oldState, *newState ; 
	int evalPos ; 
public:

	pltl_evaluator(int s);

	void copy_policychecker_state();
	
	bool eval_snap(ast_node * root, sys_state * snap);
	
	bool policy_check(ast_node * root, sys_state * snap);
		
};


#endif 
