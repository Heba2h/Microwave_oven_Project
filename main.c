#include "tm4c123gh6pm.h"
#include "LCD_time.h"
#include "LCD.h"
#include "keypad.h"
#include "Counting_Down.h"
#include "initializations.h"
#include "functions.h"
#include "switches.h"
#include "control.h"
#include "delay.h"

enum state{Idle, Popcorn, Beef, Chicken, Custom, Time_Display, Error, Cooking, Pause, Door_Check, End};
	
int time = 0;
char key;
int previous_state;
int state = Idle;
int flag;
int flag2;
int flag3;
int x;
int flagD;
//char num[4];

int main(){
	SysTick_Init();
	LCD_init1();
	LCD_init2();
	SystemInit();
	sw_Init();
	sw3_Init();
  	buzzer_init(); //Buzzer placed on Port A ,first pin , output , off Status+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
	while(1){
		switch(state){
						  
						case	Idle:	
										LCD_cmd(clear);
										Leds_off();
										LCD_PrintStr("Choose Program");
										//LCD_cmd(cursor_at_2ndline);
										//LCD_PrintStr("to Start Op");
		
					
												 while(1)
														{
														key = pressed();
																switch (key)
																{
																	case 'A' :
																	LCD_cmd(clear);
																				state = Popcorn; 
																	//LCD_PrintStr("Popcorn");
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
															if(state != Idle){
																	break;
															}
														}
													
										break;
									
						case Popcorn:
										time = 10;
										LCD_PrintStr("Popcorn");
										Systick_ms(2000);
										while(flag ==0){};
										if (state == 0){
											break;
										}
										state = End;										
										flag = 0;
										break;
					case	Beef:
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
											while(flag ==0){};
												
											state = End;
											flag = 0;
																	
										}
										else{
											previous_state = state;
											state = Error;
										}
										break;
					case	Chicken:
										LCD_PrintStr("Chicken Weight?");
										key = pressed();
										if (Valid_Check(key) == 1){
											LCD_cmd(cursor_at_2ndline);
											LCD_PrintStr("Weight = ");
											LCD_data(key);
											Systick_ms(2000);
											time = (key - '0')*12; // rate = 60*0.2 in seceonds
											LCD_cmd(clear);
											LCD_PrintStr("Please Press SW2");
											while(flag ==0){};
											state = End;
											flag = 0;									
										}
										else{
											previous_state= state;
											state = Error;
										}
										break;
					case	Custom:
										LCD_PrintStr("Cooking Time?");
										Systick_ms(2000);
										state = Time_Display;
										break;
					case	Time_Display:
										LCD_cmd(clear);
										Systick_ms(500);
										LCD_time();
										time = Time_Entry();
										if (Timer_Check(time) == 1){
											previous_state= state;
											state = Error;
										}
										break;
				case		Error:
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
				case		Cooking:
										LCD_init2();
										
										Counting_Down(time);
										state = End;
										break;
//						Pause:
//										 while(1){
//											if (sw2_pressed()){
//													state = Cooking;
//													break;
//											 }
//											if (sw3_pressed()){
//													previous_state= state;
//													state = Door_Check;
//													break;
//											 } 
//											if (sw1_pressed()){
//													state = Idle;
//													break;
//											 }
//											//display time stays the same
//												Led_Blinking();
//												Systick_ms(1000);
//										 }
//										 break;
//									 
//				 		Door_Check:
//										  while(1){
//												if ( ~(sw3_pressed()) ){
//													switch(previous_state){
//														case Pause:
//															state = Pause;
//															break;
//														case Cooking:
//															state = Cooking;
//															break;
//													}
//												}
//												Led_Blinking()
//												Systick_ms(1000);
//											}
//											break;
						case	End:
							        LCD_init2();
							      	//Buzzer_ON(); // el mafrood tb2a enable*****
											end_of_Operation(); // Toggling Leds and Buzzer for 3 seconds
											state = Idle;
											break;

		}
		

		
}
}
