#include "LCD.h"
#include "Keypad.h"

void LCD_time()
{
	LCD_cmd(0xC7);
	LCD_data(':');
	

}


void Time_Entry()
{
	char num[]={'0','0','0','0'} ;
	int loc[]={0xC9,0xC8,0xC6,0xC5};
	while(1)// condition->sw2 is not pressed
	{
		if (keypad_getkey())
		{	
			for(int i=3;i>0;i--)
			{
				num[i]=num[i-1];
			}
			num[0] = keypad_getkey();
			for(int i=0;i<4;i++)
			{
			LCD_cmd(loc[i]);
	    LCD_data(num[i]);
		}
	}
	}
}