/*
 * PID.h
 *
 *  Created on: Dec 18, 2022
 *      Author: MARIM
 */

#ifndef INC_PID_H_
#define INC_PID_H_

/* Controller parameters */
#define PID_KP  0.1f
#define PID_KI  0.01f
#define PID_KD  0.0f

#define PID_TAU 0.02f

#define PID_LIM_MIN -10.0f
#define PID_LIM_MAX  10.0f

#define PID_LIM_MIN_INT -5.0f
#define PID_LIM_MAX_INT  5.0f

#define SAMPLE_TIME_S 0.01f

typedef struct{

	/* controller gains */
	float kp;
	float ki;
	float kd;

	/* derivative low-pass filter constant */
	float tau;

	/* Output limits */
	float limMin;
	float limMax;

	/* Integrator limits */
	float limMinInt;
	float limMaxInt;

	/* sample time (in sec) */
	float T;

	/* controller (memory) */
	float integrator;
	float prevError;
	float differentiator;
	float prevMeasurement;

	/* controller o/p */
	float out;

} PIDController;

void PIDController_Init(PIDController *pid);
float PIDController_Update(PIDController *pid, float setpoint, float measurement);


#endif /* INC_PID_H_ */
