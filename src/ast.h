#ifndef __AST_H__
#define __AST_H__


#include "headers.h"


struct ast_node{

	nodeType nType ; 
	char *nValue ; 
	arrayIndex aIndex ; 
	 
	std::vector< ast_node *> children ; 

	ast_node()
	{
		children.clear() ; 
	}

	void add_children(ast_node *  n)
	{
		if(n)children.push_back(n) ; 
	}	

};

std::string nodetype_to_string(nodeType n, char * v);

#endif 
