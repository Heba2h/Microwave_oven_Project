#ifndef KEYPAD_H
#define KEYPAD_H
#include "tm4c123gh6pm.h"
/**
*  @author      Honda123987
*  @detailed    This fuction return the initialization of the keypad i took the 4 bins of Port C  4 pins of Port E 
*  @Hardware
* 		[PE1 - PE4] -> [R1 - R4]  Raws
* 		[PC4 - PC7] -> [C1 - C4]  Cols
*  
*  @param       All function registers are defined in "tm4c123gh6pm.h" file
*/
void SystemInit ()
{
SYSCTL_RCGCGPIO_R |= 0x14;              //enable clc for port C & E  
  while ((SYSCTL_RCGCGPIO_R&0x14)==0);  //wait for clock to be enabled
  GPIO_PORTC_CR_R  |= 0xF0;             //allow changes to all the bits in port C
  GPIO_PORTE_CR_R  |= 0x1E;             //allow changes to all the bits in port E
  GPIO_PORTC_DIR_R |= 0xF0;             //set directions for pins [PC4-PC7] which are used as coloums to be o/ps
  GPIO_PORTE_DIR_R &= ~0x1E;             //set directions for pins [PE1-PE4] which are used as raws to be i/ps
  GPIO_PORTE_PDR_R |= 0x1E;             //pull down resistor on Raws 
  GPIO_PORTC_DEN_R |= 0xF0;             //digital enable pins [PC4-PC7] in port C
  GPIO_PORTE_DEN_R |= 0x1E;             //digital enable pins [PE1-PE4] in port E
}


char elements[4][4]={{'1','2','3','A'},
                     {'4','5','6','B'},  // keypads elements
	             {'7','8','9','C'},
                     {'*','0','#','D'}
                                      };
/**
* @detailed   This function returns the value of a key have been pressed at the moment the function had been called. 
*             It simply makes a 2 nested loops one to apply +3.3 v (digital output) to the keypad's coloums one by one 
*	      and the second one read each keypad's row (digital inputs) one by one and if it read 1 from a raw it means
*             that this raw contain apresses button and by knowing from the first loop which coloum on it the +3.3 v is applied
*             we will be able to determine which button is pressed at this moment.	    
*             had been pressd and another loop to determine the row of that button. 
* @ returns   this function return the pressed key on the keypad         
*/
char pressed()
	{ int i;
	int j;
  while(flag != 1)
  // while SW2 not pressed
  {
    for(j=0;j<4;j++)
 // to apply +3.3 v (digital output) to the keypad's coloums one by one
		{
			GPIO_PORTC_DATA_R=(0X10<<j);      
			Systick_ms(2);
			for(i=0;i<4;i++)
            //	read each keypad's row (digital inputs) one by one 		

			{
				if((GPIO_PORTE_DATA_R&0x1E)&(0x02<<i)) 
					return elements[i][j];  //return the pressed key
		}
	}}}
	#endif