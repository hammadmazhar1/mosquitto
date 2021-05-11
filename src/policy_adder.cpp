# include "policy_adder.h"

    //constructor: creates a parser and initializes the other data-structures. 
policy_engine::policy_engine()
{
    // error_message_without_return("entering constructor");
    formula_parser = new pltl_parser() ; 
    // error_message_without_return("created formula parser");
    policy_asts.clear(); 
    // error_message_without_return("cleared policy asts");
    policy_evaluators.clear(); 
    // error_message_without_return("cleared evaluators");
}

bool policy_engine::add_policy(char * raw_policy)
{
    ast_node * fast = new ast_node() ;
    char msg[50];
    snprintf(msg, sizeof(msg),"initialized policy ast");
    error_message_without_return(msg);
    if(!fast)
    {
	error_message_without_return("couldn't allocate space for ast root inside add_policy <policy_adder.h>\n");
        fprintf(stderr,"couldn't allocate space for ast root inside add_policy <policy_adder.h>\n");
        return false; 
    }
        
    ast_node* fast2 = formula_parser->parse_formula_to_ast(raw_policy, fast) ; 
    if(!fast){
	error_message_without_return("couldn't allocate space for ast root inside add_policy <policy_adder.h>\n");
        fprintf(stderr,"couldn't allocate space for ast root inside add_policy <policy_adder.h>\n");
        return false; 

    }
    snprintf(msg, sizeof(msg),"parsed formula policy ast");
    policy_asts.push_back(fast2) ; 
    snprintf(msg, sizeof(msg),"added policy ast");
    error_message_without_return(msg);
    int policy_size = formula_parser->getGlobalIndex();

    pltl_evaluator * peval = new pltl_evaluator(policy_size); 
    error_message_without_return("created evaluator");
    if(!peval)
    {
        fprintf(stderr,"Cannot allocate space for pltl evaluator inside add_policy <policy_adder.h>\n") ; 
        return false; 
    }
    policy_evaluators.push_back(peval) ; 

    assert(policy_evaluators.size() == policy_asts.size()); 

    return true ; 
}
bool policy_engine::monitor(sys_state st)
{
    std::size_t sz = policy_asts.size();
    std::cout<<"Number of policy asts to check:"<< sz <<std::endl; 
    for(std::size_t i = 0 ; i < sz ; ++i)
    {
        if(!policy_evaluators[i]->policy_check(policy_asts[i], &st)) return false;  
    }
    std::cout<<"Policy check complete" <<std::endl;
    for(std::size_t i = 0 ; i < sz; ++i)
        policy_evaluators[i]->copy_policychecker_state(); 
    std::cout<<"Policy state copy complete" <<std::endl;
    return true; 
}




    //destructor: frees all the dynamically allocated memory 
policy_engine::~policy_engine()
{
    free(formula_parser); 
    int sz = (int) policy_asts.size();
    for(int i = 0 ;i < sz ; ++i) free_tree(policy_asts[i]) ; 
    policy_asts.clear(); 
    for(int i = 0 ; i < sz; ++i) delete policy_evaluators[i];
    policy_evaluators.clear();  
}
invariant_engine::invariant_engine()
{
    // error_message_without_return("entering constructor");
    formula_parser = new pltl_parser() ; 
    // error_message_without_return("created formula parser");
    invariant_asts.clear(); 
    // error_message_without_return("cleared policy asts");
    invariant_evaluators.clear(); 
    // error_message_without_return("cleared evaluators");
    corrective_actions.clear();
}

bool invariant_engine::add_invariant(string invariant,string actions)
{
    ast_node * fast = new ast_node() ;
    char msg[50];
    snprintf(msg, sizeof(msg),"initialized policy ast");
    error_message_without_return(msg);
    if(!fast)
    {
	error_message_without_return("couldn't allocate space for ast root inside add_policy <policy_adder.h>\n");
        fprintf(stderr,"couldn't allocate space for ast root inside add_invariant <policy_adder.h>\n");
        return false; 
    }
        
    ast_node* fast2 = formula_parser->parse_formula_to_ast(invariant.c_str(), fast) ; 
    if(!fast){
	error_message_without_return("couldn't allocate space for ast root inside add_policy <policy_adder.h>\n");
        fprintf(stderr,"couldn't allocate space for ast root inside add_invariant <policy_adder.h>\n");
        return false; 

    }
    snprintf(msg, sizeof(msg),"parsed formula invariant ast");
    invariant_asts.push_back(fast2) ; 
    snprintf(msg, sizeof(msg),"added invariant ast");
    error_message_without_return(msg);
    int invariant_size = formula_parser->getGlobalIndex();

    pltl_evaluator * peval = new pltl_evaluator(policy_size); 
    error_message_without_return("created invariant evaluator");
    if(!peval)
    {
        fprintf(stderr,"Cannot allocate space for pltl evaluator inside add_invariant <policy_adder.h>\n") ; 
        return false; 
    }
    invariant_evaluators.push_back(peval) ; 

    assert(invariant_evaluators.size() == invariant_asts.size()); 

    vector<string> action_strings = split_string(actions,':');
    vector<pair<string,void*>> parsed_actions;
    for (size_t i = 0; i != action_strings.size();++i){
        pair<string,void*> action = parse_action(action_strings[i]);
        parsed_actions.push_back(action);
    }
    corrective_actions.push_back(parsed_actions);
    assert(invariant_asts.size() == corrective_actions.sizes());
    return true ; 
}
vector<pair<string,void*>> invariant_engine:test_invariants(sys_state st)
{
    vector<pair<string,void*>> retval;
    std::size_t sz = invariant_asts.size();
    std::cout<<"Number of invariant asts to check:"<< sz <<std::endl; 
    for(std::size_t i = 0 ; i < sz ; ++i)
    {
        if(!invariant_evaluators[i]->policy_check(invariant_asts[i], &st)){
            vector<pair<string,void*>> possible_actions = corrective_actions[i];
            for (size_t j = 0; i<possible_actions.size();++j){
                bool to_be_added = true;
                for (size_t k = 0; k <retval.size();++k){
                    if (retval[k].first == possible_actions[j].first){
                        to_be_added = false;
                    }
                }
                if (to_be_added){
                    retval.push_back(possible_actions[j]);
                }
            }
        }  
    }
    std::cout<<"Invariant check complete" <<std::endl;
    for(std::size_t i = 0 ; i < sz; ++i)
        invariant_evaluators[i]->copy_policychecker_state(); 
    std::cout<<"invariant state copy complete" <<std::endl;
    return retval; 
}

std::pair<string,void*> invariant_engine::parse_action(string action_string){
    char tok[1024];
    int cIndex = 1;
    int len = action_string.length();
    int l = next_token(action_string.c_str(),tok,cIndex,len);
    cIndex += l;
    string action_topic(tok);
    l = next_token(action_string.c_str(),tok,cIndex,len);
    void* value;
    string action_value(tok);
    if (action_topic.find("int")!= string::npos){
        int* val = new int();
        *val = atoi(action_value.c_str());
        value = (void*) val;
    } else if (action_topic.find("bool") != string::npos){
        bool* val = new bool();
        if strcmp(action_value.c_str(),'TRUE'){
            *val = true;
        } else{
            *val = false;
        }
        value = (void*) val

    } else if (action_topic.find("str") != string::npos){
        char val[1024];
        strcpy(val,action_value.c_str());
        value = (void*) val;
    }
    pair<string, void*> ret_val;
    retval.first = action_topic;
    retval.second = value;
    return retval;

}
vector<string> invariant_engine::split_string(string input, char delimiter){
    vector<string> retval;
    size_t pos = 0;
    string token;
    while ((pos = input.find(delimiter)) != string::npos) {
        token = input.substr(0, pos);
        retval.push_back(token);
        input.erase(0, pos + 1);
    }
    retval.push_back(input);
    return retval;
}

    //destructor: frees all the dynamically allocated memory 
invariant_engine::~invariant_engine()
{
    free(formula_parser); 
    int sz = (int) invariant_asts.size();
    for(int i = 0 ;i < sz ; ++i) free_tree(invariant_asts[i]) ; 
    invariant_asts.clear(); 
    for(int i = 0 ; i < sz; ++i) delete invariant_evaluators[i];
    invariant_evaluators.clear();  
}