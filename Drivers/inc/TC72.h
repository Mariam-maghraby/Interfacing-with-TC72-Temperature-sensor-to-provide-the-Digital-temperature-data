/*
 * TC72.h
 *
 *  Created on: Dec 17, 2022
 *      Author: MARIM
 */

#ifndef INC_TC72_H_
#define INC_TC72_H_

void TC72_Init(unsigned char mode);
void TC72_RegisterWrite(unsigned char regAdd, unsigned char data);
void TC72_RegisterRead(unsigned char regAdd, unsigned char *dataPtr);



#endif /* INC_TC72_H_ */
