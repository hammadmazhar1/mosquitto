#ifndef __AST_UTIL_H__
#define __AST_UTIL_H__

# include "headers.h"
# include "ast.h" 

void print_tree(ast_node * cn)
{
	if(cn==NULL) assert(0); 
	if(cn->nType == prop||cn->nType == LTRUE || cn->nType == LFALSE)
	{
		printf("%s",nodetype_to_string(cn->nType,cn->nValue).c_str()); return ; 	
	}
	else if(cn->nType==LNOT || cn->nType == historically || cn->nType == once || cn->nType == yesterday)
	{
		printf("%s ( ",nodetype_to_string(cn->nType,cn->nValue).c_str());
		print_tree(cn->children[0]);
		printf(" ) ");
		return ; 
	}
	else if(cn->nType == LAND || cn->nType == LOR || cn->nType == since || cn->nType == LIMPLY)
	{
		printf("%s ( ",nodetype_to_string(cn->nType,cn->nValue).c_str());
		print_tree(cn->children[0]);
		printf(" , ");
		print_tree(cn->children[1]);
		printf(" ) ");
		return ; 

	}
}


void free_tree(ast_node *cn)
{
	if(!cn)return; 
	switch(cn->nType)
	{
		case LOR:
		case LAND:
		case since:
		case LIMPLY:
			free(cn->children[0]);
			free(cn->children[1] );
			free(cn); 
			return ; 
		case LNOT:
		case yesterday:
		case historically:
		case once:
			free(cn->children[0]);
			free(cn);
			return ; 
		case LTRUE:
		case LFALSE:
			free(cn);
			return;
		case prop:
			free(cn->nValue);
			free(cn);
			return ; 
		default:
			assert(0);
			return ; 
	}
}



#endif 
