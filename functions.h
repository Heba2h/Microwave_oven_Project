#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdbool.h>

bool Valid_Check(char c){
		char i = '1';
		for (i = '1';i<= '9';i++){
			if (c == i){ 
				return true;
			}			
		}
		return false;	
}

bool Timer_Check(int t){
		return (( t >= 1 && t <= 1800) == 1 )? 1:0;
}
#endif
