#include "stm32f4xx.h"
#include "gpio.h"
#include "LCD.h"
#include "SPI.h"
#include "TC72.h"
#include "PollerTimer.h"
#include "poller.h"

#define PIN 8

#define TC72_Select() (GPIO_WritePin(GPIOB,PIN,1))
#define TC72_UnSelect() (GPIO_WritePin(GPIOB,PIN,0))



void floatToString(float floatNum, char data[]);




int main(void)

{
	StartTimer();
	EnableInterrupt();
	SetPollingTime(500);
	StartPolling();

	while(1)
	{

		TIM2_IRQHandler();
	}

}

void TIM2_IRQHandler(void)
{
	TIM2->SR &=~(1<<0);
	CallPollingFunction();
}




