
#include "headers.h"
#include "ast.h"

//typedef struct ast_node ast_node ; 
ast_node::ast_node()
	{
		children.clear() ; 
	}

void ast_node::add_children(ast_node *  n)
	{
		// printf("adding child\n");
		// std::cout<<children.size()<<std::endl;
		if(n)children.push_back(n) ; 
		// printf("child_added\n");
	}	

std::string nodetype_to_string(nodeType n, char * v)
{
	switch(n)
	{
		case LTRUE: return std::string("TRUE");
		case LFALSE: return std::string("FALSE");
		case prop: return std::string(v) ; 
		case LNOT : return std::string("!");
		case LAND : return std::string("&");
		case LOR : return std::string("|");
		case LIMPLY : return std::string("=>");
		case once : return std::string("O");
		case yesterday : return std::string("Y");
		case since : return std::string("S");
		case historically : return std::string("H");
		default: assert(0); 
	}
	return std::string(""); 
}

