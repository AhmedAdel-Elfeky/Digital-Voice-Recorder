
/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: AHMED ADEL
 */
#include "utils.h"
#include "std_types.h"
#include "AVR_DIOReg.h"
#include "DIO_int.h"
#include "INTP_int.h"
#include "ADC_int.h"
#include <util/delay.h>
#include "sevenseg_int.h"
#include "TIMER0_int.h"
#include "TIMER2_int.h"
#include "SRAM_init.h"
#include <AVR/interrupt.h>
#define F_CPU 12000000UL

void Switch7segDisplay(void);


typedef struct
{
	u8 Record_Flag   :1    ;
	u8 PlayBack_Flag :1 ;
}Flags;

Flags f ;
u8 Voltage;
u16 timer;
u8 SevenSegSelect;
u8 SecondOnes_CTR;
u8 SecondTens_CTR;
u8 Minutes_CTR;
u8 OutputData;
u16 u16FinalAdrresInRecordLOC = 0;
u16 u16FinalAdrresInPlaybackLOC = 0;
u8 OneSencondFlag;
u8 ChangeDoneOn7segFlag;
u8 SampleFlage;
u8 DoneSamplingFlag;

int main(void)
{
	u16FinalAdrresInRecordLOC = 0;
	u16FinalAdrresInPlaybackLOC = 0;
	OneSencondFlag=0;
	ChangeDoneOn7segFlag = 0;

	f.PlayBack_Flag = 0;
	f.Record_Flag = 0;
	Voltage=0;
	timer = 0;
	OutputData = 0;

	/* INTURUPT configuration */
	INT_vidSetInterruptEvent(INT_0,INT_FALLING_EDGE);
	INT_vidSetInterruptEnable(INT_0,INT_ENABLE);
	INT_vidSetInterruptEvent(INT_1,INT_FALLING_EDGE);
	INT_vidSetInterruptEnable(INT_1,INT_ENABLE);
	INT_vidSetInterruptGeneral(INT_ENABLE);
	DIO_vidSetPinDirection(INT_0_PORT,INT_0_PIN,INPUT);
	DIO_vidSetPinValue(INT_0_PORT,INT_0_PIN,HIGH);
	DIO_vidSetPinDirection(INT_1_PORT,INT_1_PIN,INPUT);
	DIO_vidSetPinValue(INT_1_PORT,INT_1_PIN,HIGH);

	/* ADC configuration */
	DIO_vidSetPinDirection(PORTA,PIN0,INPUT);
	ADC_vidInit();
	ADC_vidADCState(ADC_ENABLE);

	/* TIMER0 configuration */
	DIO_vidSetPinDirection(OC2_PORT,OC2_PIN,OUTPUT);
	TIMER0_vidSetPreloadValue(68);
	TIMER0_vidIntialize();

	/* 7-SEG configuration*/
	(SEVENSEG_PORT_REG) = ((SEVENSEG_PORT_REG)&(~(0xff)))|(0xff<<0); // make 7seg direction
	DIO_vidWriteDirectionGroup(PORT_A,1,0x06,0x03); // the 2 - 7seg control pin_1 and pin_2 in port_A

	/* SRAM Configuration */
	DIO_vidSetPortDirection(LOW_BYTE_ADDRESS_PORT,ALL_OUTPUT);
	DIO_vidWriteDirectionGroup(LOW_NIBBLE_ADDRESS_PORT,4,0x70,0x07);
	DIO_vidWriteDirectionGroup(HIGH_NIBBLE_ADDRESS_PORT,3,0xf8,0x1f);
	DIO_vidWriteDirectionGroup(PORT_D,0,0x03,0x03); //control pin ( pin_0 & pin_1 )

	/* more configurations */
	while(1)
	{
		while(f.Record_Flag)
		{
			/* read from adc */
			Voltage = ADC_u8GetADCReading(ADC0);

			if(OneSencondFlag == 1) // to enter every 1 second
			{
				timer = 0;
				SecondOnes_CTR++;
				if(SecondOnes_CTR > 9)
				{
					SecondOnes_CTR = 0;
					SecondTens_CTR = SecondTens_CTR + 1;
				}else{}
				if(SecondTens_CTR > 5)
				{
					SecondTens_CTR = 0;
					SecondOnes_CTR = 0;
					Minutes_CTR++;
				}else{}
				if(Minutes_CTR > 9)
				{
					SecondOnes_CTR = 0;
					SecondTens_CTR = 0;
					Minutes_CTR = 0;
				}else{}
				ChangeDoneOn7segFlag =1;
			}else{}

			/* to not writing on the past values ,it take 9 seconds */
			if ((u16FinalAdrresInRecordLOC-1)== 0x7fff)
			{
				f.Record_Flag = 0;
			}else{}

			/* switch over 7-segments */
			Switch7segDisplay();
		}


		while(f.PlayBack_Flag)
		{
			/* disable 7-seg */
			SETBIT(PORTA_REG,1);
			SETBIT(PORTA_REG,2);
			SETBIT(PORTA_REG,3);

			/* make the port B input to read from sram */
			DIO_vidSetPortDirection(SRAM_DATA_PORT,INPUT);
			/* Get the data from sram */
			OutputData = SRAM_u8ReadData();
			TIMER2_vidSetCompareMatchValue(OutputData);
			u16FinalAdrresInPlaybackLOC = Address;
			/* make the port B out to display 7 segment */
			DIO_vidSetPortDirection(SRAM_DATA_PORT,ALL_OUTPUT);
			/* display 7-seg */
			Switch7segDisplay();

			/* to not writing on the past values ,it take 7 seconds */
			if ((u16FinalAdrresInPlaybackLOC-1)== 0x7fff || u16FinalAdrresInRecordLOC == Address)
			{
				f.PlayBack_Flag = 0;
			}else{}
		}

	}
	return 0;
}

ISR(INT0_vect)
{
	if(f.PlayBack_Flag == 0)
	{
		f.Record_Flag = !f.Record_Flag;
		if(f.Record_Flag)
		{
			DIO_vidSetPortDirection(SRAM_DATA_PORT,ALL_OUTPUT);
			SevenSegSelect=1;SecondOnes_CTR=0;SecondTens_CTR=0;Minutes_CTR=0;
			Address = 0;
		}else{}
	}else{}
}

ISR(INT1_vect)
{
	if(f.Record_Flag == 0)
	{
		f.PlayBack_Flag = !f.PlayBack_Flag;
		if(f.PlayBack_Flag)
		{
			SevenSegSelect=1;SecondOnes_CTR=0;SecondTens_CTR=0;Minutes_CTR=0;
			Address = 0;
		}else{}
	}else{}
}


ISR(TIMER0_OVF_vect)
{
	if (f.Record_Flag || f.PlayBack_Flag)
	{
		/* disable 7-seg to use 7-seg data port to write in sram */
		SETBIT(PORTA_REG,1);
		SETBIT(PORTA_REG,2);

		/* write in sram */
		u16FinalAdrresInRecordLOC = SRAM_u16WriteData(Voltage);


		timer++;
		TIMER0_vidSetPreloadValue(68);
		if(timer == 8000)
		{
			OneSencondFlag = 1;
			ChangeDoneOn7segFlag = 0;
		}
		else
		{
			if(ChangeDoneOn7segFlag == 1)
			{
				OneSencondFlag = 0;
				ChangeDoneOn7segFlag =0;
			}else{}
		}

	}
	else
	{
		timer = 0;
		SecondOnes_CTR = 0;
		SecondTens_CTR = 0;
		Minutes_CTR = 0;
		SEVENSEG_vidDisplayOff();
	}
}

void Switch7segDisplay(void)
{
	switch(SevenSegSelect)
	{
	case 1:
	{
		//DIO_vidSetPinValue(SEVENSEG_2_CON_PORT,SEVENSEG_2_CON_PIN,HIGH);
		//SETBIT(PORTA_REG,1);
		//DIO_vidSetPinValue(SEVENSEG_3_CON_PORT,SEVENSEG_3_CON_PIN,HIGH);
		SETBIT(PORTA_REG,2);
		//DIO_vidSetPinValue(SEVENSEG_1_CON_PORT,SEVENSEG_1_CON_PIN,LOW);
		SEVENSEG_vidDisplay(SEVENSEG_PORT,SecondOnes_CTR);
		RESETBIT(PORTA_REG,1);
		SevenSegSelect = 2;
		break;
	}
	case 2:
	{
		//DIO_vidSetPinValue(SEVENSEG_1_CON_PORT,SEVENSEG_1_CON_PIN,HIGH);
		//SETBIT(PORTA_REG,3);
		//DIO_vidSetPinValue(SEVENSEG_3_CON_PORT,SEVENSEG_3_CON_PIN,HIGH);
		SETBIT(PORTA_REG,1);
		//DIO_vidSetPinValue(SEVENSEG_2_CON_PORT,SEVENSEG_2_CON_PIN,LOW);
		SEVENSEG_vidDisplay(SEVENSEG_PORT,SecondTens_CTR);
		RESETBIT(PORTA_REG,2);
		SevenSegSelect = 1;
		break;
	}
	/*
	case 3:
	{
		//DIO_vidSetPinValue(SEVENSEG_1_CON_PORT,SEVENSEG_1_CON_PIN,HIGH);
		SETBIT(PORTA_REG,3);
		//DIO_vidSetPinValue(SEVENSEG_2_CON_PORT,SEVENSEG_2_CON_PIN,HIGH);
		SETBIT(PORTA_REG,1);
		//DIO_vidSetPinValue(SEVENSEG_3_CON_PORT,SEVENSEG_3_CON_PIN,LOW);
		SEVENSEG_vidDisplay(SEVENSEG_PORT,Minutes_CTR);
		RESETBIT(PORTA_REG,2);
		SevenSegSelect = 1;
		break;
	}
	*/
	default:break;
	}

}








