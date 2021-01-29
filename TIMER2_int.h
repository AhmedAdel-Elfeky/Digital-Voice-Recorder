/*
 * TIMER2_init.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: AHMED ADEL
 */

#ifndef TIMER2_INT_H_
#define TIMER2_INT_H_

#define NORMAL_TIMER2			 1
#define CTC_TIMER2   	   		 2
#define FAST_PWM_TIMER2 		 3
#define PHASE_CORRECT_PWM_TIMER2 4

#define TIMER2_PRESCALER_0    0  //no clock source
#define TIMER2_PRESCALER_1    1  //no prescalling
#define TIMER2_PRESCALER_8    2
#define TIMER2_PRESCALER_32   3
#define TIMER2_PRESCALER_64   4
#define TIMER2_PRESCALER_128   5
#define TIMER2_PRESCALER_256  6
#define TIMER2_PRESCALER_1024 7

#define TIMER2_OVERFLOW_INTERRUPT_ENABLE    1
#define TIMER2_OVERFLOW_INTERRUPT_DISABLE   0
#define TIMER2_COMP_MATCH_INTERRUPT_ENABLE  1
#define TIMER2_COMP_MATCH_INTERRUPT_DISABLE 0

#define DISCONNECTED_OC2  0
#define CLEAR_OC2         3
#define SET_OC2    		  4
#define TOGGLE_OC2        5
#define OC2_PORT	      PORT_D
#define OC2_PIN		      PIN_7

/***************************configuration******************************************/
#define TIMER2_MODE                       FAST_PWM_TIMER2
#define TIMER2_PRESCALLER                 TIMER2_PRESCALER_1024
#define OC2_STATE                         CLEAR_OC2
#define TIMER2_OVERFLOW_INTERRUPT_STATE   TIMER2_OVERFLOW_INTERRUPT_ENABLE
#define TIMER2_COMP_MATCH_INTERRUPT_STATE TIMER2_COMP_MATCH_INTERRUPT_DISABLE
/**********************************************************************************/

void TIMER2_vidIntialize(void);
void TIMER2_vidSetPreloadValue(u8 u8PreloadRegCPY);
void TIMER2_vidSetCompareMatchValue(u8 u8CompareMacthCPY);





#endif /* TIMER2_INT_H_ */
