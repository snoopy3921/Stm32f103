#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"

static uint16_t f_us, f_ms;//Frequency
void delay_Config(uint8_t SYSCLK);
void delay_ms(uint16_t ms);
void delay_us(uint32_t us);