#ifndef __PL_PARSER_H__
#define __PL_PARSER_H__

# include "headers.h"
# include "pl_ast.h"
# include "parser.h" 
#include "ast_util.h"

class pl_parser{

	arrayIndex globalIndex;
public:

	pl_parser();
	int getGlobalIndex();
	std::pair< int , pl_ast_node *> handle_binop(char * formula, int cIndex, int len, pl_ast_node * current_node, pl_nodeType n);

	std::pair< int , pl_ast_node *> handle_unop(char * formula, int cIndex, int len, pl_ast_node * current_node, pl_nodeType n);

   	// std::pair< int , pl_ast_node *> handle_temporal(char * formula, int cIndex, int len, pl_ast_node * current_node, pl_nodeType n);

   	// std::pair< int , pl_ast_node *> handle_constant(char * formula, int cIndex, int len, pl_ast_node * current_node, pl_nodeType n);

	std::pair< int , pl_ast_node *> parse_formula( char * formula, int cIndex, int len, pl_ast_node * current_node);
	pl_ast_node * parse_formula_to_pl_ast(char *formula, pl_ast_node * current_node);
    std::string validate_ast(pl_ast_node* root);
};
void pl_remove_space(char* formula);
int pl_next_token(char *rFormula, char *token, int cIndex, int len);
int pl_error_message(const char * msg);
void pl_error_message_without_return(const char * msg);
#endif 
