#ifndef __HEADERS_H__
#define __HEADERS_H__
# include <cstdio>
# include <cstring>
# include <cstdlib>
# include <vector> 
# include <iostream> 
# include <fstream>
// $ include <ifstream>
# include <sstream>
# include <map> 
# include <string> 
# include <cassert> 
# include <stack> 
# include <set>
using namespace std; 


typedef int nodeType ; 
typedef int arrayIndex ;
typedef int pl_nodeType ; 

const int prop = 0 , LNOT = 1, historically = 2 , yesterday = 3 , once = 4 , 
LIMPLY = 5 , LAND = 6 , LOR = 7, since = 8, LPAREN=9, COMMA=10, 
RPAREN=11, LTRUE=12, LFALSE=13, state=14, EQUAL =15, NEQUAL =16,
LESS=17,MORE=18, LEQ=19,MEQ=20,PREV=21,CUR=22,CONSTANT_INT=23, CONSTANT_BOOL=24,
CONSTANT_STR=25  ; 

#endif 
