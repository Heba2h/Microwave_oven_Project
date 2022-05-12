#ifndef tm4c123gh6pm_h
#define tm4c123gh6pm_h

#ifndef LCD_time_h
#define LCD_time_h

#ifndef LCD_h
#define LCD_h

#ifndef keypad_h
#define keypad_h

#ifndef Counting_Down_h
#define Counting_Down_h

#ifndef initializations_h
#define initializations_h

#ifndef switches.h
#define switches.h

#endif

enum state{Idle, Popcorn, Beef, Chicken, Custom, Time_Display, Error, Cooking, Pause, Door_Check, End};
	
int main(){
	int state = Idle;
	int prevoius_state;
	while(1){
		switch(state){
						Idle: 
										Leds_off();
										while(1){
											if (sw2_pressed()){
												while(1){
													if ( pressed() == 'A'){
														state = Popcorn;
														break;
													}
													if ( pressed() == 'B'){
														state = Beef;
														break;
													}
													if ( pressed() == 'C'){
														state = Chicken;
														break;
													}
													if ( pressed() == 'D'){
														state = Custom;
														break;
													}
													
												}
											}
											if( state != Idle){
												break;
											}
										}
										break;
									
						Popcorn:
										LCD_PrintStr("Popcorn");
										//counting down function
										state = Cooking;
										break;
						Beef:
										LCD_PrintStr("Beef Weight?");
										if (Error_Check(pressed()) == 1){
											LCD_data(pressed());
											Systick_ms(2000);
											int new_time = (pressed() - '0')*30; // rate = 60*0.5 in seceonds
											//counting down function
											state = Cooking;									
										}
										else{
											prevoius_state= state;
											state = Error;
										}
										break;
						Chicken:
										LCD_PrintStr("Chicken Weight?");
										if (Error_Check(pressed()) == 1){
											LCD_data(pressed());
											Systick_ms(2000);
											int new_time = (pressed() - '0')*12; // rate = 60*0.2 in seceonds
											//counting down function
											state = Cooking;									
										}
										else{
											prevoius_state= state;
											state = Error;
										}
										break;
						Custom:
										LCD_PrintStr("Cooking Time?");
						Time_Display:
										LCD_time();
										Time_Entry();//need to be modified lcd_time in time_entry
										//show how to go to error if more than 30 minuits
										state = Cooking;
										//else
										prevoius_state= state;
										break;
		}
	}
Error:
										LCD_PrintStr("Err");
										Systick_ms(2000);
										LCD_PrintStr("Please enter a valid number");
										Systick_ms(2000);
										switch(prevoius_state){
											case Chicken:
												state = Chicken;
												break;
											case Beef:
												state = Beef;
												break;
											case Custom:
												state = Custom;
												break;
										};
										
						Cooking:
										pin_init(0x100000,0x0E,0x0E,0x0E) // LEDs' Pins intiallized and leds are enabled
										//counting down function
										if(/sw1 is pressed/){state = Pause;}
										if (/sw3 is pressed/){
										prevoius_state= state;
										state = Door_Check;
										}
										state = End;
						Pause:
										 while(1){
											if ( /sw2 is pressed/){
													state = Cooking;
													break;
											 }
											if ( /sw3 is pressed/){
													prevoius_state= state;
													state = Door_Check;
													break;
											 } 
											if ( /sw1 is pressed/){
													state = Idle;
													break;
											 }
											//display time stays the same
												Led_Blinking();
												Systick_ms(1000);
										 }
										 break;
									 
				 		Door_Check:
										  while(1){
												if (/sw3 is not pressed/){
													switch(prevoius_state){
														case Pause:
															state = Pause;
															break;
														case Cooking:
															state = Cooking;
															break;
													}
												}
												Led_Blinking()
												Systick_ms(1000);
											}
											break;
							End:
											pin_init(0x000001,0x000001,0x000001,0x000000) //Buzzer placed on Port A ,first pin , output , off Status
											end_of_Operation(); // Toggling Leds and Buzzer for 3 seconds
											state = Idle;
											Leds_off();
											break;

		}
}
}
