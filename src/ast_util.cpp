

# include "headers.h"
# include "ast.h"
# include "pl_ast.h"
# include "ast_util.h" 

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

void print_tree(pl_ast_node * cn)
{
	if(cn==NULL) assert(0); 
	if(cn->nType == state||cn->nType == LTRUE || cn->nType == LFALSE || cn->nType == CONSTANT_INT || cn->nType == CONSTANT_BOOL || cn->nType == CONSTANT_STR)
	{
		printf("%s",cn->nodetype_to_string().c_str()); return ; 	
	}
	else if(cn->nType==LNOT || cn->nType == PREV || cn->nType == CUR )
	{
		printf("%s ( ",cn->nodetype_to_string().c_str());
		print_tree(cn->children[0]);
		printf(" ) ");
		return ; 
	}
	else if(cn->nType == LAND || cn->nType == LOR || cn->nType == EQUAL || cn->nType == NEQUAL || cn->nType == LESS || cn->nType == MORE || cn->nType == LEQ || cn->nType == NEQUAL || cn->nType == LESS || cn->nType == MORE || cn->nType == LEQ || cn->nType == MEQ )
	{
		printf("%s ( ",cn->nodetype_to_string().c_str());
		print_tree(cn->children[0]);
		printf(" , ");
		print_tree(cn->children[1]);
		printf(" ) ");
		return ; 

	}
}


void free_tree(pl_ast_node *cn)
{
	if(!cn)return; 
	switch(cn->nType)
	{
		case LOR:
		case LAND:
		case NEQUAL:
		case LESS:
		case MORE:
		case LEQ:
		case MEQ:
		case EQUAL:
			free(cn->children[0]);
			free(cn->children[1] );
			free(cn); 
			return ; 
		case LNOT:
		case PREV:
		case CUR:
			free(cn->children[0]);
			free(cn);
			return ; 
		case LTRUE:
		case LFALSE:
			free(cn);
			return;
		case state:
			free(cn->nValue);
			free(cn);
			return ; 
		default:
			assert(0);
			return ; 
	}
}