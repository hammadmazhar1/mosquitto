#include "policy_checker.h"
#include "headers.h"
#include "pl_engine.h"
#include "system_state.h"



policy_engine* new_policy_engine(){
	policy_engine *pengine = new policy_engine();
	error_message_without_return("created policy engine");
    return pengine;
}

bool policy_engine_add_policy(policy_engine* pengine,char* raw_policy){

    return pengine->add_policy(raw_policy);
}


bool policy_engine_monitor(struct mosquitto_msg_store* msg){
    //create new state and check for propositions
    system_state* new_state = new system_state();
	system_state* old_state = db.parapet_state;
	for (std::map<std::string,void*>::iterator it =old_state->state_map.begin();it != old_state->state_map.end(); it++){
		new_state->update_state(it->first,it->second);
	}
	// error_message_without_return("Initialized new state with old state values");
	char* msg_topic = msg->topic;
	void* msg_value = msg->payload;
	if (std::string(msg_topic).find("int") != std::string::npos){
		int* x = new int();
		*x = atoi((char*)msg_value);
		msg_value = (void*) x;
	} else if (std::string(msg_topic).find("bool") != std::string::npos){
		bool* x = new bool();
		if (strcmp((char*)msg_topic,"ON") ==0 || strcmp((char*)msg_topic,"CLOSED") ==0){
			*x = true;
		} else{
			*x = false;
		}
		msg_value = (void*) x;
	}
	new_state->update_state(std::string(msg_topic),msg_value);
	// error_message_without_return("updated new message value");
	
	sys_state true_props = db.pl_solver->eval_props(old_state,new_state);
	// error_message_without_return("evaluated propositions");
    //send to policy engine
	
	// std::size_t sz = true_props.s.size();
	for (std::set<std::string>::iterator i = true_props.s.begin(); i != true_props.s.end(); i++){
		std::cout << "Active Propositions:" <<std::endl;
		std::cout << *i <<std::endl;
	}
	if(db.pengine->monitor(true_props)){
		
		db.parapet_state=new_state;
        return true;
    }
    else{
        return false;
    }
}
pl_engine* new_pl_engine(){
	return new pl_engine();
}





