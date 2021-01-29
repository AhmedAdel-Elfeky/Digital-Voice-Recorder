/*
 * ADC_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: AHMED ADEL
 */

#ifndef ADC_INT_H_
#define ADC_INT_H_

#define AVCC 0
#define AREF 1
#define V_256 2
#define LEFT_ADJ 0
#define RIGH_ADJ 1
#define PRESCALER_2   0
#define PRESCALER_4   1
#define PRESCALER_8   2
#define PRESCALER_16  3
#define PRESCALER_32  4
#define PRESCALER_64  5
#define PRESCALER_128 6
#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6
#define ADC7 7
#define ADC_ENABLE 1
#define ADC_DISABLE 0
#define ADC_8BIT_RESOLUSTION 0
#define ADC_10BIT_RESOLUSTION 1
/////////////////////////////////////////////////////
#define REF_VOLTAGE    AVCC
#define PRESCALER      PRESCALER_4
#define READING_ADJ    LEFT_ADJ
#define ADC_RESOLUTION ADC_8BIT_RESOLUSTION
/////////////////////////////////////////////////////

void ADC_vidInit(void);
void ADC_vidADCState(u8 u8StateCPY);
u16 ADC_u8GetADCReading(u8 u8ChannelCPY);


#endif /* ADC_INT_H_ */
