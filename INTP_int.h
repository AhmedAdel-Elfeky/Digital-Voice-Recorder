/*
 * INTP_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: AHMED ADEL
 */

#ifndef INTP_INT_H_
#define INTP_INT_H_

#define INT_0 0
#define INT_1 1
#define INT_2 2

#define INT_FALLING_EDGE 0
#define INT_RISING_EDGE 1
#define INT_LOW_LEVEL 2
#define INT_ANY_LOGIC_CHANGE 3

#define INT_ENABLE 1
#define INT_DISABLE 0

#define INT_0_PIN 2
#define INT_0_PORT PORT_D
#define INT_1_PIN 3
#define INT_1_PORT PORT_D
#define INT_2_PIN 2
#define INT_2_PORT PORT_B

///////////////////////////////////////////////////////////////////

void INT_vidSetInterruptEvent(u8 u8InterruptNumCPY, u8 u8EventCPY);
void INT_vidSetInterruptEnable(u8 u8InterruptNumCPY,u8 u8StateCPY);
void INT_vidSetInterruptGeneral(u8 u8StateCPY);



#endif /* INTP_INT_H_ */
