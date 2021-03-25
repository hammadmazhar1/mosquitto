# include "pl_parser.h"

void pl_remove_space(char *formula)
{
	int i, j, len =strlen(formula);
	//char msg[50];
	
	for(i=0,j=0; j<len;++j)
	{
		//snprintf(msg, sizeof(msg),"i:%d ,j:%d, len:%d",i,j,len);
		//error_message_without_return(msg);
		if(formula[j]==' ')continue;
		formula[i]=formula[j]; 
		++i;
	}
	formula[i]='\0';
}

int pl_next_token(char *rFormula, char *token, int cIndex, int len)
{
	int j = cIndex, i=0; 
	for(;j<len;++j)
	{
		if(rFormula[j]=='(' || rFormula[j]==')' || rFormula[j] == ',')
		{
			assert(i>0);
			token[i]='\0';
			return i;
		}
		token[i]=rFormula[j]; ++i; 
	}
	token[i]='\0';
	return i;

}
int pl_error_message(const char * msg)
{
	printf("ERROR:%s\n",msg);
	return 1 ; 
}

void pl_error_message_without_return(const char * msg)
{
	printf("ERROR:%s\n",msg);
}


pl_parser::pl_parser()
{
    globalIndex = 0 ; 
}
int pl_parser::getGlobalIndex()
{
    return globalIndex ; 
}



std::pair< int , pl_ast_node *> pl_parser::handle_binop(char * formula, int cIndex, int len, pl_ast_node * current_node, pl_nodeType n)
{
        current_node->nType = n ; 
        pl_ast_node *c1 = new pl_ast_node();
        pl_ast_node *c2 = new pl_ast_node();

        assert(cIndex < len); assert(formula[cIndex] =='('); ++cIndex;

        std::pair<int, pl_ast_node*> r1 = parse_formula(formula, cIndex, len, c1);
        current_node->add_children(r1.second); cIndex = r1.first ;
    
        assert(cIndex < len); assert(formula[cIndex] ==','); ++cIndex;

        std::pair<int, pl_ast_node*> r2 = parse_formula(formula, cIndex, len, c2);
        current_node->add_children(r2.second); cIndex = r2.first ;
        // std::cout<< "cIndex:" << cIndex <<", " << "len:" << len << std::endl;
        assert(cIndex < len); assert(formula[cIndex] ==')'); ++cIndex;

        return std::make_pair(cIndex, current_node);
    
}

std::pair< int , pl_ast_node *> pl_parser::handle_unop(char * formula, int cIndex, int len, pl_ast_node * current_node, pl_nodeType n)
{
        current_node->nType = n ; 
        pl_ast_node *c1 = new pl_ast_node();

        assert(cIndex < len); assert(formula[cIndex] =='('); ++cIndex;

        std::pair<int, pl_ast_node*> r1 = parse_formula(formula, cIndex, len, c1);
        current_node->add_children(r1.second); cIndex = r1.first ;
    
        // std::cout<< "cIndex:" << cIndex <<", " << "len:" << len << std::endl;
        assert(cIndex < len); assert(formula[cIndex] ==')'); ++cIndex;

        return std::make_pair(cIndex, current_node);

}
// std::pair< int , pl_ast_node *> pl_parser::handle_temporal(char * formula, int cIndex, int len, pl_ast_node * current_node, pl_nodeType n)
// {
//     current_node->nType = n ; 
//     // pl_ast_node *c1 = new pl_ast_node();

//         assert(cIndex < len); assert(formula[cIndex] =='('); ++cIndex;

//         std::pair<int, pl_ast_node*> r1 = parse_formula(formula, cIndex, len, c1);
//         current_node->add_children(r1.second); cIndex = r1.first ;
    
//         // std::cout<< "cIndex:" << cIndex <<", " << "len:" << len << std::endl;
//         assert(cIndex < len); assert(formula[cIndex] ==')'); ++cIndex;

//         return std::make_pair(cIndex, current_node);
// }
// std::pair< int , pl_ast_node *> pl_parser::handle_constant(char * formula, int cIndex, int len, pl_ast_node * current_node, pl_nodeType n)
// {
// }
std::pair< int , pl_ast_node *> pl_parser::parse_formula( char * formula, int cIndex, int len, pl_ast_node * current_node)
{
    if(cIndex >= len)
    {
        pl_error_message_without_return("currentIndex greater than length");		
        return std::make_pair(cIndex, (pl_ast_node*) NULL); 
    }
    char tok[1024] ; 
    int l = pl_next_token(formula, tok, cIndex, len);
    
    cIndex += l ; 
    current_node->aIndex = globalIndex; ++globalIndex; 
    #ifdef WITH_POLICY_CHECK 
        printf("DEBUG TOKEN: %s\n",tok);
    #endif 
    if(strcmp(tok,"==")==0)     return handle_binop(formula, cIndex, len, current_node, EQUAL); 
    else if(strcmp(tok,"&")==0) return handle_binop(formula, cIndex, len, current_node, LAND);
    else if(strcmp(tok,"|")==0) return handle_binop(formula, cIndex, len, current_node, LOR);
    else if(strcmp(tok,"!=")==0) return handle_binop(formula, cIndex, len, current_node, NEQUAL);
    else if(strcmp(tok,"<")==0) return handle_binop(formula, cIndex, len, current_node, LESS);
    else if(strcmp(tok,">")==0) return handle_binop(formula, cIndex, len, current_node, MORE);
    else if(strcmp(tok,"<=")==0) return handle_binop(formula, cIndex, len, current_node, LEQ);
    else if(strcmp(tok,">=")==0) return handle_binop(formula, cIndex, len, current_node, MEQ);

    else if(strcmp(tok,"!")==0) return handle_unop(formula, cIndex, len, current_node, LNOT) ; 
    
    else if(strcmp(tok,"PREVIOUS")==0){
        current_node->nType = PREV;
        assert(cIndex < len); assert(formula[cIndex] =='('); ++cIndex;
        l = pl_next_token(formula,tok,cIndex,len);
        cIndex += l;
        assert(cIndex < len); assert(formula[cIndex] ==')'); ++cIndex;
        current_node->nValue = new std::string(tok);
        pl_ast_node * new_node =  new pl_ast_node();
        new_node->nType = state;
        new_node->nValue = new std::string(tok);
        current_node->add_children(new_node);
        return std::make_pair(cIndex,current_node);

    } 
    else if(strcmp(tok,"CURRENT")==0) {
        current_node->nType = CUR;
        assert(cIndex < len); assert(formula[cIndex] =='('); ++cIndex;
        l = pl_next_token(formula,tok,cIndex,len);
        cIndex += l;
        assert(cIndex < len); assert(formula[cIndex] ==')'); ++cIndex;
        current_node->nValue = new std::string(tok);
        pl_ast_node * new_node = new pl_ast_node();
        new_node->nType = state;
        new_node->nValue = new std::string(tok);
        current_node->add_children(new_node);
        return std::make_pair(cIndex,current_node);

    } 
    else if(strcmp(tok,"CONSTANT_INT")==0){
        current_node->nType = CONSTANT_INT;
        assert(cIndex < len); assert(formula[cIndex] =='('); ++cIndex;
        l = pl_next_token(formula,tok,cIndex,len);
        cIndex += l;
        assert(cIndex < len); assert(formula[cIndex] ==')'); ++cIndex;
        int * i = new int;
        *i = atoi(tok);
        current_node->storedVal = (void*)i;
        return std::make_pair(cIndex,current_node);

    }
    else if(strcmp(tok,"CONSTANT_BOOL")==0)
    {
        current_node->nType = CONSTANT_BOOL;
        assert(cIndex < len); assert(formula[cIndex] =='('); ++cIndex;
        l = pl_next_token(formula,tok,cIndex,len);
        cIndex += l;
        assert(cIndex < len); assert(formula[cIndex] ==')'); ++cIndex;
        bool * i = new bool;
        if (strcmp(tok,"TRUE")==0){ 
            *i = true;
        } else{
            *i = false;
        }
        current_node->storedVal = (void*)i;
        return std::make_pair(cIndex,current_node);
   
    } 
    else if(strcmp(tok,"CONSTANT_STR")==0){
        current_node->nType = CONSTANT_BOOL;
        assert(cIndex < len); assert(formula[cIndex] =='('); ++cIndex;
        l = pl_next_token(formula,tok,cIndex,len);
        cIndex += l;
        assert(cIndex < len); assert(formula[cIndex] ==')'); ++cIndex;
        char * i = new char[1024];
        strcpy(i,tok); 
        current_node->storedVal = (void*)i;
        return std::make_pair(cIndex,current_node);
    } 

    else 	if(strcmp(tok,"TRUE")==0)
    {
        current_node->nType = LTRUE ;
        current_node->nValue=NULL; 
        return std::make_pair(cIndex, current_node) ; 

    }
    else 	if(strcmp(tok,"FALSE")==0)
    {
        current_node->nType = LFALSE ;
        current_node->nValue=NULL; 
        return std::make_pair(cIndex, current_node) ; 
    }
    else
    {
        current_node->nType = state ;
        std::string * val = new std::string(tok); 
        current_node->nValue = val; 
        return std::make_pair(cIndex, current_node) ; 
    }
}



pl_ast_node * pl_parser::parse_formula_to_pl_ast(char *formula, pl_ast_node * current_node)
{
    pl_remove_space(formula); 

    std::pair< int , pl_ast_node *> ret = parse_formula(formula, 0, strlen(formula), current_node) ; 
    current_node = ret.second ;
    std::string validation_result = validate_ast(current_node); 
    if (validation_result.compare("BOOL")==0){
        return current_node ;
    }
    else{
        pl_error_message_without_return(validation_result.c_str());
        return NULL;
    }
}

std::string pl_parser::validate_ast(pl_ast_node* root){
    if (root->nType==PREV || root->nType==CUR){
        if (root->nValue->find("int") != std::string::npos){
            return (std::string("INT"));
        } else if (root->nValue->find("bool") != std::string::npos){
            return (std::string("BOOL"));
        } else if (root->nValue->find("str") != std::string::npos){
            return (std::string("STR"));
        }
    } else if(root->nType==CONSTANT_INT){
        return (std::string("INT"));
    } else if(root->nType==CONSTANT_BOOL){
        return (std::string("BOOL"));
    } else if(root->nType==CONSTANT_STR){
        return (std::string("STR"));
    } else if (root->nType==EQUAL || root->nType==NEQUAL || root->nType==LESS || root->nType==MORE || root->nType==LEQ || root->nType==MEQ ){
        std::string left = validate_ast(root->children[0]);
        std::string right = validate_ast(root->children[1]);
        if (left.compare(right)==0){
            return(std::string("BOOL"));
        } else{
            if (left.find("ERROR") != std::string::npos){
                return left;
            } else if (right.find("ERROR") != std::string::npos){
                return right;
            } else{
                char* buf = new char[1024];
                snprintf(buf,1024,"ERROR: Types in expression %s do not match: %s vs %s",root->nodetype_to_string().c_str(),left.c_str(),right.c_str());
                return buf;
            }
        }
    }else if (root->nType==LAND || root->nType==LOR){
        std::string left = validate_ast(root->children[0]);
        std::string right = validate_ast(root->children[0]);
        if (left.compare("BOOL")==0 && right.compare("BOOL")==0){
            return left;
        } else{
            if (left.find("ERROR")!= std::string::npos){
                return left;
            } else if (right.find("ERROR")!= std::string::npos){
                return right;
            } else{
                char* buf = new char[1024];
                snprintf(buf,1024,"ERROR: Type in expression %s does not match: %s (Should be BOOL)",root->nodetype_to_string().c_str(),left.c_str());
                return buf;
            }
        }
    }
    return std::string("");
}