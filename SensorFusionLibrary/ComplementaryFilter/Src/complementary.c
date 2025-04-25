#include "complementary.h"

static double roll_acc = 0.0f , pitch_acc = 0.0f , yaw_acc = 0.0f;
static double roll_gyro = 0.0f , pitch_gyro = 0.0f , yaw_gyro = 0.0f;

extern void Error_Handler(void);


void Complementary_Init(struct complementary *pComp,double alpha,double sampling_time)
{
	if( pComp == NULL)
	{
		printf("Null pointer error !\n");
		Error_Handler();
	}

	if( !( ( alpha >= 0.0f ) && ( alpha <= 1.0f ) && ( sampling_time > 0.0f ) ) )
	{
		printf("Alpha must be [0-1] !\n");
		Error_Handler();
	}

	pComp->alpha = alpha;
	pComp->pitch = 0.0f;
	pComp->roll = 0.0f;
	pComp->yaw = 0.0f;
	pComp->ts = sampling_time / 1000.0f;

}
/**
 * @brief This function shall be executed either in polling or interrupt handler,
 *        specifically at the end of the given sampling period.
 *
 * @note  The timing of this function call is critical for the correct processing
 *        of sensor data.
 */
void Complementary_Update(struct complementary *pComp,\
						double ax,double ay,double az,double gx,double gy,double gz,double mx,double my,double mz)
{
	if( pComp == NULL)
	{
		printf("Null pointer error !\n");
		Error_Handler();
	}

	if( !( ( pComp->alpha >= 0.0f ) && ( pComp->alpha <= 1.0f ) && ( pComp->ts > 0.0f ) ) )
	{
		printf("Alpha must be [0-1] !\n");
		Error_Handler();
	}

	roll_gyro = ( roll_acc + ( gx * pComp->ts ) ) ;
	pitch_gyro = ( pitch_acc + ( gy * pComp->ts ) ) ;
	yaw_gyro = ( yaw_acc + ( gz * pComp->ts ) ) ;

	roll_acc = atan2(ay,az) * ( 180.0f / M_PI );
	pitch_acc = atan2(-ax, sqrt(ay * ay + az * az)) * ( 180.0f / M_PI );

	double bx=0.0f,by=0.0f;
	bx = mx * cos(roll_acc*(M_PI / 180.0f)) + my * sin(roll_acc*(M_PI / 180.0f)) * sin(pitch_acc*(M_PI / 180.0f)) + mz * sin(roll_acc*(M_PI / 180.0f)) * cos(pitch_acc*(M_PI / 180.0f));
	by = my * cos(pitch_acc*(M_PI / 180.0f)) - mz *sin(pitch_acc*(M_PI / 180.0f));
	yaw_acc = atan2(-by,bx) * ( 180.0f / M_PI );

	pComp->roll  = ( pComp->alpha * roll_gyro ) + ( 1 - pComp->alpha ) * ( roll_acc );
	pComp->pitch = ( pComp->alpha * pitch_gyro ) + ( 1 - pComp->alpha ) * ( pitch_acc );
	pComp->yaw = ( pComp->alpha * yaw_gyro ) + ( 1 - pComp->alpha ) * ( yaw_acc );
}
























