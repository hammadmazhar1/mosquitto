# include "ast.h"
# include "headers.h" 
# include "parser.h" 
# include "traces.h" 
# include "ast_util.h" 
# include "evaluator.h"  

trace currentTrace ; 
ast_node * formula_root ; 


int main(int argc, char *argv[])
{	
	if(argc != 3) return error_message("mismatched number of arguments\n Usage: ./executable-name file-name-containing-formula file-name-containing-trace"); 
	
	FILE *fformula = fopen(argv[1], "r"); 
	if(!fformula) return error_message("couldn't open the input formula file"); 
	
	FILE *ftrace = fopen(argv[2], "r"); 
	if(!ftrace) return error_message("couldn't open the input trace file"); 

	formula_root = (ast_node *) std::malloc( sizeof( ast_node)) ; 
	if(!formula_root) return error_message("couldn't allocate space for ast root"); 

	char raw_formula[1025] ; 
	if(!fgets(raw_formula, 1024, fformula)) return error_message("couldn't read the raw formula"); 


	#ifdef DEBUG
	printf("DEBUG: %s\n",raw_formula);
	#endif 	

	pltl_parser pr; 

	formula_root=pr.parse_formula_to_ast(raw_formula, formula_root);
	assert(formula_root);  

	#ifdef DEBUG
	print_tree(formula_root); printf("\n");
	#endif 

	//printf("I am here\n");

	//currentTrace.clear(); 
	readTrace(ftrace, currentTrace);
	
	#ifdef DEBUG
	printf("TRACE SIZE: %d\n",currentTrace.getSize());
	#endif 

	pltl_evaluator pltl_eval(pr.getGlobalIndex());

	pltl_eval.evaluate(formula_root, &currentTrace); 


	//CLEANING UP 
	free_tree(formula_root); 	
	fclose(fformula); 
	fclose(ftrace); 	

	return 0 ; 
}
