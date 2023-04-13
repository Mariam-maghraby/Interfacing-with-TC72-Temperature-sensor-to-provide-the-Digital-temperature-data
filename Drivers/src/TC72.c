/*
 * TC72.c
 *
 *  Created on: Dec 17, 2022
 *      Author: MARIM
 */
#include "gpio.h"
#include "TC72.h"
#include "SPI.h"


void TC72_Init(unsigned char mode){
	/*Control write Address*/
	/*Continuous Temperature Conversion*/
	TC72_RegisterWrite(0x80, 0x00);
}


void TC72_RegisterWrite(unsigned char regAdd, unsigned char data){
	/*set bit 7 with register address*/
	SPI1_TransmitRecieveByte(regAdd | (1<<7));
	/*transmit the data */
	SPI1_TransmitRecieveByte(data);
}


void TC72_RegisterRead(unsigned char regAdd, unsigned char *dataPtr){
	/*transmit the address that will read from*/
	SPI1_TransmitRecieveByte(regAdd & (~(1<<7))); /* ~(1<<7) check bit 7 is cleared to read */
	 /* transmit data 0x00 (any dummy data) to read at the data pointer */
	*dataPtr = SPI1_TransmitRecieveByte(0x00);
}

