#ifndef INC_FLIGHT_CONTROL_H_
#define INC_FLIGHT_CONTROL_H_

#include "stm32f4xx.h"
#include "bmp3_defs.h"
#include "bmi160_defs.h"
#include "bmi160_port.h"
#include "bmp388_port.h"
#include "hmc5883l.h"


struct FlightHardwareInterface_t
{
	struct bmp388_interface *pBMP388Interface;

	struct bmp160_interface *pBMI160Interface;

	struct hmc5883l_interface *pHMC5883LInterface;
};

struct FlightControlSystem_t
{
	struct hmc5883l_dev *pHMC5883L;

	struct bmi160_dev *pBMI160;

	struct bmp3_dev	*pBMP388;

	struct esc_dev	*pESC;

	struct FlightHardwareInterface_t *pHardware;

	struct FlightCommandInterface_t *pFlightParser;

};


//void Initialize_Sensor_Modules(struct FlightControlData_t*);


#endif /* INC_FLIGHT_CONTROL_H_ */













