#include <KalmanFilter1D.h>

extern void Error_Handler(void);

void Kalman1D_Init(Kalman1D_t *kalman)
{
	/*<! Check null-pointer  <!*/
	if ( kalman == NULL )
	{
		Error_Handler();
	}

	/*<! 1D Kalman Initial Value  <!*/
	kalman->gain 		= 	0.0f;
	kalman->current_est = 	KALMAN_INITIAL_EST;
	kalman->est_error 	= 	KALMAN_INITIAL_ERROR_EST;
	kalman->mea_error 	= 	KALMAN_INITIAL_ERROR_MEA;
}


void Kalman1D_Update(Kalman1D_t *kalman,float measured_value)
{
	/*<! Check null-pointer  <!*/
	if ( kalman == NULL )
	{
		Error_Handler();
	}

	/*<! Calculate the Kalman Gain  <!*/
	kalman->gain = ( kalman->est_error /
			( kalman->est_error + kalman->mea_error ) );

	/*<! Calculate the Current Estimate  <!*/
	kalman->current_est = ( kalman->current_est + \
			( kalman->gain * ( measured_value - kalman->current_est ) ) );

	/*<! Calculate the Current Estimate Error  <!*/
	kalman->est_error = ( ( 1 - kalman->gain ) * kalman->est_error );

}










