#ifndef __AST_H__
#define __AST_H__


#include "headers.h"


class ast_node{
public:
	nodeType nType ; 
	char *nValue ; 
	arrayIndex aIndex ; 
	 
	std::vector< ast_node *> children ; 

	ast_node();
	void add_children(ast_node *  n);

};

std::string nodetype_to_string(nodeType n, char * v);

#endif 
