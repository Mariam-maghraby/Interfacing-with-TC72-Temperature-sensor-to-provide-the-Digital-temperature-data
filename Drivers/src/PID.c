/*

* PID.c
 *
 *  Created on: Dec 18, 2022
 *      Author: MARIM
 */

#include "PID.h"

void PIDController_Init(PIDController *pid){

	/* clear controller variables */
	pid ->integrator = 0.0f;
	pid ->prevError = 0.0f;
	pid ->differentiator = 0.0f;
	pid ->prevMeasurement = 0.0f;
	pid ->out = 0.0f;

}

float acctemp = 0 ;
float PIDController_Update(PIDController *pid, float setpoint, float measurement){

//	float pidOut ;

	acctemp += (measurement - setpoint);
	pid->out = (acctemp *0.01) + (0.1 * (measurement - setpoint));
	return pid->out;

}

