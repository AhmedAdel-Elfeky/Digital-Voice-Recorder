/*
 * TIMER_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: AHMED ADEL
 */
#include "std_types.h"
#include "TIMER0_int.h"
#include "utils.h"

#define TCCR0  *((volatile u8*)0x53)
#define TCNT0  *((volatile u8*)0x52)
#define TIMSK  *((volatile u8*)0x59)
#define SREG   *((volatile u8*)0x5F)
#define OCR0   *((volatile u8*)0x5C)

void (*PointerToFunc)(void);


void TIMER0_vidIntialize(void)
{
	// timer mode
#if TIMER0_MODE==NORMAL_TIMER0
	RESETBIT(TCCR0,6);
	RESETBIT(TCCR0,3);
	SETBIT(TIMSK,0); // enable interrupt for over flow
#elif TIMER0_MODE==CTC_TIMER0
	RESETBIT(TCCR0,6);
	SETBIT(TCCR0,3);
	SETBIT(TIMSK,1); // enable interrupt for compare match
	#if OC0_STATE == DISCONNECTED_OC0
		RESETBIT(TCCR0,4);
		RESETBIT(TCCR0,5);
	#elif OC0_STATE == CLEAR_OC0
		RESETBIT(TCCR0,4);
		SETBIT(TCCR0,5);
	#elif OC0_STATE == SET_OC0 // set pin oc0 on compare match
		SETBIT(TCCR0,4);
		SETBIT(TCCR0,5);
	#else  // TOGGLE OC0
		SETBIT(TCCR0,4);
		RESETBIT(TCCR0,5);
	#endif

#elif TIMER0_MODE == PHASE_CORRECT_PWM_TIMER0
	SETBIT(TCCR0,6);
	RESETBIT(TCCR0,3);

	#if OC0_STATE == DISCONNECTED_OC0
		RESETBIT(TCCR0,4);
		RESETBIT(TCCR0,5);
	#elif OC0_STATE == NON_INVERTING_OC0
		RESETBIT(TCCR0,4);
		SETBIT(TCCR0,5);
	#elif OC0_STATE == INVERTING_OC0
		SETBIT(TCCR0,4);
		SETBIT(TCCR0,5);
	#endif

#elif TIMER0_MODE == FAST_PWM_TIMER0
	SETBIT(TCCR0,6);
	SETBIT(TCCR0,3);
	SETBIT(TIMSK,0); // enable interrupt for over flow
	#if OC0_STATE == DISCONNECTED_OC0
		RESETBIT(TCCR0,4);
		RESETBIT(TCCR0,5);
	#elif OC0_STATE == NON_INVERTING_OC0
		RESETBIT(TCCR0,4);
		SETBIT(TCCR0,5);
	#elif OC0_STATE == INVERTING_OC0
		SETBIT(TCCR0,4);
		SETBIT(TCCR0,5);
	#endif

#endif

   // pre-scaler
#if TIMER0_PRESCALLER == TIMER0_PRESCALER_0  // no clock source
	RESETBIT(TCCR0,2);
	RESETBIT(TCCR0,1);
	RESETBIT(TCCR0,0);
#elif TIMER0_PRESCALLER == TIMER0_PRESCALER_1
	RESETBIT(TCCR0,2);
	RESETBIT(TCCR0,1);
	SETBIT(TCCR0,0);
#elif TIMER0_PRESCALLER == TIMER0_PRESCALER_8
	RESETBIT(TCCR0,2);
	SETBIT(TCCR0,1);
	RESETBIT(TCCR0,0);
#elif TIMER0_PRESCALLER == TIMER0_PRESCALER_64
	RESETBIT(TCCR0,2);
	SETBIT(TCCR0,1);
	SETBIT(TCCR0,0);
#elif TIMER0_PRESCALLER == TIMER0_PRESCALER_256
	SETBIT(TCCR0,2);
	RESETBIT(TCCR0,1);
	RESETBIT(TCCR0,0);
#elif TIMER0_PRESCALLER == TIMER0_PRESCALER_1024
	SETBIT(TCCR0,2);
	RESETBIT(TCCR0,1);
	SETBIT(TCCR0,0);
#endif

	// enable global interrupts
	SETBIT(SREG,7);

	return;
}

void TIMER0_vidSetPreloadValue(u8 u8PreloadRegCPY)
{
	TCNT0=u8PreloadRegCPY;
	return;
}

void TIMER0_vidSetCompareMatchValue(u8 u8CompareMacthCPY)
{
	OCR0=u8CompareMacthCPY;
	return;
}

void TIMER0_vidSetCallBackFun(void (*Pointer)(void))
{
	if(Pointer!=0)
	{
		PointerToFunc=Pointer;
	}
	else{}

	return;
}

