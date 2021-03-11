

#include "policy_checker.h"



policy_engine* new_policy_engine(){
	policy_engine *pengine = new policy_engine();
	error_message_without_return("created policy engine");
    return pengine;
}

bool policy_engine_add_policy(policy_engine* pengine,char* raw_policy){

    return pengine->add_policy(raw_policy);
}

// bool policy_engine_monitor(policy_engine* pengine, struct mosquitto* context, struct mosquitto_msg_store * msg){
//     //create new state and check for propositions
//     struct sys_state new_state;
//     if (strncmp(msg->topic,"int_Bulb_Level",10)==0){
// 		int new_bulb_level= (atoi((char*) msg->payload));
// 		if (new_bulb_level != context->bulb_level){
// 			new_state.s.insert(std::string("Change_in_intensity"));
// 			log__prinf(NULL,MOSQ_LOG_INFO,"Proposition 'Change_in_intensity' true");
// 		}
// 	}
// 	if (strncmp(msg->topic,"Bulb_Temp",9)==0){
// 		int new_temp = (atoi((char*) msg->payload));
// 		if (new_temp != context->bulb_temp){
// 			new_state.s.insert(std::string("Change_in_temperature"));
// 			log__prinf(NULL,MOSQ_LOG_INFO,"Proposition 'Change_in_temperature' true");
// 		}
// 	}
// 	if (context->bulb_temp == 100){
// 		new_state.s.insert(std::string("Color_temperature_100"));
// 		log__prinf(NULL,MOSQ_LOG_INFO,"Proposition 'Color_temperature' true");
// 	}
//     //send to policy engine
// 	if(pengine->monitor(new_state)){
// 		if (strncmp(msg->topic,"Bulb_Level",10)==0){
// 			char* x = (char*) msg->payload;
// 			std::cout<<"new_bulb_level: "<<x<<std::endl;
// 			context->bulb_level = (atoi((char*) msg->payload));
// 		}
// 		if (strncmp(msg->topic,"Bulb_Temp",9)==0){
// 			char* x = (char*) msg->payload;
// 			std::cout<<"new_bulb_temp: "<<x<<std::endl;
// 			context->bulb_temp = (atoi((char*) msg->payload));		
// 		}
//         return true;
//     }
//     else{
//         return false;
//     }
// }
bool policy_engine_monitor(struct mosquitto_msg_store* msg){
    //create new state and check for propositions
    struct sys_state new_state;
	int level_cmp = strncmp(msg->topic,"Bulb1/int_Bulb_Level",20);
	int temp_cmp = strncmp(msg->topic,"Bulb1/int_Bulb_Temp",19);
	log__printf(NULL,MOSQ_LOG_INFO,"strcmp %s, %s level res: %d",msg->topic,"Bulb1/int_Bulb_Level",level_cmp);
	log__printf(NULL,MOSQ_LOG_INFO,"strcmp %s, %s temp res: %d",msg->topic,"Bulb1/int_Bulb_Temp",temp_cmp);
    if (!strcmp(msg->topic,"Bulb1/int_Bulb_Level")){
		int new_bulb_level= (atoi((char*) msg->payload));
		void* old_bulb_level = db.parapet_state->retrieve_state(std::string("Bulb1/int_Bulb_Level"));
		if (old_bulb_level){
			log__printf(NULL, MOSQ_LOG_INFO,"Checking old state of %s",msg->topic);
			if (*(int*)old_bulb_level != new_bulb_level){
				new_state.s.insert(std::string("Change_in_intensity"));
				log__printf(NULL,MOSQ_LOG_INFO,"Proposition 'Change_in_intensity' true");	
			}
		} else{
			new_state.s.insert(std::string("Change_in_intensity"));
			log__printf(NULL,MOSQ_LOG_INFO,"Proposition 'Change_in_intensity' true");
		}
	}
	if (!strcmp(msg->topic,"Bulb1/int_Bulb_Temp")){
		int new_bulb_temp = (atoi((char*) msg->payload));
		void* old_bulb_temp = db.parapet_state->retrieve_state(std::string("Bulb1/int_Bulb_Temp"));
		if (old_bulb_temp){
			log__printf(NULL,MOSQ_LOG_INFO,"old Bulb Temp State Found");
			if (*(int*)old_bulb_temp != new_bulb_temp){
				new_state.s.insert(std::string("Change_in_temperature"));
				log__printf(NULL,MOSQ_LOG_INFO,"Proposition 'Change_in_temperature' true");	
			}
		} else{
			new_state.s.insert(std::string("Change_in_temperature"));
			log__printf(NULL,MOSQ_LOG_INFO,"Proposition 'Change_in_temperature' true");
		}
	}
	
	void* old_bulb_temp = db.parapet_state->retrieve_state(std::string("Bulb1/int_Bulb_Temp"));
	if (old_bulb_temp){
		log__printf(NULL, MOSQ_LOG_INFO,"Checking old state of %s: %d","Bulb1/int_Bulb_Temp",*(int*) old_bulb_temp);
		if (*(int*)old_bulb_temp == 100){
			new_state.s.insert(std::string("Color_temperature_100"));
			log__printf(NULL,MOSQ_LOG_INFO,"Proposition 'Color_temperature_100' true");
		}
	}
    //send to policy engine
	if(db.pengine->monitor(new_state)){
		if (!strcmp(msg->topic,"Bulb1/int_Bulb_Level")){
			char* x = (char*) msg->payload;
			log__printf(NULL,MOSQ_LOG_INFO,"new_bulb_level: %s ",x);
			int a = atoi(x);
			db.parapet_state->update_state(std::string(msg->topic),(void*) &a);

			
		}
		if (!strcmp(msg->topic,"Bulb1/int_Bulb_Temp")){
			char* x = (char*) msg->payload;
			log__printf(NULL,MOSQ_LOG_INFO,"new_bulb_temperature: %s ",x);		
			int a = atoi(x);
			db.parapet_state->update_state(std::string(msg->topic),(void*) &a);
		}
		// db.parapet_state->update_state(std::string(msg->topic),msg->payload);
        return true;
    }
    else{
        return false;
    }
}




