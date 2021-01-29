/*
 * AVR_DIOReg.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: AHMED ADEL
 */

#ifndef AVR_DIOREG_H_
#define AVR_DIOREG_H_
//every port has 3 registers
//portA
#define PORTA_REG *((volatile u8*)0x3B)
#define DDRA_REG  *((volatile u8*)0x3A)
#define PINA_REG  *((volatile u8*)0x39)
//portB
#define PORTB_REG *((volatile u8*)0x38)
#define DDRB_REG  *((volatile u8*)0x37)
#define PINB_REG  *((volatile u8*)0x36)
//portC
#define PORTC_REG *((volatile u8*)0x35)
#define DDRC_REG  *((volatile u8*)0x34)
#define PINC_REG  *((volatile u8*)0x33)
//portD
#define PORTD_REG *((volatile u8*)0x32)
#define DDRD_REG  *((volatile u8*)0x31)
#define PIND_REG  *((volatile u8*)0x30)


#endif /* AVR_DIOREG_H_ */
