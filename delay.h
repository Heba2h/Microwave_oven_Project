#ifndef delay_H
#define delay_H
#include "tm4c123gh6pm.h"


/**
*  @author      Aser-ElDahshan
*  @detailed    This fuction initializes Systick.
*/

void SysTick_Init(void)
{
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 5;
}

/**
*  @author      Aser-ElDahshan
*  @detailed    This fuction gives the reload register a value to count down from it waiting untill the flag is set to indicate that the current register is now zero.
*  @param	This function takes an integer value to write it in the reload regsister after decrementing it by one.
*/


void Systick_Wait(int delay)
{
	NVIC_ST_RELOAD_R = delay-1;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R & 0x00010000)==0);
}

/**
*  @author      Aser-ElDahshan
*  @detailed    This fuction waites a multiple of a milli second.
*  @param	The function takes an integer value representing time in milli seconds.
*/


void Systick_ms(int delay)// wait delay*1ms
{
	unsigned long i;
	for( i=0;i<delay;i++)
	Systick_Wait(16000);
}

#endif
