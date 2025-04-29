#include "flight_control.h"

/*<! This function declared in main.c file !>*/
extern void Error_Handler(void);

void flight_hardware_init(struct FlightControlData_t *pFlightData)
{
	uint8_t temp = 0U;
	temp = (pFlightData == NULL) || (pFlightData->pBMI160 == NULL)    ||\
		   (pFlightData->pBMP388 == NULL) || (pFlightData->pBMI160AccelData == NULL)  ||\
		   (pFlightData->pBMI160GyroData == NULL) || (pFlightData->pBMP388Data == NULL);

	/*<! null pointer check !>*/
	if ( temp == 1U )
	{
		Error_Handler();
	}

	temp = 0;




//	/*<! bmi160 interface enable !>*/
//	pFlightData->bmi160_rslt = init_bmi160_sensor_driver_interface(pFlightData->pBMI160);
//
//	if ( pFlightData->bmi160_rslt != BMI160_OK )
//	{
//		printf("BMI160 initialization failure !\n");
//		Error_Handler();
//	}
//
//	printf("BMI160 initialization success !\n");





}







































