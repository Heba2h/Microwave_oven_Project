#include "tm4c123gh6pm.h"
void keypad_init()
{
	SYSCTL_RCGCGPIO_R|=0x1;   // clock port a
	while((SYSCTL_PRGPIO_R & 0x1)==0); // clock status
	GPIO_PORTA_AFSEL_R =0;  //afsel zeroos 
	GPIO_PORTA_PCTL_R =0;    // pctl =o
	GPIO_PORTA_DIR_R =0xf0;  // pin0-3 are inputs and pins 4-7 are outputs
	GPIO_PORTA_PDR_R =0X0F;  //ACTIVE HIGH
	GPIO_PORTA_DEN_R =0XFF;  // DIGITAL ENABLED
}
short i;// number of rows 
short j;// number of coloms
short x;//temporary to refer to rows
short y;// temporary to refer to coloms
char elements[4][4]={{'1','2','3','A'},
                     {'4','5','6','B'},  // keypads elements
										 {'7','8','9','C'},
                     {'*','0','#','D'}
                                      };
char pressed()
	{ 
		x=GPIO_PORTA_DATA_R&0x0f;  
		y=GPIO_PORTA_DATA_R&0xf0;  
		if((x=1)||(x=2))
       {i=x-1;}
     else if((x=4))
		 {i=2;}
		 else if((x=8))
		 {i=3;}
		 y=y>>4;
		if((y=1)||(y=2))
       {j=y-1;}
     else if((y=4))
		 {j=2;}
		 else if((y=8))
		 {j=3;}
		 return(elements[i][j]);
	 }