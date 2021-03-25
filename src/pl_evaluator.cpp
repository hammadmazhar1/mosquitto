# include "pl_evaluator.h"






void* pl_evaluator::eval_snap(pl_ast_node * root, system_state * old_snap, system_state * new_snap, std::string* ret_type)
{
    bool* ret = new bool(false);
    switch(root->nType)
    {

        case LTRUE:{
            ret = new bool(true);
            *ret_type = std::string("BOOL");
            return (void*) ret;
        }
        case LFALSE:
        {
            ret = new bool(true);
            *ret_type = std::string("BOOL");
            return (void*) ret;
        }
        // case prop:   return newState[root->aIndex]  = snap->isTrue(std::string(root->nValue)) ; 
        case LAND:
        {
            pl_ast_node *c1 = root->children[0] ; 
            pl_ast_node *c2 = root->children[1] ; 
            bool r1 = *(bool*) eval_snap(c1, old_snap, new_snap,ret_type);
            bool r2 = *(bool*)eval_snap(c2, old_snap, new_snap,ret_type);
            ret = new bool(r1 && r2) ;
            *ret_type = std::string("BOOL");
            return (void*) ret; 
        }
        case LOR:
        {
            pl_ast_node *c1 = root->children[0] ; 
            pl_ast_node *c2 = root->children[1] ; 
            bool r1 = *(bool*)eval_snap(c1, old_snap,new_snap,ret_type);
            bool r2 = *(bool*)eval_snap(c2, old_snap,new_snap,ret_type);
            ret = new bool(r1 || r2);
            *ret_type = std::string("BOOL");
            return (void*) ret ; 
        }
        case LNOT:
        {
            pl_ast_node *c1 = root->children[0] ; 
            bool r1 = *(bool*)eval_snap(c1, old_snap,new_snap,ret_type);
            ret = new bool(!r1);
            *ret_type = std::string("BOOL");
            return (void*) ret;
        }
        case EQUAL:
        {
            pl_ast_node *c1 = root->children[0] ; 
            pl_ast_node *c2 = root->children[1] ;
            std::string ret_type2; 
            void* r1 = eval_snap(c1, old_snap,new_snap,ret_type);
            void* r2 = eval_snap(c2, old_snap,new_snap,&ret_type2);
            // std::cout << "Sides evaluated for EQUAL" << std::endl; 
            // std::cout<<*ret_type<< " " << ret_type2 << std::endl;
            if (ret_type->compare("BOOL")==0 && ret_type2.compare("BOOL")==0){
                ret = new bool(*(bool*)r1 == *(bool*)r2); 
            } else if(ret_type->compare("INT")==0 && ret_type2.compare("INT")==0){
                ret = new bool( *(int*)r1 == *(int*)r2);
            } else if(ret_type->compare("STR")==0 && ret_type2.compare("STR")==0){
                ret = new bool( strcmp((char*)r1,(char*)r2) ==0);    
            }
            *ret_type = std::string("BOOL");
            return (void*) ret;
        }
        case NEQUAL:
        {
            pl_ast_node *c1 = root->children[0] ; 
            pl_ast_node *c2 = root->children[1] ;
            std::string ret_type2;
            void* r1 = eval_snap(c1, old_snap,new_snap,ret_type);
            void* r2 = eval_snap(c2, old_snap,new_snap,&ret_type2);
            if (ret_type->compare("BOOL")==0 && ret_type2.compare("BOOL")==0){
                ret = new bool(*(bool*)r1 != *(bool*)r2); 
                
            } else if(ret_type->compare("INT")==0 && ret_type2.compare("INT")==0){
                ret = new bool( *(int*)r1 != *(int*)r2);

            } else if(ret_type->compare("STR")==0 && ret_type2.compare("STR")==0){
                ret = new bool( strcmp((char*)r1,(char*)r2) !=0);
                
            }
            *ret_type = std::string("BOOL");
            return (void*) ret;
        }
        case LESS:
        {
            pl_ast_node *c1 = root->children[0] ; 
            pl_ast_node *c2 = root->children[1] ;
            std::string ret_type2; 
            void* r1 = eval_snap(c1, old_snap,new_snap,ret_type);
            void* r2 = eval_snap(c2, old_snap,new_snap,&ret_type2);
            if(ret_type->compare("INT")==0 && ret_type2.compare("INT")==0){
                ret = new bool(*(int*)r1 < *(int*)r2);             
            } else if(ret_type->compare("STR")==0 && ret_type2.compare("STR")==0){
                ret = new bool(strcmp((char*)r1,(char*)r2) <0);
            }
            *ret_type = std::string("BOOL");
            return (void*) ret;
        }
        case MORE:
        {
            pl_ast_node *c1 = root->children[0] ; 
            pl_ast_node *c2 = root->children[1] ;
            std::string ret_type2; 
            void* r1 = eval_snap(c1, old_snap,new_snap,ret_type);
            void* r2 = eval_snap(c2, old_snap,new_snap,&ret_type2);
            if(ret_type->compare("INT")==0 && ret_type2.compare("INT")==0){
                ret = new bool(*(int*)r1 > *(int*)r2);
                *ret_type = std::string("BOOL"); 
            } else if(ret_type->compare("STR")==0 && ret_type2.compare("STR")==0){
                ret = new bool(strcmp((char*)r1,(char*)r2) >0);
                *ret_type = std::string("BOOL");
            }
            return (void*) ret;
        }
        case LEQ:
        {
            pl_ast_node *c1 = root->children[0] ; 
            pl_ast_node *c2 = root->children[1] ;
            std::string ret_type2; 
            void* r1 = eval_snap(c1, old_snap,new_snap,ret_type);
            void* r2 = eval_snap(c2, old_snap,new_snap,&ret_type2);
            if(ret_type->compare("INT")==0 && ret_type2.compare("INT")==0){
                ret = new bool( *(int*)r1 <= *(int*)r2);
                *ret_type = std::string("BOOL"); 
            } else if(ret_type->compare("STR")==0 && ret_type2.compare("STR")==0){
                ret = new bool(strcmp((char*)r1,(char*)r2) <=0);
                *ret_type = std::string("BOOL");
            }
            return (void*) ret;
        }
        case MEQ:
        {
            pl_ast_node *c1 = root->children[0] ; 
            pl_ast_node *c2 = root->children[1] ;
            std::string ret_type2; 
            void* r1 = eval_snap(c1, old_snap,new_snap,ret_type);
            void* r2 = eval_snap(c2, old_snap,new_snap,&ret_type2);
            if(ret_type->compare("INT")==0 && ret_type2.compare("INT")==0){
                ret = new bool(*(int*)r1 >= *(int*)r2);
                *ret_type = std::string("BOOL"); 
            } else if(ret_type->compare("STR")==0 && ret_type2.compare("STR")==0){
                ret = new bool(strcmp((char*)r1,(char*)r2) >=0);
                *ret_type = std::string("BOOL");
            }
            return (void*) ret;
        }
        case PREV:
        {
            // std::cout << "In case PREV" << std::endl;
            void* r1 = old_snap->retrieve_state(*(root->nValue));
            if(root->nValue->find("int")!=std::string::npos) {
                // std::cout << "PREV "<<*(root->nValue) << std::endl;
                if (r1 == NULL){
                    int* n = new int();
                    r1 = (void*)n;
                }
                std::cout << "Prev "<< *(root->nValue) << " " <<*(int*) r1 <<std::endl;
                *ret_type = std::string("INT");
            } else if(root->nValue->find("bool")!=std::string::npos){
                // std::cout << "PREV "<<*(root->nValue) << std::endl;
                if (r1 == NULL){
                    bool* n = new bool(false);
                    r1 = (void*)n;
                }
                *ret_type = std::string("BOOL");
            }else if(root->nValue->find("str")!=std::string::npos){
                // std::cout << "PREV "<<*(root->nValue) << std::endl;
                if (r1 == NULL){
                    std::string* n = new std::string("");
                    r1 = (void*)n;
                }
                *ret_type = std::string("STR");
            }
            return r1;
        }
        case CUR:
        {
            // std::cout << "In case Current" << std::endl;
            void* r1 = new_snap->retrieve_state(*(root->nValue));
            if(root->nValue->find("int")!=std::string::npos) {
                // std::cout << "CURRENT "<<*(root->nValue) << std::endl;
                if (r1 == NULL){
                    r1 = old_snap->retrieve_state(*(root->nValue));
                    if (r1 == NULL){
                        int* n = new int();
                        r1 = (void*)n;
                    }
                }
                // std::cout << "Current "<< *(root->nValue) << " " <<*(int*) r1 <<std::endl;

                *ret_type = std::string("INT"); 
            } else if(root->nValue->find("bool")!=std::string::npos){
                // std::cout << "CURRENT "<<*(root->nValue) << std::endl;
                 if (r1 == NULL){
                    r1 = old_snap->retrieve_state(*(root->nValue));
                    if (r1 == NULL){
                        bool* n = new bool(false);
                        r1 = (void*)n;
                    }
                }
                *ret_type = std::string("BOOL");
            }else if(root->nValue->find("str")!=std::string::npos){
                // std::cout << "CURRENT "<<*(root->nValue) << std::endl;
                 if (r1 == NULL){
                    r1 = old_snap->retrieve_state(*(root->nValue));
                    if (r1 == NULL){
                        std::string* n = new std::string("");
                        r1 = (void*)n;
                    }
                }
                *ret_type = std::string("STR");
            }
            return r1;
        }
        case CONSTANT_INT:
        {
            void* r1 = root->storedVal;
            *ret_type = std::string("INT"); 
            return r1;
        }
        case CONSTANT_BOOL:
        {
            void* r1 = root->storedVal;
            *ret_type = std::string("BOOL");
            return r1;
        }
        case CONSTANT_STR:
        {
            void* r1 = root->storedVal;
            *ret_type = std::string("STR");
            return r1;
        }
        default:
        {
            assert(0);
            bool * ret = new bool(false);
            *ret_type = std::string("BOOL");
            return ret; 
        }

    }
    *ret_type = std::string("BOOL");
    return (void *) ret;
}

bool pl_evaluator::prop_check(pl_ast_node * root, system_state* old_snap, system_state* new_snap){
	std::string ret_type ;
    void* f = eval_snap(root,old_snap,new_snap,&ret_type);
    // std::cout << "ret type: " << ret_type << std::endl; 
    if (ret_type == std::string("BOOL")){
        // std::cout << "final answer:" << *(bool*)f <<std::endl;
	    return *(bool*)f;
    }
    return false;
	 
}
		 
