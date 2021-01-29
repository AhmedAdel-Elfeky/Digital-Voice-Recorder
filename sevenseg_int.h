/*
 * _7seg_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: AHMED ADEL
 */

#ifndef _7SEG_INT_H_
#define _7SEG_INT_H_

#define SEVENSEG_COM_ANODE  0
#define SEVENSEG_COM_CATHOD  1
#define SEVENSEG_MODE SEVENSEG_COM_CATHODE

#define SEVENSEG_PORT     PORT_B
#define SEVENSEG_PORT_REG DDRB_REG

#define SEVENSEG_1_CON_PORT  PORT_A
#define SEVENSEG_1_CON_PIN	 PIN_3
#define SEVENSEG_2_CON_PORT  PORT_A
#define SEVENSEG_2_CON_PIN	 PIN_1
#define SEVENSEG_3_CON_PORT  PORT_A
#define SEVENSEG_3_CON_PIN	 PIN_2

#if SEVENSEG_MODE == SEVENSEG_COM_CATHODE
void SEVENSEG_vidDisplay(u8 u8DataPortCPY,u8 u8NumCPY);
void SEVENSEG_vidDisplayOff(void);

#else

void SEVENSEG_vidDisplay7 (u8 u8DataPortCPY,u8 u8NumCPY );
#endif

#endif /* 7SEG_INT_H_ */
