#include <stdbool.h>

bool Error_Check(unsigned char c){
		unsigned char i = '1';
		for (i = '1';i<= '9';i++){
			if (c == i){ 
				return true;
				break;
			}			
		}
		return false;	
}