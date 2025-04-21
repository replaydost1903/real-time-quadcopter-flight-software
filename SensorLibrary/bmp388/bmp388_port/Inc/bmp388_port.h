#ifndef BMP388_PORTING_INC_BMP388_PORT_H_
#define BMP388_PORTING_INC_BMP388_PORT_H_

#include <stdio.h>
#include "stm32f4xx.h"
#include "bmp3.h"
#include "bmp3_selftest.h"



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
BMP3_INTF_RET_TYPE init_bmp388_sensor_driver_interface(struct bmp3_dev*,struct bmp388_interface*);
void delay_us(uint32_t period, void *intf_ptr);























#endif /* BMP388_PORTING_INC_BMP388_PORT_H_ */
