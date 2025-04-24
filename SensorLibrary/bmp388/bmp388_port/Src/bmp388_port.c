#include "bmp388_port.h"

extern void Error_Handler(void);
extern struct bmp388_interface bmp388_intf;

static volatile uint32_t counter = 0U;

BMP3_INTF_RET_TYPE bmp388_read(uint8_t reg_addr, uint8_t *read_data, uint32_t len, void *intf_ptr)
{
	struct bmp388_interface *intf = (struct bmp388_interface *)intf_ptr;
	HAL_I2C_Mem_Read(intf->hi2c, (intf->dev_addr << 1U), reg_addr, 1U, read_data, len, HAL_MAX_DELAY);
	return ( BMP3_INTF_RET_SUCCESS );
}

BMP3_INTF_RET_TYPE bmp388_write(uint8_t reg_addr, const uint8_t *read_data, uint32_t len,void *intf_ptr)
{
	struct bmp388_interface *intf = (struct bmp388_interface *)intf_ptr;
	HAL_I2C_Mem_Write(intf->hi2c, ((intf->dev_addr << 1U) | 0x1U), reg_addr, 1U, (uint8_t*)read_data, len, HAL_MAX_DELAY);
	return ( BMP3_INTF_RET_SUCCESS );
}

void delay_us(uint32_t period, void *intf_ptr)
{
	struct bmp388_interface *intf = (struct bmp388_interface *)intf_ptr;

	HAL_TIM_Base_Start_IT(intf->htim);

	while(counter != period);

	HAL_TIM_Base_Stop_IT(intf->htim);

	counter = 0U;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if ( htim == NULL )
	{
		Error_Handler();
	}

	if ( htim->Instance == (TIM_TypeDef*)(bmp388_intf.htim->Instance) )
	{
		++counter;
	}

}

BMP3_INTF_RET_TYPE init_bmp388_sensor_driver_interface(struct bmp3_dev *bmp388,struct bmp388_interface *bmp388_intf)
{
	if( ( bmp388 == NULL ) || ( bmp388_intf == NULL ) )
	{
		Error_Handler();
	}

	struct bmp3_settings settings = { 0 };
	int8_t rslt = 0U;
	uint16_t settings_sel = 0U;

	bmp388->intf = BMP3_I2C_INTF;
	bmp388->read = bmp388_read;
	bmp388->write = bmp388_write;
	bmp388->delay_us = delay_us;
	bmp388->intf_ptr = bmp388_intf;

	rslt = bmp3_selftest_check(bmp388);

	if ( rslt !=  BMP3_OK )
	{
		printf("BMP388 self-test failure !\n");
		Error_Handler();
	}

	printf("BMP388 self-test success !\n");

	rslt = bmp3_init(bmp388);

	if ( rslt !=  BMP3_OK )
	{
		printf("BMP388 initialization failure !\n");
		Error_Handler();
	}

	printf("BMP388 initialization success !\n");
	printf("Chip ID 0x%X\n" , bmp388->chip_id);

	settings.press_en = BMP3_ENABLE;
	settings.temp_en = BMP3_ENABLE;

	settings.odr_filter.iir_filter = BMP3_IIR_FILTER_COEFF_63; //BMP3_IIR_FILTER_COEFF_3
	settings.odr_filter.press_os = BMP3_OVERSAMPLING_2X;
	settings.odr_filter.temp_os = BMP3_NO_OVERSAMPLING;
	settings.odr_filter.odr = BMP3_ODR_50_HZ;

	settings_sel = BMP3_SEL_PRESS_EN | BMP3_SEL_TEMP_EN | BMP3_SEL_PRESS_OS | BMP3_SEL_TEMP_OS | BMP3_SEL_ODR |
				 BMP3_SEL_DRDY_EN | BMP3_SEL_IIR_FILTER;

	rslt = bmp3_set_sensor_settings(settings_sel, &settings, bmp388);

	if ( rslt !=  BMP3_OK )
	{
		printf("BMP388 set sensor settings failure !\n");
		Error_Handler();
	}

	printf("BMP388 set sensor settings success !\n");

	settings.op_mode = BMP3_MODE_NORMAL;
	rslt = bmp3_set_op_mode(&settings, bmp388);

	if ( rslt !=  BMP3_OK )
	{
		printf("BMP388 sensor op mode failure !\n");
		Error_Handler();
	}

	printf("BMP388 sensor op mode failure !\n");

	HAL_Delay(4000);

	return ( BMP3_INTF_RET_SUCCESS );

}

BMP3_INTF_RET_TYPE get_bmp388_sensor_data(struct bmp3_dev *bmp388,struct bmp3_data *bmp388_data)
{
	if( ( bmp388 == NULL ) || ( bmp388_data == NULL ) )
	{
		Error_Handler();
	}

	struct bmp3_status status = { { 0 } };
	int8_t rslt = 0U;

	rslt = bmp3_get_status(&status, bmp388);

	if ( rslt !=  BMP3_OK )
	{
		  printf("BMP388 sensor get status failure !\n");
		  Error_Handler();
	}

	/* Read temperature and pressure data iteratively based on data ready interrupt */
	if ( (rslt == BMP3_OK) && (status.intr.drdy == BMP3_ENABLE) )
	{
		  /*
		   * First parameter indicates the type of data to be read
		   * BMP3_PRESS_TEMP : To read pressure and temperature data
		   * BMP3_TEMP       : To read only temperature data
		   * BMP3_PRESS      : To read only pressure data
		   */
		  rslt = bmp3_get_sensor_data(BMP3_PRESS_TEMP, bmp388_data , bmp388);

		  if ( rslt !=  BMP3_OK )
		  {
			  printf("BMP388 sensor get status failure !\n");
			  Error_Handler();
		  }

		  /* NOTE : Read status register again to clear data ready interrupt status */
		  rslt = bmp3_get_status(&status, bmp388);

		  if ( rslt !=  BMP3_OK )
		  {
			  printf("BMP388 sensor get status failure !\n");
			  Error_Handler();
		  }
	}

	return ( BMP3_INTF_RET_SUCCESS );
}

BMP3_INTF_RET_TYPE calibration_bmp388_sensor(struct bmp3_dev *bmp388,struct bmp3_data *bmp388_data,uint32_t sample_count)
{
	if( ( bmp388 == NULL ) || ( bmp388_data == NULL ) || ( sample_count <= 0U) )
	{
		Error_Handler();
	}

	uint32_t iter = 0U;
	double calibration_data = 0.0f;
	double LowPassFilteredData = 0.0f;


	while ( iter++ < sample_count )
	{
		if ( get_bmp388_sensor_data(bmp388,bmp388_data) != BMP3_OK )
		{
			  printf("BMP388 sensor get data failure !\n");
			  Error_Handler();
		}

		LowPassFilteredData = LPF_BAR_ALPHA * LowPassFilteredData + (1.0f - LPF_BAR_ALPHA) * bmp388_data->pressure;

		calibration_data += LowPassFilteredData;

	}

	calibration_data /= (double)sample_count;

	bmp388_data->altitude[1] = - (LowPassFilteredData - calibration_data) / (DENSITY_AIR_KG_M3 * GRAVITY_AIR_KG_MPS2)/1000;
	return ( BMP3_INTF_RET_SUCCESS );
}


BMP3_INTF_RET_TYPE get_bmp388_altitude_data(struct bmp3_data *bmp388_data)
{
	static char key = 1U;

	if ( bmp388_data == NULL )
	{
		Error_Handler();
	}

	if ( key )
	{
		/*! @brief variable to hold the reference altitude value  */
		bmp388_data->altitude[0] = 44330.0f * (1.0f - powf((bmp388_data->pressure / SEA_LEVEL_PRESSURE), 0.19029495718f));
		key = 0U;
	}

	/*! @brief variable to hold the current altitude value  */
	bmp388_data->altitude[1] = 44330.0f * (1.0f - powf((bmp388_data->pressure / SEA_LEVEL_PRESSURE), 0.19029495718f));

	/*! @brief variable to hold the current z axis value  */
	bmp388_data->altitude[2] = fabs ( bmp388_data->altitude[1] - bmp388_data->altitude[0] );

	return ( BMP3_INTF_RET_SUCCESS );
}

double median_filter(double input_signal[],uint32_t signal_len)
{
	if ( ( signal_len == 0 ) && ( signal_len < 0 ) )
	{
		Error_Handler();
	}

	double sum = 0.0f;
	uint32_t temp = 0;
	temp = signal_len;

	while ( --signal_len > 0 )
	{
		sum += input_signal[signal_len];
	}

	signal_len = temp;

	sum = sum / (double) signal_len;

	return ( sum );
}

























