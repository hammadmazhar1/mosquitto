#ifndef __EVALUATOR_H__
#define __EVALUATOR_H__

# include "headers.h" 
# include "ast.h" 
# include "traces.h" 

class pltl_evaluator
{
	int aSize ; 
	bool *oldState, *newState ; 
public:

	pltl_evaluator(int s)
	{
		aSize = s ; 
		oldState = new bool[aSize] ; 
		newState = new bool[aSize] ; 

		for(int i=0;i<aSize;++i)oldState[i]=false;
	}

	void copy_state(bool * dest, bool * src, int sz)
	{
		for(int i=0;i<sz;++i)dest[i]=src[i];
	}	

	bool eval(ast_node * root, trace * ctrace, int evalPos)
	{
		switch(root->nType)
		{

			case LTRUE:  return newState[root->aIndex]=true;
			case LFALSE: return newState[root->aIndex]=false;
			case prop:   return newState[root->aIndex]  = ctrace->isTrue(std::string(root->nValue), evalPos) ; 
			case LAND:
			{
				ast_node *c1 = root->children[0] ; 
				ast_node *c2 = root->children[1] ; 
				bool r1 = eval(c1, ctrace, evalPos);
				bool r2 = eval(c2, ctrace, evalPos);
				return newState[root->aIndex] = r1 && r2 ; 
			}
			case LOR:
			{
				ast_node *c1 = root->children[0] ; 
				ast_node *c2 = root->children[1] ; 
				bool r1 = eval(c1, ctrace, evalPos);
				bool r2 = eval(c2, ctrace, evalPos);
				return newState[root->aIndex] = r1 || r2 ; 
			}
			case LIMPLY:
			{
				ast_node *c1 = root->children[0] ; 
				ast_node *c2 = root->children[1] ; 
				bool r1 = eval(c1, ctrace, evalPos);
				bool r2 = eval(c2, ctrace, evalPos);
				if(r1) return newState[root->aIndex] = r2 ; 
				else return newState[root->aIndex] = true; 
				//return newState[root->aIndex] = (!r1) || r2 ; 

			}
			case since:
			{
				ast_node *c1 = root->children[0] ; 
				ast_node *c2 = root->children[1] ; 
				bool r1 = eval(c1, ctrace, evalPos);
				bool r2 = eval(c2, ctrace, evalPos);
				return newState[root->aIndex] = r2 || (oldState[root->aIndex] && r1) ;
 

			}
			case yesterday:
			{
				ast_node *c1 = root->children[0] ; 
				bool r1 = eval(c1, ctrace, evalPos); 
				if(evalPos <= 0) return newState[root->aIndex] = false ; 
				return newState[root->aIndex] = oldState[c1->aIndex] ; 

			}
			case historically:
			{
				ast_node *c1 = root->children[0] ; 
				bool r1 = eval(c1, ctrace, evalPos); 
				if(evalPos==0) return newState[root->aIndex] = r1 ; 
				return newState[root->aIndex] = oldState[root->aIndex] && r1;

			}
			case once:
			{
				ast_node *c1 = root->children[0] ; 
				bool r1 = eval(c1, ctrace, evalPos); 
				return newState[root->aIndex] = oldState[root->aIndex] || r1;
			}
			case LNOT:
			{
				ast_node *c1 = root->children[0] ; 
				bool r1 = eval(c1, ctrace, evalPos); 
				return newState[root->aIndex] = ! r1;
			} 
			default:
			{
				assert(0);
				return false; 
			}

		}
	}

bool eval_snapshot(ast_node * root, snapshot * snap)
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

	bool policy_check(ast_node * root, snapshot* snap){
		bool f = eval_snapshot(root,snap);
		copy_state(oldState, newState,aSize);
		return f; 
	}
	
	void evaluate(ast_node * root, trace * ctrace)
	{
		
		int tlen = ctrace->getSize(); 

		for(int i = 0 ; i < tlen; ++i )
		{
			bool f = eval(root, ctrace, i) ; 
			if(!f)
			{
				#ifdef OUTPUT
					printf("FORMULA FALSIFIED IN POSITION %d\n",i+1);
				#endif 
			}
			copy_state(oldState, newState,aSize); 
		}
		

	}
		
};


#endif 
