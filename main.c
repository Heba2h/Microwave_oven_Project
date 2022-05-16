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

// void GPIOF_Handler(void){
//         if(state == Time_Display){
//                 while(1)
//                 {
//                 if(sw1_pressed()){
//                         GPIO_PORTF_ICR_R = 0x11;
//                         goto Time_Display;
//                 }
//                 if(sw2_pressed()){
//                 GPIO_PORTF_ICR_R = 0x11;
//                 goto exit;
//                 }
//                 }
//         }
//         if(state == Cooking){
//         while(~sw2_pressed() || (~sw1_pressed()) ){};
//         if(sw1_pressed()) 
//         {
//                 GPIO_PORTF_ICR_R = 0x11;
//                 goto Idle;
//         }
//     }
//         GPIO_PORTF_ICR_R = 0x11;
// }


int main(){
	SysTick_Init();
	LCD_init1();
	LCD_init2();
	SystemInit();
	sw_Init();
	sw3_Init();
	
	while(1){
		switch(state){
						Idle: 
								Leds_off();
										LCD_PrintStr("Please Press SW2");
										LCD_cmd(cursor_at_2ndline);
										LCD_PrintStr("to Start Op");
										while(1){
												if (sw2_pressed())
														{
												 while(1)
														{
															key = pressed();
																switch (key)
																{
																	case 'A' :
																				state = Popcorn; 
																		break;
																	case 'B':
																				state = Beef; 
																		break;
																	case 'C':
																				state = Chicken; 
																		break;
																	case 'D':
																				state = Custom; 
																		break;
																}
														}
												}
												if( state != Idle){  // di eh lazmtaha
														break;
												}
										}
										break;
									
						Popcorn:
										LCD_PrintStr("Popcorn");
										Systick_ms(2000);
										time = 60;
										state = Cooking;
										break;
						Beef:
										LCD_PrintStr("Beef Weight?");
										key = pressed();
										if (Valid_Check(key) == 1){
											LCD_cmd(cursor_at_2ndline);
											LCD_PrintStr("Weight = ");
											LCD_data(key);
											Systick_ms(2000);
											time = (key - '0')*30; // rate = 60*0.5 in seceonds
											state = Cooking;							
										}
										else{
											previous_state = state;
											state = Error;
										}
										break;
						Chicken:
										LCD_PrintStr("Chicken Weight?");
										key = pressed();
										if (Valid_Check(key) == 1){
											LCD_cmd(cursor_at_2ndline);
											LCD_PrintStr("Weight = ");
											LCD_data(key);
											Systick_ms(2000);
											time = (key - '0')*12; // rate = 60*0.2 in seceonds
											state = Cooking;									
										}
										else{
											previous_state= state;
											state = Error;
										}
										break;
						Custom:
										LCD_PrintStr("Cooking Time?");
										Systick_ms(2000);
										state = Time_Display;
										break;
						Time_Display:
										LCD_time();
										time = Time_Entry();
										if (Timer_Check(time) == 1){
											state = Cooking;
										}
										else{
											previous_state= state;
											state = Error;
										}
										break;
						Error:
										LCD_PrintStr("Err");
										Systick_ms(2000);
										LCD_cmd(clear);
										LCD_PrintStr(" Please enter a");
										LCD_cmd(cursor_at_2ndline);
										LCD_PrintStr("  valid number");
										Systick_ms(2000);
										state = previous_state;
										break;
						Cooking:
										LCD_init2();
										pin_init(0x100000,0x0E,0x0E,0x0E); // LEDs' Pins intiallized and leds are on
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
							End:
											pin_init(0x000001,0x000001,0x000001,0x000000); //Buzzer placed on Port A ,first pin , output , off Status
											end_of_Operation(); // Toggling Leds and Buzzer for 3 seconds
											state = Idle;
											break;

		}
}
}
