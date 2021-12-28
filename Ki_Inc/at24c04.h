#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"

void I2C1_init(void);
void i2c_Write(uint32_t address, uint8_t address_Word, uint8_t data);
void i2c_Read(uint32_t address, uint8_t address_Word);
void i2c_Reset();
