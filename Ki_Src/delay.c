#include "delay.h"

void delay_Config(uint8_t SYSCLK)
{
	SysTick->CTRL	&=	1; // Clear
	f_us = SYSCLK/8; 
	f_ms = f_us*1000;// 1ms = 1000us
}
void delay_ms(uint16_t ms)
{
	uint32_t temp;
	SysTick->LOAD=(uint32_t)ms*f_ms;
	SysTick->VAL =0x00;//Reset current value 
	SysTick->CTRL	|= 0x01 ;//Enable and set Flag to 0
	do
		{
			temp=SysTick->CTRL;
		}
	while(	temp&0x01	&& !(temp&(1<<16)));//Wait flag to reverse
	SysTick->CTRL=0x00;
	SysTick->VAL =0X00;
}
void delay_us(uint32_t us)
{
	uint32_t temp;
	SysTick->LOAD=(uint32_t)us*f_us;
	SysTick->VAL =0x00;//Reset current value 
	SysTick->CTRL	|= 0x01 ;//Enable and set Flag to 0
	do
		{
			temp=SysTick->CTRL;
		}
	while(	temp&0x01	&& !(temp&(1<<16)));//Wait flag to reverse
	SysTick->CTRL=0x00;
	SysTick->VAL =0X00;
}