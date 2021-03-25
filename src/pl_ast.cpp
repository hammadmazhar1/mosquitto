
#include "headers.h"
#include "pl_ast.h"

//typedef struct ast_node ast_node ; 
pl_ast_node::pl_ast_node()
	{
		children.clear() ; 
	}

void pl_ast_node::add_children(pl_ast_node *  n)
	{
		// printf("adding child\n");
		// std::cout<<children.size()<<std::endl;
		if(n)children.push_back(n) ; 
		// printf("child_added\n");
	}	

std::string pl_ast_node::nodetype_to_string()
{
	switch(nType)
	{
		case LTRUE: return std::string("TRUE");
		case LFALSE: return std::string("FALSE");
		case state: return *nValue ; 
		case LNOT : return std::string("!");
		case LAND : return std::string("&");
		case LOR : return std::string("|");
		case EQUAL : return std::string("==");
		case NEQUAL : return std::string("!=");
		case LESS: return std::string("<");
		case MORE : return std::string(">");
		case LEQ : return std::string("<=");
        case MEQ : return std::string(">=");
        case PREV : return std::string("PREVIOUS");
        case CUR : return std::string("CURRENT");
        case CONSTANT_INT:
            // int size = snprintf(nullptr,0,"CONSTANT_INT(%d)",*(int*)(n->nValue)) +1;
            // char* buf = new char[size];
            // snprintf(buf,size,"CONSTANT_INT(%d)",*(int*)(n->nValue));
            return std::string(to_string(*(int*)(storedVal)));
        case CONSTANT_BOOL:
            if (*(bool*)storedVal){
                return std::string("TRUE" );
            } else{
                return std::string("FALSE" );
            }
        case CONSTANT_STR:
            return *nValue;
		default: assert(0); 
	}
	return std::string(""); 
}

