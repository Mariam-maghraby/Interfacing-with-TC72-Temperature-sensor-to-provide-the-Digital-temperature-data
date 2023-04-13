/*
 * SPI.h
 *
 *  Created on: Dec 17, 2022
 *      Author: MARIM
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

void SPI1_INIT(void);
void SPI1_Write(unsigned char data);
unsigned char SPI1_Read(void);
unsigned char SPI1_TransmitRecieveByte(unsigned char data);
void SPI1_CS_ENABLE(void);
void SPI1_CS_DISABLE(void);

#endif /* INC_SPI_H_ */
