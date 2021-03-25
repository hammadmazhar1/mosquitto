#include "system_state.h"

system_state::system_state(){
    state_map.clear();
}
bool system_state::update_state(std::string state_var, void* item){
    //make a copy of the item to prevent loss by mem free ops and assign to key
    if (state_var.find("int_") != std::string::npos){
        int* x = new int;
        *x = *(int*) item;
        state_map[state_var] = (void*) x;
    }else if (state_var.find("bool_") != std::string::npos){
        bool* x = new bool;
        *x = *(bool*) item;
        state_map[state_var] = (void*) x;
    } else if(state_var.find("str_") != std::string::npos){
        char* x = new char[1024];
        strncpy(x, (char*) item,1024);
        state_map[state_var] = (void*) x;
    } else{
        return false;
    }
    return true;
    
}
void* system_state::retrieve_state(std::string state_var){
    if (state_map.find(state_var) == state_map.end()){
        return NULL;
    }else{
        return state_map[state_var];
    }
}