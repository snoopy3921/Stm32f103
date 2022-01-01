#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"
#include "debug.h"
#include "usart.h"
#include "MPU9250.h"



int main()
{	
	struct MPU9250 *mpu;
	//I2C_ClearFlag(I2C1,I2C_FLAG_BUSY);
	
	Delay_Init(72);
	I2Cx_Init(I2C1, 100000, 0x38);
	//i2c_Write(0x50, 0x12, 0x13);
	//i2c_Write(0x50, 0x12, 0x13);
	//delay_ms(1000);
	//i2c_Read(0x50, 0x12);
	
	
 	USART_Printf_Init(9600);
	//printf("Hello");
	Delay_Ms(200);
	//i2c_Read(0x50, 0x12);
	int8_t i= MPU9250_Init(I2C1, mpu, MPU9250_Device_1,MPU9250_Acce_16G, MPU9250_Gyro_2000s);
	printf("MPU Init%d\n",i);
	

	MPU9250_Calibration_Acce(I2C1,mpu);
	while(1)
	{
	/*	
	MPU9250_Read_Gyroscope(I2C1,mpu);
	printf("GYRO<-------------------------------------------->\n");
	printf("%f\n",mpu->Gyroscope_X_dgs);
	printf("%f\n",mpu->Gyroscope_Y_dgs);
	printf("%f\n",mpu->Gyroscope_Z_dgs);
	*/	
	
	MPU9250_Read_Accelerometer(I2C1,mpu);
	printf("ACCEL<-------------------------------------------->\n");
	printf("%f-----%f-----%f\n",mpu->Accelerometer_vector_gx,mpu->Accelerometer_vector_gy,mpu->Accelerometer_vector_gz);
	//printf("%f\n",mpu->Accelerometer_vector_gy);
	//printf("%f\n",mpu->Accelerometer_vector_gz);	

	//I2C_Read(I2C1, 0x10, 1, 0x50);
	
	//getGyroCounts(&gx,&gy,&gz);
	//printf("X value = %f, Y value = %f, Z value = %f\n", gx ,gy, gz );
  Delay_Ms(1000);
	}
}
