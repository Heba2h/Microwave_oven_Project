#ifndef INTERRUPTS_HANDLERS_H
#define INTERRUPTS_HANDLERS_H

#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include <TM4C123.h>
#include "LCD.h"
#include "control.h"
#include "functions.h"


#define VECTKEY_Pos 16
#define SYSRESETREQ_Msk (1UL << 2)


extern int time;
extern int flag;
extern char num[4];
extern char key;
extern bool check;
extern int previous_state;
extern int state ;
extern int ready;



void Counting_Down(int time);


void GPIOF_Handler(){
	if (ready ==1){
	 if ((GPIO_PORTF_MIS_R & 0x01)) /* check if interrupt is caused by PF0/SW2 */
    {
			
			RGB_Init();
			Leds_on();			
		  LCD_cmd(clear);
			
			if (state ==5 ){
				check = Timer_Check(time);
			if (check == 0){
				previous_state = state;
				state = 6;
			}
		}
			Counting_Down(time);
			flag =1;
		}
		
		else if ((GPIO_PORTF_MIS_R & 0x10) && key == 'D')
		{
			LCD_time();		
		}
		
	}
	GPIO_PORTF_ICR_R |= 0x11;
}

void SystemReset(void){
	NVIC_APINT_R = ((0x5FA << VECTKEY_Pos) | (SYSRESETREQ_Msk));
	while(1){};
}

#endif
