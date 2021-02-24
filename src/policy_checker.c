#include <string.h>

#include "ast.h"
#include "headers.h" 
#include "parser.h" 
#include "traces.h" 
#include "ast_util.h" 
#include "evaluator.h"  
#include "mosquitto_broker_internal.h"
#include "alias_mosq.h"
#include "mqtt_protocol.h"
#include "memory_mosq.h"
#include "packet_mosq.h"
#include "property_mosq.h"
#include "read_handle.h"
#include "send_mosq.h"
#include "sys_tree.h"
#include "util_mosq.h"

// static trace *sys_states= NULL;
static ast_node * policy_root = NULL;

int check_policy(struct mosquitto_msg_store *command){
    return 0
}
int parse_policy(char *filename){
    FILE *fpolicy = fopen(filename, "r"); 
	if(!ftrace){
        return log__printf(NULL,MOSQ_LOG_DEBUG,"couldn't open the input policy file");
    } 
    policy_root = (ast_node *) std::malloc( sizeof( ast_node)) ; 
	if(!formula_root) {
        return log__printf(NULL,MOSQ_LOG_DEBUG,"couldn't allocate space for ast root");
    }
    char raw_formula[1025] ; 
	if(!fgets(raw_formula, 1024, fpolicy)){
        return error_message("couldn't read the raw policy");
    }
    pltl_parser pr;
    policy_root = pr.parse_formula_to_ast(raw_formula,policy_root);
}