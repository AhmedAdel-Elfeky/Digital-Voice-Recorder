/*
 * ADC_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: AHMED ADEL
 */
#include "std_types.h"
#include "utils.h"
#include "ADC_int.h"

#define ADCSRA *((volatile u8*)0x26)
#define ADMUX  *((volatile u8*)0x27)
#define ADCH   *((volatile u8*)0x25)
#define ADCL   *((volatile u8*)0x24)

void ADC_vidInit(void)
{
	#if REF_VOLTAGE == AVCC
		SETBIT(ADMUX,6);
		RESETBIT(ADMUX,7);
	#elif REF_VOLTAGE == AREF
		RESETBIT(ADMUX,6);
		RESETBIT(ADMUX,7);
	else //V_256
		SETBIT(ADMUX,6);
		SETBIT(ADMUX,7);
	#endif
	//prescaler
	#if PRESCALER == PRESCALER_2
		RESETBIT(ADCSRA,0);
		RESETBIT(ADCSRA,1);
		RESETBIT(ADCSRA,2);
	#elif PRESCALER == PRESCALER_4
		RESETBIT(ADCSRA,0);
		SETBIT(ADCSRA,1);
		RESETBIT(ADCSRA,2);
	#elif PRESCALER == PRESCALER_8
		SETBIT(ADCSRA,0);
		SETBIT(ADCSRA,1);
		RESETBIT(ADCSRA,2);
	#elif PRESCALER == PRESCALER_16
		RESETBIT(ADCSRA,0);
		RESETBIT(ADCSRA,1);
		SETBIT(ADCSRA,2);
	#elif PRESCALER == PRESCALER_32
		SETBIT(ADCSRA,0);
		RESETBIT(ADCSRA,1);
		SETBIT(ADCSRA,2);
	#elif PRESCALER == PRESCALER_64
		RESETBIT(ADCSRA,0);
		SETBIT(ADCSRA,1);
		SETBIT(ADCSRA,2);
	#else // PRESCALLER == PRESCALLER_128
		SETBIT(ADCSRA,0);
		SETBIT(ADCSRA,1);
		SETBIT(ADCSRA,2);
	#endif
		// Reading adjustment
	#if READING_ADJ == LEFT_ADJ
		SETBIT(ADMUX,5);
	#else
		RESETBIT(ADMUX,5);
	#endif

    return;
}

void ADC_vidADCState(u8 u8StateCPY)
{
	switch(u8StateCPY)
	{
	case ADC_ENABLE:
		SETBIT(ADCSRA,7); // enable ADC
		break;
	case ADC_DISABLE:
		RESETBIT(ADCSRA,7);
		break;
	default: break;
	}
	return;
}
u16 ADC_u8GetADCReading(u8 u8ChannelCPY)
{
	u16 u16AdcValueLOC;
	// select channel
	switch(u8ChannelCPY)
	{
	case ADC0:
		{
			RESETBIT(ADMUX,0);
			RESETBIT(ADMUX,1);
			RESETBIT(ADMUX,2);
			RESETBIT(ADMUX,3);
			RESETBIT(ADMUX,4);
			break;
		}
	case ADC1:
		{
			SETBIT(ADMUX,0);
			RESETBIT(ADMUX,1);
			RESETBIT(ADMUX,2);
			RESETBIT(ADMUX,3);
			RESETBIT(ADMUX,4);
			break;
		}
	case ADC2:
		{
			RESETBIT(ADMUX,0);
			SETBIT(ADMUX,1);
			RESETBIT(ADMUX,2);
			RESETBIT(ADMUX,3);
			RESETBIT(ADMUX,4);
			break;
		}
	case ADC3:
		{
			SETBIT(ADMUX,0);
			SETBIT(ADMUX,1);
			RESETBIT(ADMUX,2);
			RESETBIT(ADMUX,3);
			RESETBIT(ADMUX,4);
			break;
		}
	case ADC4:
		{
			RESETBIT(ADMUX,0);
			RESETBIT(ADMUX,1);
			SETBIT(ADMUX,2);
			RESETBIT(ADMUX,3);
			RESETBIT(ADMUX,4);
			break;
		}
	case ADC5:
		{
			SETBIT(ADMUX,0);
			RESETBIT(ADMUX,1);
			SETBIT(ADMUX,2);
			RESETBIT(ADMUX,3);
			RESETBIT(ADMUX,4);
			break;
		}
	case ADC6:
		{
			RESETBIT(ADMUX,0);
			SETBIT(ADMUX,1);
			SETBIT(ADMUX,2);
			RESETBIT(ADMUX,3);
			RESETBIT(ADMUX,4);
			break;
		}
	case ADC7:
		{
			SETBIT(ADMUX,0);
			SETBIT(ADMUX,1);
			SETBIT(ADMUX,2);
			RESETBIT(ADMUX,3);
			RESETBIT(ADMUX,4);
			break;
		}
	}
	// start conversion
	SETBIT(ADCSRA,6);

	// wait on flag till conversion complete
	//flag_bit=GETBIT(ADCSRA,4);

	while(GETBIT(ADCSRA,4)==0)
	{
		///
	}
 //// read ADCH ADCL
#if READING_ADJ == LEFT_ADJ
	#if ADC_RESOLUTION == ADC_10BIT_RESOLUSTION
	u16AdcValueLOC=(u16)(ADCH<<2)|ADCL>>6;
    #else //8bit
	u16AdcValueLOC=ADCH;
	#endif
#else //Righ
	#if ADC_RESOLUTION == ADC_10BIT_RESOLUSTION
	u16AdcValueLOC=(ADCH<<8)|(u16)ADCL;
	#else //8bit
	u16AdcValueLOC=ADCH<<6;
	#endif
#endif
    // write zero on flag=0
    SETBIT(ADCSRA,4);

    return u16AdcValueLOC;
}
