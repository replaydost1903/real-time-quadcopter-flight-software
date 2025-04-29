#include "bmi160_port.h"
#include "bmi160_defs.h"

extern I2C_HandleTypeDef hi2c1;

__inline static void IsDeviceReady(uint8_t dev_addr);

static void IsDeviceReady(uint8_t dev_addr)
{
	  if(HAL_OK == HAL_I2C_IsDeviceReady(&hi2c1, (dev_addr << 1U), 100, HAL_MAX_DELAY))
	  {
		  HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, 1U);
	  }
	  else
	  {
		  Error_Handler();
	  }
}

int8_t bmi160_i2c_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *read_data, uint16_t len)
{
	dev_addr = ((dev_addr << 1U) | 0x0U);
	HAL_I2C_Mem_Write(&hi2c1, dev_addr, reg_addr, 1U, read_data, len, HAL_MAX_DELAY);
	return ( BMI160_OK );
}
int8_t bmi160_i2c_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
	dev_addr = ((dev_addr << 1U) | 0x1U);
	HAL_I2C_Mem_Read(&hi2c1, dev_addr, reg_addr, 1U, data, len, HAL_MAX_DELAY);
	return ( BMI160_OK );
}
void delay_ms(uint32_t period)
{
	HAL_Delay(period);		//Systick yerine TIM6 olacak
}

int8_t bmi160_interface_init(struct bmi160_dev *bmi160)
{
	/*<! Check null-pointer  <!*/
	if( bmi160 == NULL )
	{
	  Error_Handler();
	}

#if ( ( BMI160_I2C_INTERFACE) && ( !BMI160_SPI_INTERFACE ) )

	int8_t rslt;

	bmi160_soft_reset(bmi160);

	bmi160->id = BMI160_DEV_ADDR;
	bmi160->intf = BMI160_I2C_INTF;
	bmi160->read = bmi160_i2c_read;
	bmi160->write = bmi160_i2c_write;
	bmi160->delay_ms = delay_ms;

	/* After sensor init introduce 200 msec sleep */
	bmi160->delay_ms(200);

	rslt = bmi160_init(bmi160);

	if ( rslt != BMI160_OK )
	{
		printf("BMI160 initialization failure !\n");
		Error_Handler();
	}

	printf("BMI160 initialization success !\n");
	printf("Chip ID 0x%X\n" , bmi160->chip_id);

	//acceleration self-test configuration
	rslt = bmi160_perform_self_test(BMI160_ACCEL_ONLY,bmi160);

	if( rslt != BMI160_OK )
	{
		printf("BMI160 acceleration self-test failure !\n");
		Error_Handler();
	}

	printf("BMI160 acceleration self-test success !\n");

	//gyroscope self-test configuration
	rslt = bmi160_perform_self_test(BMI160_GYRO_ONLY,bmi160);

	if( rslt != BMI160_OK )
	{
		printf("BMI160 gyroscope self-test failure !\n");
		Error_Handler();
	}

	printf("BMI160 gyroscope self-test success !\n");

	/* Select the Output data rate, range of accelerometer sensor */
	bmi160->accel_cfg.odr = BMI160_ACCEL_ODR_1600HZ;
	bmi160->accel_cfg.range = BMI160_ACCEL_RANGE_2G;
	bmi160->accel_cfg.bw = BMI160_ACCEL_BW_NORMAL_AVG4;

	/* Select the power mode of accelerometer sensor */
	bmi160->accel_cfg.power = BMI160_ACCEL_NORMAL_MODE;

	/* Select the Output data rate, range of Gyroscope sensor */
	bmi160->gyro_cfg.odr = BMI160_GYRO_ODR_3200HZ;
	bmi160->gyro_cfg.range = BMI160_GYRO_RANGE_2000_DPS;
	bmi160->gyro_cfg.bw = BMI160_GYRO_BW_NORMAL_MODE;

	/* Select the power mode of Gyroscope sensor */
	bmi160->gyro_cfg.power = BMI160_GYRO_NORMAL_MODE;

	/* Set the sensor configuration */
	rslt = bmi160_set_power_mode(bmi160);

	if( rslt != BMI160_OK )
	{
		printf("BMI160 sensor configuration failure !\n");
		Error_Handler();
	}

	printf("BMI160 sensor configuration success !\n");

	struct bmi160_offsets bmi160_offset = {0};
	struct bmi160_foc_conf bmi160_foc = {0};

	rslt = bmi160_get_offsets(&bmi160_offset,bmi160);

	if( rslt != BMI160_OK )
	{
		printf("BMI160 sensor offset value failure !\n");
		Error_Handler();
	}

	printf("BMI160 sensor offset value success !\n");

	bmi160_foc.acc_off_en = BMI160_ENABLE;
	bmi160_foc.gyro_off_en = BMI160_ENABLE;
	bmi160_foc.foc_gyr_en = BMI160_ENABLE;
	bmi160_foc.foc_acc_x = BMI160_FOC_ACCEL_POSITIVE_G;
	bmi160_foc.foc_acc_y = BMI160_FOC_ACCEL_POSITIVE_G;
	bmi160_foc.foc_acc_z = BMI160_FOC_ACCEL_POSITIVE_G;

	bmi160_set_offsets(&bmi160_foc, &bmi160_offset, bmi160);

	if( rslt != BMI160_OK )
	{
		printf("BMI160 sensor offset value failure !\n");
		Error_Handler();
	}

	printf("BMI160 sensor offset value success !\n");

	HAL_Delay(2000);

	return ( BMI160_OK );

	#elif ( ( BMI160_SPI_INTERFACE) && ( !BMI160_I2C_INTERFACE ) )


	#else
		Error_Handler();
	#endif
	return ( BMI160_E_INVALID_CONFIG );
}

int8_t bmi160_calibration(struct bmi160_dev *bmi160,uint32_t IterTimeMS)
{
	/*<! Check null-pointer  <!*/
	if( bmi160 == NULL )
	{
	   Error_Handler();
	}

	if ( IterTimeMS <= 0)
	{
	   Error_Handler();
	}

	uint32_t sample_num = 0U , current_tick = HAL_GetTick();
	double acc_x_offset = 0.0f , acc_y_offset = 0.0f , acc_z_offset = 0.0f;
	double gyr_x_offset = 0.0f , gyr_y_offset = 0.0f , gyr_z_offset = 0.0f;

	while( ( HAL_GetTick() - current_tick ) < IterTimeMS )
	{

	  if( bmi160_get_sensor_data((BMI160_ACCEL_SEL | BMI160_GYRO_SEL),&bmi160->accel_data,&bmi160->gyro_data,(struct bmi160_dev*)bmi160) != BMI160_OK)
	  {
		  printf("BMI160 sensor data failed !\n");
		  Error_Handler();
	  }

	  acc_x_offset += (double)bmi160->accel_data.x;
	  acc_y_offset += (double)bmi160->accel_data.y;
	  acc_z_offset += (double)bmi160->accel_data.z;

	  gyr_x_offset += (double)bmi160->gyro_data.x;
	  gyr_y_offset += (double)bmi160->gyro_data.y;
	  gyr_z_offset += (double)bmi160->gyro_data.z;

	  ++sample_num;
	}

	acc_x_offset /= (double)sample_num;
	acc_y_offset /= (double)sample_num;
	acc_z_offset = (acc_z_offset / (double)sample_num) - 1 ;

	gyr_x_offset /= (double)sample_num;
	gyr_y_offset /= (double)sample_num;
	gyr_z_offset /= (double)sample_num;

	return ( BMI160_OK );
}




































