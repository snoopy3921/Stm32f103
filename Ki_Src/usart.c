#include "usart.h"


void usart_Gpio_Config()
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // TX - USART1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // RX - USART1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void USARTx_Configuration(USART_TypeDef* USARTx)
{
	USART_InitTypeDef USART_InitStructure;
	if(USARTx==USART1)      RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	else if(USARTx==USART2)	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	else if(USARTx==USART3)	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
	USART_DeInit(USARTx);
	USART_InitStructure.USART_BaudRate = 9600; // Config BaudRate
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; // Bitlen
	USART_InitStructure.USART_StopBits = USART_StopBits_1; // Number of bit stop
	USART_InitStructure.USART_Parity = USART_Parity_No; // Cau hinh su dung che do Parity
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // Cauhinh che do dieu khien theo luong
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // Cau hinh che do truyennhan
	USART_Init(USARTx, &USART_InitStructure); // Cau hinh USART1
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USARTx,USART_IT_TXE, ENABLE); 
	USART_Cmd(USARTx, ENABLE); // Kich hoat USART1
}