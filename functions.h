#ifndef FUNCTIONS
#define FUNCTIONS

#include <stdbool.h>

bool Valid_Check(char c){
		char i = '1';
		for (i = '1';i<= '9';i++){
			if (c == i){ 
				return true;
				break;
			}			
		}
		return false;	
}

bool Timer_Check(int t){
		if ( t >= 60 && t <= 1800 ){
	
			return true;
		}
		return false;
}
#endif
