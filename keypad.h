#ifndef KEYPAD_H
#define KEYPAD_H
#include "tm4c123gh6pm.h"
void SystemInit ()
{
SYSCTL_RCGCGPIO_R |= 0x14;            //enable clc for port C & D  
  while ((SYSCTL_RCGCGPIO_R&0x14)==0);  //wait for clock to be enabled
  GPIO_PORTC_CR_R  |= 0xF0;             //allow changes to all the bits in port C
  GPIO_PORTE_CR_R  |= 0x1E;             //allow changes to all the bits in port E
  GPIO_PORTC_DIR_R |= 0xF0;             //set directions cols are o/ps
  GPIO_PORTE_DIR_R |= 0x00;             //set directions raws are i/ps
  GPIO_PORTE_PDR_R |= 0x1E;             //pull down resistor on Raws
  GPIO_PORTC_DEN_R |= 0xF0;             //digital enable pins in port C
  GPIO_PORTE_DEN_R |= 0x1E;             //digital enable pins in port E
}


char elements[4][4]={{'1','2','3','A'},
                     {'4','5','6','B'},  // keypads elements
										 {'7','8','9','C'},
                     {'*','0','#','D'}
                                      };
char pressed()
	{ int i;
	int j;
  while(flag != 1)
  {
    for(j=0;j<4;j++){
			GPIO_PORTC_DATA_R=(0X10<<j); // 0001 0000
			Systick_ms(2);
			for(i=0;i<4;i++)
			{
				if((GPIO_PORTE_DATA_R&0x1E)&(0x02<<i)) //0000 0010
					return elements[i][j];
		}
	}}}
	#endif