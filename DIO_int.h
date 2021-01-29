/*
 * DIO_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: AHMED ADEL
 */

#ifndef DIO_INT_H_
#define DIO_INT_H_

#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3
////////////////////////////
#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7
////////////////////////////
#define OUTPUT 1
#define INPUT 0
#define ALL_OUTPUT 255
#define HIGH 1
#define LOW 0

void DIO_vidSetPortDirection(u8 u8PortCPY , u8 u8DirectionCPY);
void DIO_vidSetPortValue(u8 u8PortCPY , u8 u8ValueCPY);
u8 DIO_u8GetPortValue(u8 u8PortCPY);
void DIO_vidSetPinDirection(u8 u8PortCPY,u8 u8PinCPY,u8 u8DirectionCPY);
void DIO_vidSetPinValue(u8 u8PortCPY,u8 u8PinCPY,u8 u8ValueCPY);
u8 DIO_u8GetPinValue(u8 u8PortCPY,u8 u8PinCPY);
void DIO_vidWriteChannnelGroup(u8 PortIdLOC,u8 OffsetLOC , u8 MaskLOC,u8 Level);
void DIO_vidWriteDirectionGroup(u8 PortIdLOC,u8 OffsetLOC , u8 MaskLOC,u8 Direction);


#endif /* DIO_INT_H_ */
