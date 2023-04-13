/*
 * pwd.h
 *
 *  Created on: Oct 20, 2022
 *      Author: MARIM
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

void pwm_init(void);
void set_level(unsigned char cnt);
void set_signal(float data);

#endif /* INC_PWM_H_ */
