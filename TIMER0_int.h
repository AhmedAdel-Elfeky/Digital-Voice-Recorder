/*
 * TIMER_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: AHMED ADEL
 */
#ifndef TIMER0_INT_H_
#define TIMER0_INT_H_

#define NORMAL_TIMER0			 1
#define CTC_TIMER0   	   		 2
#define FAST_PWM_TIMER0 		 3
#define PHASE_CORRECT_PWM_TIMER0 4
#define TIMER0_PRESCALER_0 0  //no clock source
#define TIMER0_PRESCALER_1 1  //no prescalling
#define TIMER0_PRESCALER_8 2
#define TIMER0_PRESCALER_64 3
#define TIMER0_PRESCALER_256 4
#define TIMER0_PRESCALER_1024 5
#define DISCONNECTED_OC0  0
#define NON_INVERTING_OC0 1
#define INVERTING_OC0     2
#define CLEAR_OC0         3
#define SET_OC0    		  4
#define TOGGLE_OC0        5
#define OC0_PORT	      PORT_B
#define OC0_PIN		      PIN_3
/*****************************************configuration***************************************/
#define TIMER0_MODE       FAST_PWM_TIMER0
#define TIMER0_PRESCALLER TIMER0_PRESCALER_1024
#define OC0_STATE         DISCONNECTED_OC0
/*********************************************************************************************/
void TIMER0_vidIntialize(void);
void TIMER0_vidSetPreloadValue(u8 u8PreloadRegCPY);
void TIMER0_vidSetCompareMatchValue(u8 u8CompareMacthCPY);
void TIMER0_vidSetCallBackFun(void (*Pointer)(void));
#endif /* TIMER0_INT_H_ */
