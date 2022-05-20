#include "tm4c123gh6pm.h"
#include "LCD_time.h"
#include "LCD.h"
#include "Keypad.h"
#include "Counting_Down.h"
#include "initializations.h"
#include "functions.h"
#include "switches.h"
#include "control.h"
#include "delay.h"
#include "interrupts_handlers.h"


enum state{Idle, Popcorn, Beef, Chicken, Custom, Time_Display, Error,End};
	
int time ;
char key;
int previous_state;
int state = Idle;
int flag;
int flag2;
int flag3;
bool check;
int ready;


int main(){
	SysTick_Init();
	LCD_init1();
	LCD_init2();
	SystemInit();
	sw_Init();
	sw3_Init();
  buzzer_init();

	while(1){
		check= true;
		ready=0;
		switch(state){
						  
		case Idle:	
					LCD_cmd(clear);
					Leds_off();
	      	time = 0;
          LCD_PrintStr("Choose Program");					
           while(1)
						{
						   key = pressed();
						   switch (key)
    {
                case 'A' :
								LCD_cmd(clear);
								state = Popcorn; 
								break;
							case 'B':
								LCD_cmd(clear);
                state = Beef; 
                break;
							case 'C':
								LCD_cmd(clear);
								state = Chicken; 
								break;
							case 'D':
                LCD_cmd(clear);
								state = Custom; 
								break;
							    }
						  if(state != Idle)
								break;							
						 }
													
						break;
			// flag for sw2 						
		case Popcorn:
					 time = 5;
					 LCD_PrintStr("Popcorn");
					 Systick_ms(2000);
	         ready=1;
					 while(flag ==0){}				 			
					 state = End;										
					 flag = 0;
					 break;
		case Beef:
				         LCD_PrintStr(" Beef Weight?");
                 key = pressed();
					    	if (Valid_Check(key) == 1){
							LCD_cmd(clear);
							LCD_PrintStr("  Weight = ");
							LCD_data(key);
							Systick_ms(2000);
							time = (key - '0')*30; // rate = 60*0.5 in seceonds
							LCD_cmd(clear);
							LCD_PrintStr("Please Press SW2");
							ready=1;
							while(flag ==0){};
							state = End;
							flag = 0;
							}
						 else{
							previous_state = state;
							state = Error;
							}
					     break;
		case Chicken:
					LCD_PrintStr("Chicken Weight?");
					key = pressed();
					if (Valid_Check(key) == 1){
						LCD_cmd(clear);
						LCD_PrintStr("Weight = ");
						LCD_data(key);
						Systick_ms(2000);
						time = (key - '0')*12; // rate = 60*0.2 in seceonds
						LCD_cmd(clear);
						LCD_PrintStr("Please Press SW2");
						ready=1;
						while(flag ==0){};
						state = End;
						flag = 0;									
					}
					else{
						previous_state= state;
						state = Error;
					}
					break;
		 case Custom:
					LCD_PrintStr("Cooking Time?");
					Systick_ms(2000);
					state = Time_Display;
					break;
		 
		 
	  case Time_Display:
			
					LCD_cmd(clear);
					Systick_ms(500);
					LCD_time();
		      ready=1;
					time = Time_Entry();
		      flag = 0;			
					break;
		
		 case Error:
					LCD_cmd(clear);
					LCD_PrintStr("Err");
					Systick_ms(2000);
					LCD_cmd(clear);
					LCD_PrintStr(" Please enter a");
					LCD_cmd(cursor_at_2ndline);
					LCD_PrintStr("  valid number");
					Systick_ms(2000);
					LCD_cmd(clear);
					state = previous_state;
					break;
									 
		 case End:
				LCD_init2();
				end_of_Operation(); // Toggling Leds and Buzzer for 3 seconds
				state = Idle;
				break;

	         	}		
                 } 
							 }
