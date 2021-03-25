# include "pl_engine.h"
# include "pl_parser.h"

    //constructor: creates a parser and initializes the other data-structures. 
pl_engine::pl_engine()
{
    formula_parser = new pl_parser() ; 
    prop_asts.clear();
    prop_names.clear(); 
    prop_evaluator = new pl_evaluator(); 
    
}

bool pl_engine::add_prop(char * raw_prop, std::string prop_name)
{
    pl_ast_node * fast = new pl_ast_node() ;
    // char msg[50];
    // snprintf(msg, sizeof(msg),"initialized policy ast");
    // error_message_without_return(msg);
    if(!fast)
    {
	    pl_error_message_without_return("couldn't allocate space for ast root inside add_policy <pl_engine.h>\n");
        return false; 
    }
        
    pl_ast_node* fast2 = formula_parser->parse_formula_to_pl_ast(raw_prop, fast) ; 

    if(!fast2){
	    pl_error_message_without_return("couldn't allocate space for ast root inside add_policy <pl_engine.h>\n");
        return false; 

    }

    
    prop_asts.push_back(fast2) ;
    prop_names.push_back(prop_name); 
    
    int policy_size = formula_parser->getGlobalIndex();


    assert(prop_names.size() == prop_asts.size()); 

    return true ; 
}

sys_state pl_engine::eval_props(system_state* old_state, system_state* new_state)
{
    std::size_t sz = prop_asts.size();
    std::cout<<"Number of propositions to check:"<< sz <<std::endl;
    sys_state new_props; 
    for(std::size_t i = 0 ; i < sz ; ++i)
    {
        std::cout<<"Checking proposition: " << prop_names[i] <<std::endl;
        if(prop_evaluator->prop_check(prop_asts[i], old_state, new_state)){
            // std::cout << "Propostion true: " << prop_names[i] <<std::endl;
            new_props.s.insert(prop_names[i]);
        }   
    }
    std::cout<<"Proposition check complete" <<std::endl;
    
    return new_props; 
}
bool pl_engine::add_prop_file(char* prop_file){
    std::ifstream* prop_file_reader = new std::ifstream(prop_file);
	std::string line;
	while(std::getline(*prop_file_reader,line,'\n')){
		std::stringstream ss;
        ss.str(line);
		std::string prop_name;
		std::string raw_formula_s;
		std::getline(ss,prop_name,':');
		std::getline(ss,raw_formula_s,'\n');
        char* raw_formula = new char[1024];
        strcpy(raw_formula,raw_formula_s.c_str());
		if (!add_prop(raw_formula,std::string(prop_name))){
            std::cout<<"Error parsing proposition, Prop Name:"<< prop_name << ", Prop Formula: " << raw_formula << std::endl;
        }
	}
	
	return true;
}



    //destructor: frees all the dynamically allocated memory 
pl_engine::~pl_engine()
{
    free(formula_parser); 
    int sz = (int) prop_asts.size();
    for(int i = 0 ;i < sz ; ++i) free_tree(prop_asts[i]) ; 
    prop_asts.clear(); 
    // for(int i = 0 ; i < sz; ++i) delete prop_names[i];
    prop_names.clear();
    free(prop_evaluator);  
}
