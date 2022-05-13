#ifndef Counting_Down_H
#define Counting_Down_H
#include "LCD.h"
#include "delay.h"

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
