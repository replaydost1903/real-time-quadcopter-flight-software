#ifndef	__KALMAN_FILTER_1D__
#define __KALMAN_FILTER_1D__

#include <math.h>

/*
 * These values must be changed accordingly before the kalman is initialised
 */
#define KALMAN_INITIAL_EST						((float)(68.0f))
#define KALMAN_INITIAL_ERROR_EST				((float)(2.0f))
#define KALMAN_INITIAL_ERROR_MEA				((float)(4.0f))

/*
 * 1D Kalman Filter Data Type
 */
typedef struct
{
	float gain;
	float est_error;
	float mea_error;
	float current_est;

}Kalman1D_t;

void Kalman1D_Init(Kalman1D_t *kalman);
void Kalman1D_Update(Kalman1D_t *kalman,float measured_value);

#endif
