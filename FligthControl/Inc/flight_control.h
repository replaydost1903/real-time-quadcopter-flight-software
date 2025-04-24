#ifndef INC_FLIGHT_CONTROL_H_
#define INC_FLIGHT_CONTROL_H_

#include <stdio.h>
#include "stm32f4xx.h"
#include "bmp3_defs.h"
#include "bmi160_defs.h"
#include "bmi160_port.h"
#include "bmp388_port.h"

typedef enum
{
	FLIGHT_GUIDANCE = 1,
	FLIGHT_TAKE_OFF = 2




}FlightState_t;

struct FlightHardwareInterface_t
{
	struct bmp388_interface *pBMP388Interface;

	struct bmp160_interface *pBMI160Interface;

};

struct FlightControlData_t
{
	struct FlightHardwareInterface_t *pHardware;

	struct FlightControlParser_t *pFlightParser;

	struct bmi160_dev *pBMI160;

	struct bmi160_sensor_data *pBMI160AccelData;

	struct bmi160_sensor_data *pBMI160GyroData;

	volatile int8_t bmi160_rslt;

	struct bmp3_dev	*pBMP388;

	struct bmp3_data *pBMP388Data;

	volatile int8_t bmp388_rslt;

	FlightState_t fstat;

};


void FligthInit(struct FlightControlData_t*);


#endif /* INC_FLIGHT_CONTROL_H_ */













