#ifndef __PARSER_H__
#define __PARSER_H__

# include "headers.h"
# include "ast.h" 

void remove_space(char *formula);

int next_token(char *rFormula, char *token, int cIndex, int len);

int error_message(const char * msg);

void error_message_without_return(const char * msg);




class pltl_parser{

	arrayIndex globalIndex;
public:

	pltl_parser();
	int getGlobalIndex();
	std::pair< int , ast_node *> handle_binop(char * formula, int cIndex, int len, ast_node * current_node, nodeType n);

	std::pair< int , ast_node *> handle_unop(char * formula, int cIndex, int len, ast_node * current_node, nodeType n);

	std::pair< int , ast_node *> parse_formula( char * formula, int cIndex, int len, ast_node * current_node);
	ast_node * parse_formula_to_ast(char *formula, ast_node * current_node);

};

#endif 
