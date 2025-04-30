#ifndef BMP388_PORTING_INC_BMP388_PORT_H_
#define BMP388_PORTING_INC_BMP388_PORT_H_

#include <stdio.h>
#include <math.h>
#include "stm32f4xx.h"
#include "bmp3.h"
#include "bmp3_selftest.h"

#define SEA_LEVEL_PRESSURE 		( ( double )( 101325.0f ) )
#define DENSITY_AIR_KG_M3		( ( double )( 1.225f ) )
#define GRAVITY_AIR_KG_MPS2		( ( double )( 9.81f ) )
#define LPF_BAR_ALPHA			( ( double )(  0.3f ) )

#define BMP388_DEV_ADDR				( 0x76U )
#define BMP388_DEV_ADDR_WRITE		( BMP388_DEV_ADDR << 1U )
#define BMP388_DEV_ADDR_READ		( ( ( BMP388_DEV_ADDR << 1U ) | 0x1U ))


struct bmp388_interface
{
	TIM_HandleTypeDef *htim;
    I2C_HandleTypeDef *hi2c;
    uint8_t dev_addr;
};

BMP3_INTF_RET_TYPE bmp388_read(uint8_t reg_addr, uint8_t *read_data, uint32_t len, void *intf_ptr);
BMP3_INTF_RET_TYPE bmp388_write(uint8_t reg_addr, const uint8_t *read_data, uint32_t len,void *intf_ptr);
BMP3_INTF_RET_TYPE bmp388_interface_init(struct bmp3_dev*,struct bmp388_interface*);
BMP3_INTF_RET_TYPE get_bmp388_sensor_data(struct bmp3_dev*,struct bmp3_data*);
BMP3_INTF_RET_TYPE get_bmp388_altitude_data(struct bmp3_data*);
void delay_us(uint32_t period, void *intf_ptr);
double median_filter(double input_signal[],uint32_t signal_len);
BMP3_INTF_RET_TYPE bmp388_calibration(struct bmp3_dev *bmp388,struct bmp3_data *bmp388_data,uint32_t sample_count);




















#endif /* BMP388_PORTING_INC_BMP388_PORT_H_ */
