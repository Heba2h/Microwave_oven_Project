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
											if (/*sw2 is pressed*/){
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
}