/*
 * PollDataClient.c
 *
 *  Created on: Mar 31, 2022
 *      Author: moham
 */
#include "stm32f4xx.h"
#include "gpio.h"
#include "PollingDataClient.h"
#include "PID.h"
#include "pwm.h"
#include "LCD.h"
#include "device.h"

/* Initialise PID controller */
PIDController pid = { PID_KP, PID_KI, PID_KD,
					  PID_TAU,
					  PID_LIM_MIN, PID_LIM_MAX,
		  PID_LIM_MIN_INT, PID_LIM_MAX_INT,
					  SAMPLE_TIME_S };

void floatToString(float floatNum, char data[]);

char PWM_outputSignal[] = {'-', ' ', ' ', '.', ' ', ' ', '\r', '\n', '\0'};

void Handle_data(float data)
{
	if(data > 30.0f)
	{

		PIDController_Init(&pid);
		float output_signal = PIDController_Update(&pid, 30.0f, data);
		LCD_DisplayString("PWM..\r\n");
//		GPIO_Init(GPIOA, 8, 1, 1);
		GPIO_Init(GPIOA,2,1,0);
//		GPIO_WritePin(GPIOA, 8, 1);
//		floatToString(output_signal , PWM_outputSignal);
//		LCD_DisplayString(PWM_outputSignal);
		pwm_init();
		set_level(output_signal*50);
//		set_signal(output_signal);
//		set_level(50);
//		while(data){
//		data --;
//		}
//		floatToString(data , PWM_outputSignal);
//		LCD_DisplayString(PWM_outputSignal);

		//GPIOA->ODR |= (1u<<5);
		if(data == 30.0f){
			set_level(0);
		}
		if(data <30.0f){
			PIDController_Init(&pid);
					float output_signal = PIDController_Update(&pid, 30.0f, data);
					LCD_DisplayString("PWM..\r\n");
			//		GPIO_Init(GPIOA, 8, 1, 1);
					set_level(output_signal*(-50));

		}
	}
	else
	{
		GPIOA->ODR &= ~(1u<<5);
	}
}
