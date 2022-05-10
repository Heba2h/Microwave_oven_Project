#include "Io.h"

void SysTick_Init(void)
{
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 5;
}
void Systick_Wait(int delay)
{
	NVIC_ST_RELOAD_R = delay-1;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R & 0x00010000)==0);
}
void Systick_ms(int delay)// wait delay*1ms
{
	for(unsigned long i=0;i<delay;i++)
	Systick_Wait(80000);
}
void Systick_us(int delay)// wait delay*1us
{
	for(unsigned long i=0;i<delay;i++)
	Systick_Wait(80);
}

