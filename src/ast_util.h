#ifndef __AST_UTIL_H__
#define __AST_UTIL_H__

# include "headers.h"
# include "ast.h" 
# include "pl_ast.h"

void print_tree(ast_node * cn);
void free_tree(ast_node *cn);
void print_tree(pl_ast_node * cn);
void free_tree(pl_ast_node *cn);



#endif 
