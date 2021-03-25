#ifndef __PL_AST_H__
#define __PL_AST_H__


#include "headers.h"


class pl_ast_node{
public:
	pl_nodeType nType ; 
	std::string *nValue ;
    void* storedVal; 
	arrayIndex aIndex ; 
	 
	std::vector< pl_ast_node *> children ; 

	pl_ast_node();
	void add_children(pl_ast_node *  n);
    std::string nodetype_to_string();

};



#endif 
