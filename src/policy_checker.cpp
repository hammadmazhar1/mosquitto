

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
		int new_bulb_level= (atoi((char*) msg->payload));
		if (new_bulb_level != context->bulb_level){
			new_state.s.insert(std::string("Change_in_intensity"));
			error_message_without_return("Proposition 'Change_in_intensity' true");
		}
	}
	if (strncmp(msg->topic,"Bulb_Temp",9)==0){
		int new_temp = (atoi((char*) msg->payload));
		if (new_temp != context->bulb_temp){
			new_state.s.insert(std::string("Change_in_temperature"));
			error_message_without_return("Proposition 'Change_in_temperature' true");
		}
	}
	if (context->bulb_temp == 100){
		new_state.s.insert(std::string("Color_temperature_100"));
		error_message_without_return("Proposition 'Color_temperature_100' true");
	}
    //send to policy engine
	if(pengine->monitor(new_state)){
		if (strncmp(msg->topic,"Bulb_Level",10)==0){
			char* x = (char*) msg->payload;
			std::cout<<"new_bulb_level: "<<x<<std::endl;
			context->bulb_level = (atoi((char*) msg->payload));
		}
		if (strncmp(msg->topic,"Bulb_Temp",9)==0){
			char* x = (char*) msg->payload;
			std::cout<<"new_bulb_temp: "<<x<<std::endl;
			context->bulb_temp = (atoi((char*) msg->payload));		
		}
        return true;
    }
    else{
        return false;
    }
}




