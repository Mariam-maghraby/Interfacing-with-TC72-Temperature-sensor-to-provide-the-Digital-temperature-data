/*
 * pwd.c
 *
 *  Created on: Oct 20, 2022
 *      Author: MARIM
 */

#include "pwm.h"
#include "stm32f4xx.h" /*device header file*/


void pwm_init(void){

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	//configure pin 8 as alternate fn
	//10: Alternate function mode
	GPIOA -> MODER &= GPIO_MODER_MODER8_0;
	GPIOA -> MODER |= GPIO_MODER_MODER8_1;

	//set no pull-up and no pull-down
	GPIOA->PUPDR &= ~(1<<16);
	GPIOA->PUPDR &= ~(1<<17);

	//select alternate fn mode AF1 for GPIO A PIN 8
	GPIOA -> AFR[1] |= (1u<< 0);
	GPIOA -> AFR[1] &= ~(7u<<1);

	//Enable TIM1 clk
	//Bit 0 TIM1EN: TIM1 clock enable at RCC_APB2ENR
	RCC->APB2ENR |= (1<<0);

	//enable TIM1
	//Bit 0 CEN: Counter enable
	TIM1 ->CR1 |= (1<<0);

	//Enable auto-reload preload
	TIM1->CR1 |= (1<<7);             //Bit 7 ARPE: Auto-reload pre-load enable

	//set counter direction as up-counter
	TIM1->CR1 &= ~(1<<4);     //Bit 4 DIR: Direction,  0: Counter used as up-counter

	//set timer prescaler, maximum value of fHCLK = 84 MHz.
	//The counter clock frequency (CK_CNT) is equal to fCK_PSC/ (PSC[15:0] + 1).
	//PSC contains the value to be loaded in the active prescaler register at each update event
	//100000 Hz -> time base = 10us
	TIM1 ->PSC = 1799;

	//select output compare 1 PWD mode 1
	//Bits 6:4 OC1M: 110: PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive.
	TIM1->CCMR1 |= (1<<6);
	TIM1->CCMR1 |= (1<<5);
	TIM1->CCMR1 &= ~(1<<4);
	//Output Compare 2 mode
	//Bits 14:12 OC2M[2:0]: Output Compare 2 mode
//	TIM1->CCMR1 |= (1<<14);
//	TIM1->CCMR1 |= (1<<13);
//	TIM1->CCMR1 &= ~(1<<12);

	//select capture/compare 1 output polarity is active high
	//CC1P: Bit 1 = 0 -> OC1 active high
//	TIM1->CCER |= (1<<1);
	TIM1->CCER &= ~TIM_CCER_CC1P;

	//Initialize all the registers
	//Bit 0 UG: Update generation
	//Bit 0 = 1 -> Reinitialize the counter and generates an update of the registers
	TIM1->EGR |= (1<<0);

	//enable capture/compare channel 1 output
	// Bin 0 = 1 ->signal is output on the corresponding output pin
	TIM1->CCER |= (1<<0);

	//enable timer main output
	//Bit 15 MOE: Main output enable
	TIM1->BDTR |= (1<<15);

	//enable TIM1
	//Bit 0 CEN: Counter enable
	TIM1 ->CR1 |= (1<<0);



}


void set_level(unsigned char cnt){

	TIM1 -> ARR = 100000/20000;

	/*
	 * Update CCR1 with duty cycle
	 * PWM_Output_duty_cycle = (TIM1->CCR1 / TIM1->ARR) * 100
	 * TIM1->CCR1 = (PWM_OUTput_duty_cycle * TIM1->ARR) / 100
	 */
	TIM1 -> CCR1 = (100000/20000) *(cnt) /100;
}

void set_signal(float data){
	TIM1 -> ARR = 100000/20000;
	if(data <= 0.0f){
		TIM1 -> CCR1 = 0;
	}
	if (data >= 128.0f){
		TIM1 -> CCR1 = 0.73;
	}
	else{
		TIM1 -> CCR1 = 0.73*(data/13.0f);
	}
}


