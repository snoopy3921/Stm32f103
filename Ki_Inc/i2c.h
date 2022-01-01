#ifndef I2C_H
#define I2C_H

#include <stm32f10x_i2c.h>

typedef enum {Error = 0, Success = !Error } Status;


void I2Cx_Init(I2C_TypeDef* I2Cx, uint32_t ClockSpeed, uint16_t OwnAddress);
Status I2C_device_exist(I2C_TypeDef* I2Cx, uint8_t SlaveAddress);
Status I2C_Mem_Read(I2C_TypeDef *I2Cx, uint8_t* buf, uint8_t SlaveAddress, uint32_t nbyte, uint16_t MemAddress);
Status I2C_Mem_Write(I2C_TypeDef *I2Cx, uint8_t* buf, uint8_t SlaveAddress, uint32_t nbyte, uint16_t MemAddress);
#endif
