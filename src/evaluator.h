#ifndef __EVALUATOR_H__
#define __EVALUATOR_H__

# include "headers.h" 
# include "ast.h" 
# include "constate.h"

class pltl_evaluator
{
	int aSize ; 
	bool *oldState, *newState ; 
	int evalPos ; 
public:

	pltl_evaluator(int s)
	{
		aSize = s ; 
		oldState = new bool[aSize] ; 
		newState = new bool[aSize] ; 
		evalPos = 0 ; 

		for(int i=0;i<aSize;++i)
			oldState[i]=false;
	}

	void copy_policychecker_state()
	{
		for(int i = 0; i < aSize; ++i)
			oldState[i] = newState[i] ; 
	}


bool eval_snap(ast_node * root, sys_state * snap)
	{
		switch(root->nType)
		{

			case LTRUE:  return newState[root->aIndex]=true;
			case LFALSE: return newState[root->aIndex]=false;
			case prop:   return newState[root->aIndex]  = snap->isTrue(std::string(root->nValue)) ; 
			case LAND:
			{
				ast_node *c1 = root->children[0] ; 
				ast_node *c2 = root->children[1] ; 
				bool r1 = eval_snap(c1, snap);
				bool r2 = eval_snap(c2, snap);
				return newState[root->aIndex] = r1 && r2 ; 
			}
			case LOR:
			{
				ast_node *c1 = root->children[0] ; 
				ast_node *c2 = root->children[1] ; 
				bool r1 = eval_snap(c1, snap);
				bool r2 = eval_snap(c2, snap);
				return newState[root->aIndex] = r1 || r2 ; 
			}
			case LIMPLY:
			{
				ast_node *c1 = root->children[0] ; 
				ast_node *c2 = root->children[1] ; 
				bool r1 = eval_snap(c1, snap);
				bool r2 = eval_snap(c2, snap);
				if(r1) return newState[root->aIndex] = r2 ; 
				else return newState[root->aIndex] = true; 
				//return newState[root->aIndex] = (!r1) || r2 ; 

			}
			case since:
			{
				ast_node *c1 = root->children[0] ; 
				ast_node *c2 = root->children[1] ; 
				bool r1 = eval_snap(c1, snap);
				bool r2 = eval_snap(c2, snap);
				return newState[root->aIndex] = r2 || (oldState[root->aIndex] && r1) ;
 

			}
			case yesterday:
			{
				ast_node *c1 = root->children[0] ; 
				bool r1 = eval_snap(c1, snap); 
				if(evalPos <= 0) return newState[root->aIndex] = false ; 
				return newState[root->aIndex] = oldState[c1->aIndex] ; 

			}
			case historically:
			{
				ast_node *c1 = root->children[0] ; 
				bool r1 = eval_snap(c1, snap); 
				if(evalPos==0) return newState[root->aIndex] = r1 ; 
				return newState[root->aIndex] = oldState[root->aIndex] && r1;

			}
			case once:
			{
				ast_node *c1 = root->children[0] ; 
				bool r1 = eval_snap(c1, snap); 
				return newState[root->aIndex] = oldState[root->aIndex] || r1;
			}
			case LNOT:
			{
				ast_node *c1 = root->children[0] ; 
				bool r1 = eval_snap(c1, snap); 
				return newState[root->aIndex] = ! r1;
			} 
			default:
			{
				assert(0);
				return false; 
			}

		}
	}

	bool policy_check(ast_node * root, sys_state* snap){
		bool f = eval_snap(root,snap);
		if(f) ++evalPos ; 
		return f; 
	}
		
};


#endif 
