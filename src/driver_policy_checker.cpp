# include "policy_adder.h"
# include "headers.h" 


int main(int argc, char *argv[])
{	
	policy_engine * pengine = new policy_engine ; 

	char * ptr = new char[1024]; 
	strcpy(ptr, "&(a, !(b))") ; 

	pengine->add_policy(ptr) ; 


	sys_state st ; 

	 
	st.s.insert(std::string("a")) ; 
	st.s.insert(std::string("c")) ;

	if(pengine->monitor(st)) printf("[CORRECT ANSWER]: Policy check successful\n");
	else printf("[INCORRECT ANSWER]: Policy check unsuccessful\n") ;

	st.s.clear(); 
	st.s.insert(std::string("a")) ; 
	st.s.insert(std::string("b")) ;

	if(pengine->monitor(st)) printf("[INCORRECT ANSWER]: Policy check successful\n");
	else printf("[CORRECT ANSWER]: Policy check unsuccessful\n") ;


	delete pengine ; 

	return 0 ; 
}
