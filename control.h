#ifndef CONTROL_H
#define CONTROL_H
 
#include "tm4c123gh6pm.h"
#include "delay.h" 
 
 void Leds_off(){ //Disabling Leds 

 GPIO_PORTF_DATA_R &=~  0x0E; 

 }

 void Leds_on(){ // enabling leds

	 GPIO_PORTF_DATA_R |=  0x0E;

 } 

	void Led_Buzzer_Blinking(){   //toggling the leds
	GPIO_PORTD_DATA_R ^= 0x04;
	GPIO_PORTF_DATA_R ^= 0x0E; 

}
	void Led_Blinking(){ //Toggling the Leds
	GPIO_PORTF_DATA_R ^= 0x0E; 
	
	}

 void end_of_Operation(){  //called in the End Case

		int i;

	for(i =0;i<=5;i++){ 

		Led_Buzzer_Blinking();
		Systick_ms(500);
 }
} 
 void buzzer_init(void){
	SYSCTL_RCGCGPIO_R |= 0x08;
	while ((SYSCTL_PRGPIO_R &0x08)==0);
	
	GPIO_PORTD_LOCK_R = 0x4C4F434B;
	GPIO_PORTD_AMSEL_R &=~ 0x04;
	GPIO_PORTD_CR_R |= 0x04;
	GPIO_PORTD_PCTL_R &=~ 0x00000F00;
	GPIO_PORTD_AFSEL_R &=~ 0x04;
	GPIO_PORTD_DIR_R |= 0x04;
	GPIO_PORTD_DEN_R |= 0x04;
	GPIO_PORTD_DATA_R &=~ 0x04;
}
void RGB_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x20;
	while ((SYSCTL_PRGPIO_R &0x20)==0);
	GPIO_PORTF_LOCK_R = 0x4C4F434B; 
	GPIO_PORTF_AMSEL_R &=~ 0x0E; 
	GPIO_PORTF_CR_R |= 0x0E; 
	GPIO_PORTF_PCTL_R &=~ 0x0000FFF0;
	GPIO_PORTF_AFSEL_R &=~ 0x0E; 
	GPIO_PORTF_DIR_R |= 0x0E; 
	GPIO_PORTF_DEN_R |= 0x0E;
	GPIO_PORTF_DATA_R |= 0x0E;
}


#endif
