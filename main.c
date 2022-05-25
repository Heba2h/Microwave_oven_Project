#include "tm4c123gh6pm.h"
#include "LCD_time.h"
#include "LCD.h"
#include "Keypad.h"
#include "Counting_Down.h"
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


/**
*  @detailed  In this project ,We are aiming to implement a Microwave System 
* 						firsly, flages gonna be clarified:
*             (flag -> refers to sw2 (start button)
*             ,flag2 -> refers to sw1 (start button)             
*             ,flag3 -> refers to sw3 (start button), 
*							,check -> returns a bool of check funtion in state 'Time_Display'
*											  to check the validation of inputs
*							,ready -> ready is flaged to 1 when its time to start cooking.
*												We made this flag because sw2 is interrupt so it can 
*  											be used anywhere in the code, so to limit its fuctionality 
*												and make sw2 do not affect the whole program and dont go 
*                       immediately to cooking state & stay in same state till its time to cook.)
*							Secondly, main operations will be explained:
*             The main starts by intializing then taking in put from user to go to a specific case
*             and runs its scope till it reach to end state and restarts from the begining. 
*
*  @param     All function registers are defined in "tm4c123gh6pm.h" file
*/


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
          LCD_PrintStr("Choose a Program");					
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
		case Popcorn:
					 time = 60;
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
					if (state !=Error){
					state = End;
					}
		      			flag = 0;			
					break;
		
		 case Error:
					Leds_off();
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
				LCD_PrintStr(" Happy Meal ^_^");
				end_of_Operation(); // Toggling Leds and Buzzer for 3 seconds
				state = Idle;
				break;

	      }		
    } 
}
