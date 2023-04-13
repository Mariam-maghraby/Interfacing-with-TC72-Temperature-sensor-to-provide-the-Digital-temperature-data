#include "stm32f4xx.h"
#include "gpio.h"
void GPIO_Init(GPIO_TypeDef * GPIOx,char pin,char dir,char state){
	/* enable pin is for RCC
	 PUPD to select between pull-up(1) and pull-down(0) if the dir=0(input)
*/
	if (GPIOx==GPIOA)
			RCC->AHB1ENR |= (1u<<0);
		else if (GPIOx==GPIOB)
			RCC->AHB1ENR |= (1u<<1);
		else if (GPIOx==GPIOC)
			RCC->AHB1ENR |= (1u<<2);
		else if (GPIOx==GPIOD)
			RCC->AHB1ENR |= (1u<<3);
		else if (GPIOx==GPIOE)
			RCC->AHB1ENR |= (1u<<4);
		else if (GPIOx==GPIOH)
			RCC->AHB1ENR |= (1u<<7);

	if (dir==1) //output
	{
			GPIOx->MODER|=(1<<(pin*2));
			GPIOx->MODER&=~(1<<(pin*2+1));

			if(state){
				GPIOx->OTYPER |= (1u<<pin);
			} else {
				GPIOx->OTYPER &=~ (1u<<pin);
			}
	}
	else if(dir==0) //input
	{
		GPIOx->MODER&=~(1<<(pin*2));
		GPIOx->MODER&=~(1<<(pin*2+1));

		if(state){ //pull-up
			GPIOx->PUPDR |=(1<<(pin*2));
			GPIOx->PUPDR&=~(1<<(pin*2+1));
		}
		else{//pull-down
			GPIOx->PUPDR |=(1<<(pin*2+1));
			GPIOx->PUPDR&=~(1<<(pin*2));
		}
	}
	else if(dir==2){//analog
		GPIOx->MODER&=~(1<<(pin*2));
		GPIOx->MODER|=(1<<(pin*2+1));

		//no pull-up pill-down
		GPIOx->PUPDR &=~(1<<(pin*2+1));
		GPIOx->PUPDR&=~(1<<(pin*2));
	}

}

int GPIO_WritePin (GPIO_TypeDef *GPIOx,char pin,char state){
	if(GPIOx->MODER&(1<<(pin*2))){
		if(state){
			GPIOx->ODR|=(1<<pin);
		}
		else{
			GPIOx->ODR&=~(1<<pin);
		}
		return 0;
	}
	else{
		return 1;
	}
}

int GPIO_ReadPin(GPIO_TypeDef *GPIOx,char pin){
	if(GPIOx->IDR&(1<<pin))
		return 1;
	else
		return 0;
}



