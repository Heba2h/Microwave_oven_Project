#include "tm4c123gh6pm.h"
#define	clear 							0x01
#define	cursor_on 					0x0F
#define cursor_off					0x08
#define	increment_cursor 		0x06
#define	display_on 					0x0E
#define	cursor_at_1stline 	0x80
#define	cursor_at_2ndline 	0xC0
#define mode_8pins 					0x38


void LCD_init1(void)
	{
	SYSCTL_RCGCGPIO_R |= 0x03; //Enable the clock for PA,PB
	while ( (SYSCTL_RCGCGPIO_R & 0x03) == 0);
	//Port B
	GPIO_PORTB_DIR_R = 0xFF;
	GPIO_PORTB_DEN_R = 0xFF;
	GPIO_PORTB_AFSEL_R = 0x00;
	GPIO_PORTB_AMSEL_R = 0x00;
	GPIO_PORTB_PCTL_R = 0x00000000;
	
	//Port A
	GPIO_PORTA_DIR_R |= 0x0C; //0000 1100
	GPIO_PORTA_DEN_R |= 0x0C;	
	GPIO_PORTA_AFSEL_R &=~0x0C;
	GPIO_PORTA_AMSEL_R &=~ 0x0C;
	GPIO_PORTA_PCTL_R &= ~ 0x0000FF00;
                  }

void LCD_cmd(unsigned char cmd) 
{
	GPIO_PORTA_DATA_R &=~0x04;	//RS = 0 0000 0100
	GPIO_PORTB_DATA_R =cmd ;			//sending command
	GPIO_PORTA_DATA_R |= 0x08;	//enable on 0000 1000
	Systick_ms(10);
	GPIO_PORTA_DATA_R &=~0x08;	//enable off
}

void LCD_init2(void)
{
                  LCD_cmd(mode_8pins);
                   Systick_ms(10);
	LCD_cmd(display_on);
                   Systick_ms(10);
	LCD_cmd(increment_cursor);  
                   Systick_ms(10);
	LCD_cmd(cursor_at_1stline);
                   Systick_ms(10);
	LCD_cmd(cursor_at_2ndline);
	Systick_ms(10);
	LCD_cmd(clear);
}



void LCD_data(unsigned char data)
{
	GPIO_PORTA_DATA_R |=0x04; // 0000 0100
	GPIO_PORTB_DATA_R = data;
	GPIO_PORTA_DATA_R |= 0x08;
	Systick_ms(10);
	GPIO_PORTA_DATA_R &=~0x08;	//enable off
	
}


void LCD_PrintStr(unsigned char* msg)
{
	int i;
	for(i=0 ; msg[i] != '\0'; i++)
	{LCD_data(msg[i]);
	}

}

