#ifndef INC_FLIGHT_CONTROL_H_
#define INC_FLIGHT_CONTROL_H_

#include <stdio.h>
#include "stm32f4xx.h"
#include "bmp3_defs.h"
#include "bmi160_defs.h"
#include "bmi160_port.h"
#include "bmp388_port.h"
#include "hmc5883l.h"

typedef enum
{
	FLIGHT_GUIDANCE = 1,
	FLIGHT_TAKE_OFF = 2




}FlightState_t;

struct FlightHardwareInterface_t
{
	struct bmp388_interface *pBMP388Interface;

	struct bmp160_interface *pBMI160Interface;

	struct hmc5883l_interface *pHMC5883LInterface;
};

struct FlightControlData_t
{
	struct hmc5883l_dev *pHMC5883L;

	struct bmi160_dev *pBMI160;

	struct bmp3_dev	*pBMP388;

	struct FlightHardwareInterface_t *pHardware;

	struct FlightControlParser_t *pFlightParser;

	FlightState_t fstat;

};


void flight_hardware_init(struct FlightControlData_t*);


#endif /* INC_FLIGHT_CONTROL_H_ */













