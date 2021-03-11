#ifndef __SYSTEM_STATE_H__
#define __SYSTEM_STATE_H__

#include "headers.h"

class system_state{
    std::map<std::string, void*> state_map;

    public:
    system_state();
    bool update_state(std::string state_var, void* item);
    void* retrieve_state(std::string state_var);

};
#endif
