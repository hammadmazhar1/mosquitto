#ifndef __POLICY_CHECKER_H
#define __POLICY_CHECKER_H


#include "headers.h" 
#include "policy_adder.h" 
#include "pl_engine.h"
#include "mosquitto_broker_internal.h"
// #include "alias_mosq.h"
// #include "mqtt_protocol.h"
// #include "memory_mosq.h"
// #include "packet_mosq.h"
// #include "property_mosq.h"
// #include "read_handle.h"
// #include "send_mosq.h"
// #include "sys_tree.h"
// #include "util_mosq.h"

#ifndef __cplusplus
extern "C" {
#endif

// typedef struct policy_engine policy_engine;

policy_engine* new_policy_engine();
invariant_engine* new_invariant_engine();
bool initialize_db_policy_engine();
vector<string> read_policy_file(char* policy_fname);
vector<pair<string,string>> read_invariant_file(char* inv_fname);
// bool policy_engine_add_policy(policy_engine* pengine, char* raw_policy);

// bool policy_engine_monitor(policy_engine *pengine, struct mosquitto* context, struct mosquitto_msg_store * msg);
bool policy_engine_monitor(struct mosquitto_msg_store* msg);
vector<pair<string,void*> invariant_engine_monitor(struct mosquitto_msg_store* msg);
pl_engine* new_pl_engine();
#ifndef __cplusplus
}
#endif
#endif