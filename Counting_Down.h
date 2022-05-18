#ifndef Counting_Down_H
#define Counting_Down_H
#include "LCD.h"
#include "delay.h"
#include "switches.h"

extern int state;
extern int flag2;
extern int flag3;

void Counting_Down(int time)
{
    int min,sec,min1,min2,sec1,sec2,i,j;
    min = (int)(time/60);
    sec = time%60;
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
            if (GPIO_PORTF_MIS_R & 0x10) /* check if interrupt causes by PF4/SW1 /
                    {
                        flag2 = 1;
                        GPIO_PORTF_ICR_R |= 0x10;
                    while(sw1_pressed()){}
                if ( flag2 == 1){
                        while(!sw2_pressed() && !sw1_pressed()){
                            Led_Blinking();
                        }
                        if(sw1_pressed()){
                            //SystemReset();
                            state = 0;
                            break;
                        }
                        Leds_on();
                        flag2 = 0;
                    }
            }

            if (GPIO_PORTA_MIS_R & 0x80) / check if interrupt causes by PF4/SW1 */
                    {
                        flag3 = 1;
                        GPIO_PORTA_ICR_R |= 0x80;
                    }
            if ( flag3 == 1){
                    while(sw3_pressed()){}
                    while(!sw2_pressed()){}
                    flag3 = 0;
                }
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
#endif
