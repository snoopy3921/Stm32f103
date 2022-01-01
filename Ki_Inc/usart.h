#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "delay.h"

void usart_Gpio_Config(void);
void USARTx_Configuration(USART_TypeDef* USARTx);