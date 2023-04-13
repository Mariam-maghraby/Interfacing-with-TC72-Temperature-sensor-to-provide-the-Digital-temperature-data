/*
 * device.c
 *
 *  Created on: Mar 31, 2022
 *      Author: moham
 */
#include "stm32f4xx.h"
#include "gpio.h"
#include "device.h"
#include "TC72.h"
#include "LCD.h"

#define PIN 8

#define TC72_Select() (GPIO_WritePin(GPIOB,PIN,1))
#define TC72_UnSelect() (GPIO_WritePin(GPIOB,PIN,0))

void floatToString(float floatNum, char data[]);

void SPI_config(void);



float temp = 0;
unsigned char SPI_Data = 0;
char output2Data[] = {'-', ' ', ' ', '.', ' ', ' ', '\r', '\n', '\0'};



float Get_Temp_Data(void)
{
	SPI_config();

	/*LCD Display*/
	LCD_Init();

	SPI1_INIT();

	TC72_Select();
	TC72_Init((unsigned)0);
	TC72_UnSelect();

	temp = 0.0f;

	TC72_Select();
	/* read LSB @ 0x01 */
	/* read the floating pt */
	TC72_RegisterRead(0x01, &SPI_Data);
	TC72_UnSelect();

	if(SPI_Data & (1<<7)){
		/*2^(-1)*/
		temp +=0.5f;
	}

	if(SPI_Data & (1<<6)){
		/*2^(-2)*/
		temp +=0.25f;
	}

	TC72_Select();
	/* read MSB @ 0x02 */
	/* read the int vale */
	TC72_RegisterRead(0x02, &SPI_Data);
	TC72_UnSelect();

	temp += (signed char)SPI_Data; /*signed char type casting as data is -ve (-128)*/

	floatToString(temp, output2Data);
	LCD_DisplayString(output2Data);

	return temp;
}


void floatToString(float floatNum, char data[]){
	if (floatNum < 0){
		*data = '-';
		data++;
		floatNum *= -1;
	}
	int intNum = floatNum * 100;
	/* num + '0' converts the num to char */
	data[4] = (intNum % 10) + '0'; /* int 0 is 0000 0000  while char "0" is 0000 0011 */
	intNum /= 10;
	data[3] = (intNum % 10) + '0';
	data[2] = '.';
	intNum /= 10;
	data[1] = (intNum % 10) + '0';
	intNum /= 10;
	data[0] = (intNum % 10) + '0';

	data[5] = '\r';
	data[6] = '\n';
	data[7] = '\0';

}


void SPI_config(void){
	/*select slave*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIO_Init(GPIOB, PIN, 1 , 0);
	GPIO_WritePin(GPIOB, PIN, 0);
}


