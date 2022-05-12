 void Leds_off(){ //Disabling Leds 

 GPIO_PORTF_DATA_R &=~  0x0E; 

 }

 void Leds_on(){ // enabling leds

	 GPIO_PORTF_DATA_R |=  0x0E;

 } 

  void Buzzer_toggle(){ // toggling the buzzer

	   GPIO_PORTA_DATA_R ^= 0x01; 

 }

	void Led_Blinking(){   /toggling the leds

	GPIO_PORTF_DATA_R ^= 0x0E; 

}

 void end_of_Operation(){  // should be called when countdown is equal to zero (end Case ) ( if     ((NVIC_ST_CTRL_R & 0x000100000) == 0x01);  ))))))

	 int i;


for(i =0;i<=5;i++){ 

	Led_Blinking();

	Buzzer_toggle();

	 Systick_ms(1000);

 }

} 

