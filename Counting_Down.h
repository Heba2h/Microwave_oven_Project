#ifndef Counting_Down_H
#define Counting_Down_H
#include "LCD.h"
#include "delay.h"
#include "switches.h"
#include "interrupts_handlers.h"


extern int state;
extern int flag2;
extern int flag3;


/**
*  @author      Aser-ElDahshan
*  @detailed    This fuction represents the pause state. Each iteration in counting down goes to this function checking if switch 1 is pressed or the door is open.
*		If switch 1 is pressed the leds start blinking and counting down pauses waiting for switch 2 to be pressed to resume or switch 1 to be pressed to return 
*		to the idle state and exits counting down. If the door is open, leds start blinking waiting this time the door to close then checks if switch2 is pressed
*		while the door is still closed to resume counting down.	
*/

void pause_stop(){
	            if (GPIO_PORTF_MIS_R & 0x10) // check if interrupt causes by PF4/SW1 /
                    {
                        flag2 = 1;
                        GPIO_PORTF_ICR_R |= 0x10;
                    while(sw1_pressed()){}
                      if ( flag2 == 1){
                        while(!sw2_pressed() && !sw1_pressed()){
                            Led_Blinking();
													  Systick_ms(500);												
                        }
                        if(sw1_pressed()){
                            SystemReset();
                           // break;
                        }
                        Leds_on();
                        flag2 = 0;
                       }
                   }

            if (sw3_pressed()) // check if interrupt causes by PF4/SW1 
                    {
                        flag3 = 1;
                      //  GPIO_PORTA_ICR_R |= 0x80;
                    }
            if ( flag3 == 1){
                   // while(sw3_pressed()){}
                    while(!sw2_pressed() || sw3_pressed() ){
			    Led_Blinking();
			    Systick_ms(500);
		    }
                    flag3 = 0;
                }



}

/**
*  @author      Aser-ElDahshan
*  @detailed    This fuction takes the time in seconds from the different cases and divides it into 4 digits, 2 for min and 2 for sec
*		and enters two nested for loops one for min and one for sec and starts counting down waiting each iteration one second.
*		When the internal loop finishes counting down minutes decrement by one.	
*/

void Counting_Down(int time)
{  
    int min,sec,min1,min2,sec1,sec2,i,j;
    min = (int)(time/60);
    sec = time%60;
	
	if (check == 1){
    for(i=min;i>=0;i--)
    {
        min2 = (int)(i/10);
      min1 = i%10;
        LCD_cmd(0xC5);
        LCD_data(min2+48);
        LCD_cmd(0xC6);
        LCD_data(min1+48);
        LCD_cmd(0xC7);
        LCD_data(':');

        for(j=sec;j>=0;j--)
        {
				pause_stop();
        sec2 = (int)(j/10);
        sec1 = j%10;
            LCD_cmd(0xC8);
        LCD_data(sec2+48);
            LCD_cmd(0xC9);
        LCD_data(sec1+48);
            Systick_ms(1000);
        }
        sec=59;
    }
		
}
	}
#endif
