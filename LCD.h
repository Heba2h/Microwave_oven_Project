#include "tm4c123gh6pm.h"
#define	clear                            0x01 
#define	cursor_on 	 0x0F           //display_on, cursor_blinking 
#define     cursor_off	 0x0C          //display_on, cursor_off
#define	increment_cursor 	 0x06         // Entry_mode 
#define	display_on 	 0x0E        //display_on, cursor_on 
#define	cursor_at_1stline 	 0x80
#define	cursor_at_2ndline     0xC0
#define mode_8pins 	 0x38



/**
*  @author :       Heba2h
*  @detailed :    This fuction return the initialization of the LCD i took the 8 bins of Port B and RS,E 2 pins of Port A 
*  @Hardware :  for data [D0-D7]  --> [B0-B7]  , RS -> A2  and E -> A3
*                          Rw & K are grouned -> (GND)    and A ->(VDD )
*                          But to change the contrast we connected V0 -> POT 
*                          Change display brightness we connected A -> POT
*
*  @param :      All function registers are defined in "tm4c123gh6pm.h" file
*/
 
void LCD_init1(void)
	{
	SYSCTL_RCGCGPIO_R |= 0x03;  //  Enable the clock for PA , PB
	while ( (SYSCTL_RCGCGPIO_R & 0x03) == 0); 

	//Port B
	GPIO_PORTB_DIR_R = 0xFF;    //PB 76543210 output 
	GPIO_PORTB_DEN_R = 0xFF;   // Enable digital pins PB7-PB0
	GPIO_PORTB_AFSEL_R = 0x00;   // No alternate function
	GPIO_PORTB_AMSEL_R = 0x00;  // Disable analog function
	GPIO_PORTB_PCTL_R = 0x00000000; // GPIO clear bit PCTL
	
	//Port A
	GPIO_PORTA_DIR_R |= 0x0C;    //PA 32 output                  
	GPIO_PORTA_DEN_R |= 0x0C;  // Enable digital pins PA3-PA2	
	GPIO_PORTA_AFSEL_R &=~0x0C; // No alternate function
	GPIO_PORTA_AMSEL_R &=~ 0x0C;   // Disable analog function
	GPIO_PORTA_PCTL_R &= ~ 0x0000FF00;  // GPIO clear bit PCTL
                  }

/**
*  @detailed : This function take the command which we already defined it in the top of file 
* @ returns  : its void func with no returns , it displays the action of command   
*/

void LCD_cmd(unsigned char cmd) 
{
	GPIO_PORTA_DATA_R &=~0x04;	//RS = 0 , 0000 0100
	GPIO_PORTB_DATA_R =cmd ;		//sending command
	GPIO_PORTA_DATA_R |= 0x08; 	//enable on 0000 1000
	Systick_ms(10);                                            
	GPIO_PORTA_DATA_R &=~0x08;	//enable off
                  LCD_cmd(cursor_off);
}

/**
*  @detailed : This function take the command and make the LCD ready to be used 
* @ returns  : its void func with no returns , it displays the action of commands   
*/

void LCD_init2(void)
{
                  LCD_cmd(mode_8pins);
	LCD_cmd(display_on);
	LCD_cmd(increment_cursor);  
	LCD_cmd(cursor_at_1stline);
	LCD_cmd(clear);
}


/**
*  @detailed : This function take data with char type and prints it in the LCD ,
*                      where we equates the DATA to be sent to LCD with input data.
* @ returns  : its void func with no returns , it displays the action   
*/

void LCD_data(unsigned char data)
{
	GPIO_PORTA_DATA_R |=0x04;                   // 0000 0100 ,  RS=1 
	GPIO_PORTB_DATA_R = data;                    // send data
	GPIO_PORTA_DATA_R |= 0x08;                  //enable ON
	Systick_ms(10);
	GPIO_PORTA_DATA_R &=~0x08;	//enable off
                  LCD_cmd(cursor_off);
	
}

/**
*  @detailed : This function take msg with char* type and prints it in the LCD ,
*                      where it loops at the string and print it .
* @ returns  : its void func with no returns , it displays the action   
*/

void LCD_PrintStr(unsigned char* msg)
{
	int i;
	for(i=0 ; msg[i] != '\0'; i++)
	{
              LCD_data(msg[i]);
	}

}

