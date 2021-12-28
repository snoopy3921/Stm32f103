#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"
#include "delay.h"




int main()
{
	I2C1_init();
	i2c_Write(0x50, 0x12, 0x13);
	for(int i=10000; i>0;i--);
	i2c_Read(0x50, 0x12);
	while(1)
	{
	
	}
}
