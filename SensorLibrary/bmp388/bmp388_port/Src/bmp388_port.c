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

void delay_us(uint32_t period, void *intf_ptr)
{
	struct bmp388_interface *intf = (struct bmp388_interface *)intf_ptr;

	HAL_TIM_Base_Start_IT(intf->htim);

	while(counter != period);

	HAL_TIM_Base_Stop_IT(intf->htim);

	counter = 0U;
}

BMP3_INTF_RET_TYPE init_bmp388_sensor_driver_interface(struct bmp3_dev *bmp388,struct bmp388_interface *bmp388_intf)
{

	if( bmp388 == NULL )
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
	settings.odr_filter.press_os = BMP3_OVERSAMPLING_8X;
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

	HAL_Delay(3000);

	return ( BMP3_INTF_RET_SUCCESS );

}
















