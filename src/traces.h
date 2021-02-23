#ifndef __TRACES_H__
#define __TRACES_H__

# include "headers.h" 

typedef std::vector< std::set< std::string > > sigma;


struct TRACE{

	sigma s ; 

	TRACE()
	{
		s.clear(); 
	}
	
	int getSize()
	{
		return s.size(); 
	}	

	bool isTrue(std::string prop, int pos)
	{
		if(pos >= s.size()) return false ;
		std::set<std::string>::iterator it = s[pos].find(prop) ; 
		if(it == s[pos].end())return false;
		return true; 
	}
	void addState(std::set<std::string> st)
	{
		s.push_back(st ); 
	}
	

};

typedef struct TRACE trace;

void readTrace(FILE *ftrace, trace &ctrace)
{
	char buff[1024], token[1024]; 
	ctrace.s.clear() ; 	
	while(fgets(buff, 1024, ftrace))
	{
		#ifdef DEBUG
			printf("GOT: %s\n", buff);
		#endif 

		std::set< std::string> tempString ; 
		char * ptr = strtok(buff, " 	\n") ; 
		while(ptr)
		{
			tempString.insert(std::string(ptr)) ; 
			ptr = strtok(NULL," 	\n") ; 
		}
		ctrace.addState(tempString); 
	}
}




#endif 
