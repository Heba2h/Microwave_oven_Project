#ifndef SWITCHES_H
#define SWITCHES_H

#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include <TM4C123.h>

	
void sw_Init(void){//pin f4, f0
		SYSCTL_RCGCGPIO_R |= 0x20; //1) initialize the clock of portf
		while((SYSCTL_PRGPIO_R & 0x20) == 0); //Delay
		GPIO_PORTF_LOCK_R = 0x4C4F434B; //2) unlock portf
		GPIO_PORTF_AMSEL_R &= ~0x11; //3) disable analog fuction
		GPIO_PORTF_CR_R |= 0x11; //set pin pf4 to change
		GPIO_PORTF_PCTL_R &= ~0x000F000F; //4)enable digital function
		GPIO_PORTF_AFSEL_R &= ~0x11; //5) disable alternate function
		GPIO_PORTF_DIR_R &= ~0x11; //6) pf4 is input
		GPIO_PORTF_DEN_R |= 0x11; //7) enable digital for sw1 & sw2
		GPIO_PORTF_PUR_R |= 0x11; //active low
	
		//interrupt for sw1 and sw2
	//GPIOIS: Interrupt sense (0: edge) (1: level)
		GPIO_PORTF_IS_R &= ~0x11;  //pf4 and pf0 is edge sensitive
	//GPIOIBE: Interrupt both edges (0: one edge) (1: both edges)
		GPIO_PORTF_IBE_R &= ~0x11; //pf4 and pf0 is not both edges
	//GPIOIEV: Interrupt Event (0: falling event) (1: rising event)
		GPIO_PORTF_IEV_R &= ~0x11; //pf4 and pf0 is a falling edge event
	//GPIOICR: Interrupt clear (1: clear interrupt flags) 
		GPIO_PORTF_ICR_R |= 0x11; //clear flags
	//GPIOIM: Interrupt mask (determine which pin the interrupt will come from)
		GPIO_PORTF_IM_R |= 0x11; //arm interrupt on pf4 and pf0
	
		//interrupt will come from pf4
	//PRI7: used to prioritize the interrupts 
	// (interrupt with the highest priority number will be executed first)
		NVIC_PRI7_R = ((NVIC_PRI7_R & 0xFF00FFFF) | (0x00A00000)); //priority 5
	//
		NVIC_EN0_R |= 0x40000000; //enable interrupt 30 in NVIC //interrupt for port f
		__enable_irq(); //enable global interrupt
}
//PRI7: for interrupts 28-31    //PRI0: for interrupts 0-3
//EN0: for interrupts 0-31

void sw3_Init(void){ //pin a7
		SYSCTL_RCGCGPIO_R |= 0x01; //initialize the clock for port a
		while((SYSCTL_PRGPIO_R & 0x01) == 0);//Delay
		GPIO_PORTA_AMSEL_R &= ~(0x80);// disable analog function
		GPIO_PORTA_CR_R |= 0x80; //allow changes for pa7
		GPIO_PORTA_PCTL_R &= ~0xF0000000; //enable digital function
		GPIO_PORTA_AFSEL_R &= ~0x80; //disable alternate function
		GPIO_PORTA_DIR_R &= ~0x80; //pa7 is input
		GPIO_PORTA_DEN_R |= 0x80; //enable digital for sw3
		GPIO_PORTA_PUR_R |= 0x80; //active low
	
		//interrupt
		GPIO_PORTA_IS_R &= ~0x80;  //pa7 is edge sensitive
		GPIO_PORTA_IBE_R &= ~0x80; //pa7 is not both edges
		GPIO_PORTA_IEV_R &= ~0x80; //pa7 is a falling edge event
		GPIO_PORTA_ICR_R |= 0x80; //clear flags
		GPIO_PORTA_IM_R |= 0x80; //arm interrupt on pf4
		//interrupt will come from pf4
		NVIC_PRI0_R = ((NVIC_PRI0_R & 0xFFFFFF00) | (0x000000E0)); //priority 7
		NVIC_EN0_R |= 0x00000001; //enable interrupt 0 in NVIC //interrupt for port A
		__enable_irq();
}

unsigned char sw1_input(void){ //pf4 check
		return GPIO_PORTF_DATA_R&0x10;
}

unsigned char sw2_input(void){// pf0 check
		return GPIO_PORTF_DATA_R&0x01;
}
unsigned char sw3_input(void){ //pa7 check
		return GPIO_PORTA_DATA_R&0x80;
}
bool sw1_pressed(void){ //check if sw1 is pressed
		if(sw1_input() != 0x10){
				return true;
		}
		else{
				return false;
		}
}
bool sw2_pressed(void){ //check if sw2 is pressed
		if(sw2_input() != 0x01){
				return true;
		}
		else{
				return false;
		}
}
bool sw3_pressed(void){ //check if sw3 is pressed
		if(sw3_input() != 0x80){
				return true;
		}
		else{
				return false;
		}
}
void GPIOF_Handler(void){
		if(state == Time_Display){
				while(1)
				{
				if(sw1_pressed()){
						GPIO_PORTF_ICR_R |= 0x11;
						goto Time_Display;
				}
				if(sw2_pressed()){
				GPIO_PORTF_ICR_R |= 0x11;
				goto exit;
				}
				}
		}
		if(state == cooking){
		while(~sw2_pressed() || (~sw1_pressed()) ){};
		if(sw1_pressed()) 
		{
				GPIO_PORTF_ICR_R |= 0x11;
				goto Idle;
		}
	}
		GPIO_PORTF_ICR_R |= 0x11;
}
void GPIOA_Handler(void){
        while(sw3_pressed()){}
        while(~sw2_pressed()){}
        GPIO_PORTA_ICR_R |= 0x80;
}

#endif
