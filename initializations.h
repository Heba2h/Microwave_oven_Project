#include "tm4c123gh6pm.h"
//paramertrized intialization function for Clean Code Purposes and avoiding code redudncy
// example for Led init : pin_init(0x100000,0x0E,0x0E,0x0E)
//example for Buzzer init : pin_init(0x000001,0x000001,0x000001,0x000000) Buzzer placed on Port A ,first pin , output , Off Status
//the function includes (PCTL , Lock , Den ,Amsel , ASfel , CR_R, DIR, Data) registers only... To modifiy any other register you have to add it
//PCTL_R = 0x00000000; no alternate functions
//LOCK_R = 0x4C4F434B;  ports should be unlocked
//DEN_R |= 0x1F; the project is digital only
//AMSEL_R &=~ 0x1F;  no analog pins in the project
//AFSEL_R &=~ 0x1F; no alternate function used in the project 

void pin_init(int port_number, int changable_pins, int pins_direction, int data){
	SYSCTL_RCGCGPIO_R |= port_number; //Port enablization
    while ((SYSCTL_PRGPIO_R & port_number)==0); // Waiting for stablization
	switch (port_number)
	{
		case 0x000001:
				GPIO_PORTA_PCTL_R = 0x00000000;
				GPIO_PORTA_LOCK_R = 0x4C4F434B;
				GPIO_PORTA_DEN_R |= 0x1F;
				GPIO_PORTA_AMSEL_R &=~ 0x1F; 
				GPIO_PORTA_AFSEL_R &=~ 0x1F; 
				GPIO_PORTA_CR_R |= changable_pins;
				GPIO_PORTF_DIR_R |= pins_direction; 
				GPIO_PORTF_DATA_R |= data;
			break;
		case 0x000010:
				GPIO_PORTB_PCTL_R = 0x00000000;
				GPIO_PORTB_LOCK_R = 0x4C4F434B;
				GPIO_PORTB_DEN_R |= 0x1F;
				GPIO_PORTB_AMSEL_R &=~ 0x1F; 
				GPIO_PORTB_AFSEL_R &=~ 0x1F;
				GPIO_PORTB_CR_R |= changable_pins;
				GPIO_PORTF_DIR_R |= pins_direction; 
				GPIO_PORTF_DATA_R |= data;
		break;
			case 0x000100:
				GPIO_PORTC_PCTL_R = 0x00000000;
				GPIO_PORTC_LOCK_R = 0x4C4F434B;
				GPIO_PORTC_DEN_R |= 0x1F;
				GPIO_PORTC_AMSEL_R &=~ 0x1F; 
				GPIO_PORTC_AFSEL_R &=~ 0x1F;
				GPIO_PORTC_CR_R |= changable_pins;
				GPIO_PORTF_DIR_R |= pins_direction; 
				GPIO_PORTF_DATA_R |= data;
			break;
			case 0x001000:
					GPIO_PORTD_PCTL_R = 0x00000000;
					GPIO_PORTD_LOCK_R = 0x4C4F434B;
					GPIO_PORTD_DEN_R |= 0x1F;
					GPIO_PORTD_AMSEL_R &=~ 0x1F; 
					GPIO_PORTD_AFSEL_R &=~ 0x1F;
					GPIO_PORTD_CR_R |= changable_pins;
					GPIO_PORTF_DIR_R |= pins_direction; 
					GPIO_PORTF_DATA_R |= data;
			break;
			case 0x010000:
					GPIO_PORTE_PCTL_R = 0x00000000;
					GPIO_PORTE_LOCK_R = 0x4C4F434B;
					GPIO_PORTE_DEN_R |= 0x1F;
					GPIO_PORTE_AMSEL_R &=~ 0x1F; 
					GPIO_PORTE_AFSEL_R &=~ 0x1F;
					GPIO_PORTE_CR_R |= changable_pins;
					GPIO_PORTF_DIR_R |= pins_direction; 
					GPIO_PORTF_DATA_R |= data;
			break;
			case 0x100000:
				GPIO_PORTF_PCTL_R = 0x00000000;
				GPIO_PORTF_LOCK_R = 0x4C4F434B;
				GPIO_PORTF_DEN_R |= 0x1F;
				GPIO_PORTF_AMSEL_R &=~ 0x1F;
				GPIO_PORTF_AFSEL_R &=~ 0x1F;
				GPIO_PORTF_CR_R |= changable_pins;
				GPIO_PORTF_DIR_R |= pins_direction; 
				GPIO_PORTF_DATA_R |= data;
			break;
	}
}
