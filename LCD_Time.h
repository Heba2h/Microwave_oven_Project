#ifndef LCD_Time_H
#define LCD_Time_H

#include "delay.h"
#include "LCD.h"
#include "Keypad.h"
#include "tm4c123gh6pm.h"
#include "functions.h"
//#include initialization for port F +++++ sw2_function
extern int x;
extern int flag;
extern int flagD;
//extern char num[4];

void LCD_time()
{
    LCD_cmd(cursor_at_1stline);
    LCD_PrintStr("Please Press SW2");
    LCD_cmd(0xC5);
    LCD_PrintStr("00:00");

}

char num[4] ={'0','0','0','0'};

int Time_Entry()
{
    int i;
    extern int time;
    int loc[]={0xC9,0xC8,0xC6,0xC5};
    int button;


    while(1)// condition->sw2 is not pressed
    {
            Systick_ms(100);
            for( i=3;i>0;i--)
            {

                num[i]=num[i-1];

            }

            num[0] = pressed();
            for( i=0;i<4;i++)
            {
                LCD_cmd(loc[i]);
                LCD_data(num[i]);

            }
            time = (num[3]-'0')1060+(num[2]-'0')60+(num[1]-'0')10+(num[0]-'0');
            if(flag == 1 || x == 1){
                    break;
            }

    }


    return time;
}
#endif
