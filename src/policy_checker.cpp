

#include "policy_checker.h"



policy_engine* new_policy_engine(){
	policy_engine *pengine = new policy_engine();
	error_message_without_return("created policy engine");
    return pengine;
}

bool policy_engine_add_policy(policy_engine* pengine,char* raw_policy){
    return pengine->add_policy(raw_policy);
}

bool policy_engine_monitor(policy_engine* pengine, struct mosquitto* context, struct mosquitto_msg_store * msg){
    //create new state and check for propositions
    struct sys_state new_state;
    if (strncmp(msg->topic,"Bulb_Level",10)==0){
		int new_bulb_level= * ((uint16_t*) msg->payload);
		if (new_bulb_level != context->bulb_level){
			new_state.s.insert(std::string("Change_in_intensity"));
		}
	}
	if (strncmp(msg->topic,"Bulb_Temp",9)==0){
		int new_temp = *((uint16_t*) msg->payload);
		if (new_temp != context->bulb_temp){
			new_state.s.insert(std::string("Change_in_temperature"));
		}
		if (context->bulb_temp == 100){
			new_state.s.insert(std::string("Color_temperature_100"));
		}
	}
    //send to policy engine
	if(pengine->monitor(new_state)){
		if (strncmp(msg->topic,"Bulb_Level",10)==0){
			context->bulb_level = *((uint16_t*) msg->payload);
		}
		if (strncmp(msg->topic,"Bulb_Temp",9)==0){
			context->bulb_temp = *((uint16_t*) msg->payload);		
		}
        return true;
    }
    else{
        return false;
    }
}




