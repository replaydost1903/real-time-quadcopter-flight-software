#ifndef BMI160_PORTING_INC_BMI160_PORT_H_
#define BMI160_PORTING_INC_BMI160_PORT_H_

#include <stdio.h>
#include "main.h"
#include "stm32f4xx.h"
#include "bmi160.h"

extern int8_t init_bmi160_sensor_driver_interface(struct bmi160_dev *bmi160);

/*
 *  local macro definitions
 */
#define BMI160_I2C_INTERFACE	(1U)			/*<! i2c interface communication, 1 - Enable; 0- Disable  <!*/
#define BMI160_SPI_INTERFACE	(0U)			/*<! spi interface communication, 1 - Enable; 0- Disable  <!*/

#define BMI160_DEV_ADDR			(0x68U)

extern void Error_Handler(void);

/*
 * Porting Function Declarations
 */
int8_t bmi160_i2c_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *read_data, uint16_t len);
int8_t bmi160_i2c_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);
void delay_ms(uint32_t period);


#endif /* BMI160_PORTING_INC_BMI160_PORT_H_ */
