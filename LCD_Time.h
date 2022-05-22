#ifndef LCD_Time_H
#define LCD_Time_H

#include "delay.h"
#include "LCD.h"
#include "Keypad.h"
#include "tm4c123gh6pm.h"
#include "functions.h"
#include "stdbool.h"


extern int flag;
extern int state;
extern int previous_state;
bool extern check;
char num[4]={'0','0','0','0'};


void LCD_time()
{
	LCD_cmd(cursor_at_1stline);	
	LCD_PrintStr("Please Press SW2");
      num[0] ='0';
			num[1] ='0';
			num[2] ='0';
			num[3] ='0';		
	LCD_cmd(0xC5);
	LCD_PrintStr("00:00");

}



int Time_Entry()
{
	int i;
	extern int time;
	int loc[]={0xC9,0xC8,0xC6,0xC5};
	char checker;
	 
	
	while(flag != 1)// condition->sw2 is not pressed
	{
		checker =pressed();
		if (('0'<= checker) && (checker<='9'))
			{	
			Systick_ms(100);
			for( i=3;i>0;i--)
			{			
				num[i]=num[i-1];			
			}		
			num[0] = checker ;
			
			for( i=0;i<4;i++)
			{
				LCD_cmd(loc[i]);
				LCD_data(num[i]);
				
			}		
			time = (num[3]-'0')*10*60+(num[2]-'0')*60+(num[1]-'0')*10+(num[0]-'0');
						
	}
	}
	
	return time;
}
#endif
