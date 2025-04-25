#ifndef _INC_COMPLEMENTARY_H_
#define _INC_COMPLEMENTARY_H_


#include <stdio.h>
#include <math.h>


struct complementary
{
	double alpha;
	double roll;
	double pitch;
	double yaw;
	double ts;				/*! @brief variable must be ms unit */
};

extern void Complementary_Init(struct complementary *pComp,double alpha,double sampling_time);
extern void Complementary_Update(struct complementary *pComp,\
						double ax,double ay,double az,double gx,double gy,double gz,double mx,double my,double mz);

#endif
