#include "MPU9250.h"


MPU9250_Error_code MPU9250_Gyroscope_Configuration(I2C_TypeDef *I2Cx,
												   struct MPU9250 *mpu,
												   MPU9250_Gyro_range Range) {

	uint8_t Byte_temp = 0x00;


	/* Case 1: Set gyroscope sensitivity range */
	Byte_temp = Range << 3;

	if( I2C_Mem_Write(I2Cx, &Byte_temp, mpu->Device_addres, 1, MPU9250_GYRO_CONFIG) == 0 ) {

		return MPU9250_Gyroscope_Config_FAIL;
	}

	/* Case 2: Set gyroscope low pass filter cut-off frequency */
	Byte_temp = 0x0E;

	if( I2C_Mem_Write(I2Cx, &Byte_temp, mpu->Device_addres, 1, MPU9250_GYRO_CONFIG) == 0 ) {

		return MPU9250_Gyroscope_Config_FAIL;
	}

	/* Case 3: Save configuration to data structure */
	if(      Range == MPU9250_Gyro_250s )   mpu->Gyroscope_sensitivity_factor = MPU9250_GYRO_SENSITIVITY_FACTOR_250s;
	else if( Range == MPU9250_Gyro_500s )	mpu->Gyroscope_sensitivity_factor = MPU9250_GYRO_SENSITIVITY_FACTOR_500s;
	else if( Range == MPU9250_Gyro_1000s )	mpu->Gyroscope_sensitivity_factor = MPU9250_GYRO_SENSITIVITY_FACTOR_1000s;
	else if( Range == MPU9250_Gyro_2000s )	mpu->Gyroscope_sensitivity_factor = MPU9250_GYRO_SENSITIVITY_FACTOR_2000s;

	mpu->Gyroscope_X_offset = 0;
	mpu->Gyroscope_Y_offset = 0;
	mpu->Gyroscope_Z_offset = 0;

	return MPU9250_Gyroscope_Config_OK;

}					
MPU9250_Error_code MPU9250_Read_Gyroscope(I2C_TypeDef *I2Cx,
										  struct MPU9250 *mpu)
{
	uint8_t Bytes_temp[6] = { 0x00 };

	if (I2C_Mem_Read(I2Cx, Bytes_temp, mpu->Device_addres, 6, MPU9250_GYRO_XOUT_H) == 0) {
		
		return MPU9250_Read_Gyroscope_FAIL;
	}
	printf("MPU9250_GYRO_XOUT_L 0x%08x\n",mpu->Gyroscope_X_dgs);
	//printf("0x%08x\n",Bytes_temp);
	mpu->Gyroscope_X = ( Bytes_temp[0] << 8 | Bytes_temp[1] ) - mpu->Gyroscope_X_offset;
	mpu->Gyroscope_Y = ( Bytes_temp[2] << 8 | Bytes_temp[3] ) - mpu->Gyroscope_Y_offset;
	mpu->Gyroscope_Z = ( Bytes_temp[4] << 8 | Bytes_temp[5] ) - mpu->Gyroscope_Z_offset;

	/* Case x: Calculate dgs/s values for XYZ axis */
	mpu->Gyroscope_X_dgs =  (float)(mpu->Gyroscope_X) / mpu->Gyroscope_sensitivity_factor;
	mpu->Gyroscope_Y_dgs =  (float)(mpu->Gyroscope_Y) / mpu->Gyroscope_sensitivity_factor;
	mpu->Gyroscope_Z_dgs =  (float)(mpu->Gyroscope_Z) / mpu->Gyroscope_sensitivity_factor;

	return MPU9250_Read_Gyroscope_OK;										
											
}
								
MPU9250_Error_code MPU9250_Init(I2C_TypeDef *I2Cx,
								struct MPU9250 *mpu,
								MPU9250_Device_number Number,
								MPU9250_Acce_range Acce_range,
								MPU9250_Gyro_range Gyro_range)
{
	uint8_t Byte_temp = 0x00;

	mpu->Device_number = Number;
	mpu->Device_addres = (0x68 | mpu->Device_number) << 1;

	/* Case 1: Is device connected ? */
	if(I2C_device_exist(I2C1, mpu->Device_addres)==0) 
	{
		printf("Device is not existed\n");
		return MPU9250_Init_FAIL;
	}	
	/* Case 2: Who am i test */
	if(I2C_Mem_Read(I2C1,&Byte_temp, mpu->Device_addres,1, MPU9250_WHO_AM_I) == 0)
	{
		printf("WHO_AM_I is not existed\n");
		return MPU9250_Init_FAIL;
	}
	if( Byte_temp != 0x70   ) 
	{
		
		return MPU9250_Init_FAIL;
	}
		/* Case 3: Wake up */
	Byte_temp = 0x01;

	if( I2C_Mem_Write(I2C1, &Byte_temp, mpu->Device_addres, 1, MPU9250_PWR_MGMT_1) == 0 ) {
		printf("Wake up is failed\n");
		return MPU9250_Init_FAIL;
	}
	/* Case 4: Accelerometer configuration */
	if( MPU9250_Accelerometer_Configuration(I2Cx, mpu, Acce_range) != MPU9250_Accelerometer_Config_OK ) {
		printf("Accelerometer Configure failed\n");
		return MPU9250_Accelerometer_Config_FAIL;
	}
		/* Case 5: Gyroscope configuration */
	if( MPU9250_Gyroscope_Configuration(I2Cx, mpu, Gyro_range) != MPU9250_Gyroscope_Config_OK ) {
		printf("Gyroscope Configure failed\n");
		return MPU9250_Gyroscope_Config_FAIL;
	}
		return 0;
}

MPU9250_Error_code MPU9250_Read_Accelerometer(I2C_TypeDef *I2Cx,
											  struct MPU9250 *mpu) {

	uint8_t Bytes_temp[6] = {0x00};

	if(I2C_Mem_Read(I2Cx, Bytes_temp , mpu->Device_addres, 6, MPU9250_ACCEL_XOUT_H) == 0 ) {

		return MPU9250_Read_Accelerometer_FAIL;
	}

	mpu->Accelerometer_X = ( Bytes_temp[0] << 8 | Bytes_temp[1] ) - mpu->Accelerometer_X_offset;
	mpu->Accelerometer_Y = ( Bytes_temp[2] << 8 | Bytes_temp[3] ) - mpu->Accelerometer_Y_offset;
	mpu->Accelerometer_Z = ( Bytes_temp[4] << 8 | Bytes_temp[5] ) - mpu->Accelerometer_Z_offset;

	/* Case x: Calculate g-force values for XYZ axis */
	mpu->Accelerometer_vector_gx = (float)(mpu->Accelerometer_X) / mpu->Accelerometer_sensitivity_factor;
	mpu->Accelerometer_vector_gy = (float)(mpu->Accelerometer_Y) / mpu->Accelerometer_sensitivity_factor;
	mpu->Accelerometer_vector_gz = (float)(mpu->Accelerometer_Z) / mpu->Accelerometer_sensitivity_factor;

	return MPU9250_Read_Accelerometer_OK;
}

MPU9250_Error_code MPU9250_Accelerometer_Configuration(I2C_TypeDef *I2Cx,
													   struct MPU9250 *mpu,
													   MPU9250_Acce_range Range) {

	uint8_t Byte_temp = 0x00;

	/* Case 1: Set accelerometer sensitivity range */
	Byte_temp = Range << 3;

	if(I2C_Mem_Write(I2Cx, &Byte_temp, mpu->Device_addres, 1, MPU9250_ACCEL_CONFIG) == 0 ) {

		return MPU9250_Accelerometer_Config_FAIL;
	}

	/* Case 2: Set accelerometer low pass filter cut-off frequency */
	/*
	Byte_temp = 0x0E;
	if( HAL_I2C_Mem_Write(I2Cx, mpu->Device_addres, MPU9250_ACCEL_CONFIG_2, 1, &Byte_temp, 1, 1000) != HAL_OK ) {
		return MPU9250_Accelerometer_Config_FAIL;
	}
	*/

	/* Case 3: Save configuration to data structure */
	if(      Range == MPU9250_Acce_2G )     mpu->Accelerometer_sensitivity_factor = MPU9250_ACCE_SENSITIVITY_FACTOR_2G;
	else if( Range == MPU9250_Acce_4G )		mpu->Accelerometer_sensitivity_factor = MPU9250_ACCE_SENSITIVITY_FACTOR_4G;
	else if( Range == MPU9250_Acce_8G )		mpu->Accelerometer_sensitivity_factor = MPU9250_ACCE_SENSITIVITY_FACTOR_8G;
	else if( Range == MPU9250_Acce_16G )	mpu->Accelerometer_sensitivity_factor = MPU9250_ACCE_SENSITIVITY_FACTOR_16G;

	mpu->Accelerometer_X_offset = 0;
	mpu->Accelerometer_Y_offset = 0;
	mpu->Accelerometer_Z_offset = 0;

	return MPU9250_Accelerometer_Config_OK;
}
void MPU9250_Calibration_Acce(I2C_TypeDef *I2Cx,
	      	  	  	  	  	  	  	        struct MPU9250 *mpu) {

	float Acce_X_offset = 0, Acce_Y_offset = 0, Acce_Z_offset = 0;

	for (int i = 0; i < 1000; ++i) {

		MPU9250_Read_Accelerometer(I2Cx, mpu);

		Acce_X_offset = Acce_X_offset + mpu->Accelerometer_X;
		Acce_Y_offset = Acce_Y_offset + mpu->Accelerometer_Y;
		Acce_Z_offset = Acce_Z_offset + mpu->Accelerometer_Z;
	}

	mpu->Accelerometer_X_offset = Acce_X_offset / 1000;
	mpu->Accelerometer_Y_offset = Acce_Y_offset / 1000;
	mpu->Accelerometer_Z_offset = Acce_Z_offset / 1000;


	mpu->Accelerometer_Z_offset = mpu->Accelerometer_Z_offset - mpu->Accelerometer_sensitivity_factor;
}