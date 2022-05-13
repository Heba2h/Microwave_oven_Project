#ifndef LCD_Time_H
#define LCD_Time_H
#include "LCD.h"
#include "Keypad.h"
#include "tm4c123gh6pm.h"
//#include initialization for port F +++++ sw2_function
int x;
void LCD_time()
{
	LCD_cmd(0xC5);
	LCD_PrintStr("00:00");

}


int Time_Entry()
{
	int i;
	int time;
	int button;
	char num[]={'0','0','0','0'} ;
	int loc[]={0xC9,0xC8,0xC6,0xC5};
	button = sw2_Input();
	x=1;
	while(x!=0)// condition->sw2 is not pressed
	{
	//button = sw2_Input();
	//	if (pressed())
		//{	
			for( i=3;i>0;i--)
			{
				num[i]=num[i-1];
			}
				
			num[0] = pressed();
			if(x==0)
				continue;
			for( i=0;i<4;i++)
			{
			LCD_cmd(loc[i]);
	    LCD_data(num[i]);
		}
			
			time = (num[3]-'0')*10*60+(num[2]-'0')*60+(num[1]-'0')*10+(num[0]-'0');
	
	}

	return time;
}
#endif
