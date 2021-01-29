/*
 * LCD_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: AHMED ADEL
 */
#define F_CPU 12000000
#include "std_types.h"
#include "utils.h"
#include <util\delay.h>
#include "DIO_int.h"
#include "LCD_int.h"

//#include <stdio.h>
#include <stdlib.h>
//#include "string.h"

#if LCD_MODE == _8BIT
void LCD_vidSendCommand(u8 u8CommandCPY)
{
	DIO_vidSetPinValue(LCD_CONTROL_PORT,RS,LOW);
	DIO_vidSetPinValue(LCD_CONTROL_PORT,RW,LOW);
	DIO_vidSetPortValue(LCD_PORT ,u8CommandCPY );
	DIO_vidSetPinValue(LCD_CONTROL_PORT,E,HIGH);
	_delay_ms(1);
	DIO_vidSetPinValue(LCD_CONTROL_PORT,E,LOW);
	return;
}

void LCD_vidIntialize8Bit(void)
{
	/* Delay 100ms to ensure the initialization of the LCD driver */
		  _delay_ms(90);

		  /* Return Home  */
		  LCD_vidSendCommand(0b00000010);
		  _delay_ms(15);

		  /* Function Set  */
		  LCD_vidSendCommand(0b00111000);
		  _delay_ms(1);

		  /* Display ON OFF Control */
		  LCD_vidSendCommand(0b00001111);
		  _delay_ms(1);

		  /* Clear Display */
		  LCD_vidSendCommand(0b00000001);
		  _delay_ms(15);

		  /* Entry Mode Set  */
		  LCD_vidSendCommand(0b00000110);
		  _delay_ms(2);
		  return;

}

void LCD_vidSendData(u8 u8DataCPY)
{
	DIO_vidSetPinValue(LCD_CONTROL_PORT,RS,1);
	DIO_vidSetPinValue(LCD_CONTROL_PORT,RW,0);
	DIO_vidSetPortValue(LCD_PORT ,u8DataCPY );
	DIO_vidSetPinValue(LCD_CONTROL_PORT,E,1);
	_delay_ms(1);
	DIO_vidSetPinValue(LCD_CONTROL_PORT,E,0);

}

void LCD_vidSendString(u8 *u8StringCPY)
{
	while( *u8StringCPY  )
	{
		LCD_vidSendData(*u8StringCPY);
		u8StringCPY++;
	}
	return;
}

void LCD_vidSendNumber(u64 u8VariableCPY )
{
	u8 u8StringConversion[8];
	itoa(u8VariableCPY, u8StringConversion ,10);
	LCD_vidSendString(u8StringConversion);
	return;
}

void LCD_vidClear_Display(void)
{
	LCD_vidSendCommand(0b00000001);
	return;
}

void LCD_vidReturn_home(void)
{
	LCD_vidSendCommand(0b00000010);
	return;
}

void LCD_vidGotoxy (u8 u8ROWCPY,u8 u8COLCPY)
{
	if (u8COLCPY>0 && u8COLCPY<=16)
	{
	    switch(u8ROWCPY)
	    {
		    case 1:
		    	LCD_vidSendCommand(u8COLCPY+127);
		    	break;
		    case 2:
		    	LCD_vidSendCommand(u8COLCPY+191);
		    	break;
		    default:break;
	    }
	}else{}
}

u8 LCD_u8CheckBusy(void)
{
	u8 u8BusyFlagLOC;
	//u must make the lcd port  input
	DIO_vidSetPortDirection(LCD_PORT,INPUT);
	DIO_vidSetPortValue(LCD_PORT,ALL_OUTPUT); //pull up
	//rw high and rs low
	DIO_vidSetPinValue(LCD_CONTROL_PORT,RW,HIGH);
	DIO_vidSetPinValue(LCD_CONTROL_PORT,RS,LOW);
	u8BusyFlagLOC=DIO_u8GetPortValue(LCD_PORT);
	// return lcd port output
	DIO_vidSetPortDirection(LCD_PORT,ALL_OUTPUT);
	(u8BusyFlagLOC) >>= 7;
	return u8BusyFlagLOC;
}


u8 LCD_u8ReadAC(void)
{
	u8 u8AddressCounter;
	//u must make the lcd port  input
	DIO_vidSetPortDirection(LCD_PORT,INPUT);
	DIO_vidSetPortValue(LCD_PORT,ALL_OUTPUT); //pull up
	//rw high and rs low
	DIO_vidSetPinValue(LCD_CONTROL_PORT,RW,HIGH);
	DIO_vidSetPinValue(LCD_CONTROL_PORT,RS,LOW);
	u8AddressCounter=DIO_u8GetPortValue(LCD_PORT);
	// return lcd port output
	DIO_vidSetPortDirection(LCD_PORT,ALL_OUTPUT);
	(u8AddressCounter) &=(~(1<<7)) ; //you get the address counter
	return u8AddressCounter;
}

void LCD_vidEntryModeSet(u8 u8EnteryModeCPY)
{
	LCD_vidSendCommand(u8EnteryModeCPY);
	return;
}

void LCD_vidSetCGRAMAddress(u8 u8AddressCPY)
{
	u8AddressCPY|=(1<<6);
	LCD_vidSendCommand(u8AddressCPY);
	return;
}

void LCD_vidSetDDRAMAddress(u8 u8AddressCPY)
{
	u8AddressCPY|=(1<<7);
	LCD_vidSendCommand(u8AddressCPY);
	return;
}

void LCD_vidSetCustomChar(void)
{
	//set the first address of cgram is 0x48 and all locations is 64*8 start is 0x48
	LCD_vidSetCGRAMAddress(0x48);
	//your data
	LCD_vidSendData(0b00000111);
	LCD_vidSendData(0b00000100);
	LCD_vidSendData(0b00011111);
	LCD_vidSendData(0b00000100);
	LCD_vidSendData(0b00000100);
	LCD_vidSendData(0b00000100);
	LCD_vidSendData(0b00000100);
	LCD_vidSendData(0b00000100);

	LCD_vidSendData(0b00011111);
	LCD_vidSendData(0b00011111);
	LCD_vidSendData(0b00011111);
	LCD_vidSendData(0b00011111);
	LCD_vidSendData(0b00011111);
	LCD_vidSendData(0b00011111);
	LCD_vidSendData(0b00011111);
	LCD_vidSendData(0b00011111);
	///
	// set the address of dd ram to continoue
	LCD_vidSetDDRAMAddress(0x00);

	// the addresses of your data is 0x01 to 0x08
	//LCD_vidSendData(0x01 to 0x08);
	return;
}


#else

u8 Counter =0 ;
void LCD_vidSendCommand4Bit(u8 u8CommandCPY)
{
	u8 u8PortReadingLOC= DIO_u8GetPortValue(LCD_PORT);
	u8PortReadingLOC = (u8PortReadingLOC & 0x0F) | (u8CommandCPY & 0xF0); // send first 4 bits
	DIO_vidSetPortValue(LCD_PORT,u8PortReadingLOC);
	//write commend
	DIO_vidSetPinValue(LCD_CONTROL_PORT,RS,LOW);
	DIO_vidSetPinValue(LCD_CONTROL_PORT,RW,LOW);
	//pulse
	DIO_vidSetPinValue(LCD_CONTROL_PORT,E,HIGH);
	_delay_ms(1);
	DIO_vidSetPinValue(LCD_CONTROL_PORT,E,LOW);
	_delay_us(200);
	// send second four bits
	u8PortReadingLOC= DIO_u8GetPortValue(LCD_PORT);
	u8PortReadingLOC = ((u8PortReadingLOC & 0x0F) | (u8CommandCPY << 4));
	DIO_vidSetPortValue(LCD_PORT,u8PortReadingLOC);
	// pulse
	DIO_vidSetPinValue(LCD_CONTROL_PORT,E,HIGH);
	_delay_ms(1);
	DIO_vidSetPinValue(LCD_CONTROL_PORT,E,LOW);
	_delay_ms(2);

	return;
}

void LCD_vidIntialize4Bit(void)
{
    _delay_ms(50);                       //wait 50 ms
    LCD_vidSendCommand4Bit(0b00110011);
    LCD_vidSendCommand4Bit(0b00110010);
    LCD_vidSendCommand4Bit(0b00101000);        //2 line and 5*7 dot
    _delay_ms(1);                        //wait 1 ms
    LCD_vidSendCommand4Bit(0b00001100);       //display and curser
	_delay_ms(1);                        //wait 1 ms
	LCD_vidSendCommand4Bit(0b00000001);        //clear
	_delay_ms(2);                        //wait 2 ms
	LCD_vidSendCommand4Bit(0b00000110);       //entry

	return;
}

void LCD_vidSendData4Bit(u8 u8DataCPY)
{
	// send first 4 bits high nib
		u8 u8PortReadingLOC= DIO_u8GetPortValue(LCD_PORT);
		u8PortReadingLOC = (u8PortReadingLOC & 0x0F) | (u8DataCPY & 0xF0);
		DIO_vidSetPortValue(LCD_PORT,u8PortReadingLOC);
		//write data
		DIO_vidSetPinValue(LCD_CONTROL_PORT,RS,HIGH);
		DIO_vidSetPinValue(LCD_CONTROL_PORT,RW,LOW);

		 //pulse
		DIO_vidSetPinValue(LCD_CONTROL_PORT,E,HIGH);

		_delay_ms(1);
		DIO_vidSetPinValue(LCD_CONTROL_PORT,E,LOW);
		_delay_us(200);
		// send second four bits
		u8PortReadingLOC= DIO_u8GetPortValue(LCD_PORT);
		u8PortReadingLOC = (u8PortReadingLOC & 0x0F) | (u8DataCPY << 4);
		DIO_vidSetPortValue(LCD_PORT,u8PortReadingLOC);
		//write data
		DIO_vidSetPinValue(LCD_CONTROL_PORT,RS,HIGH);
		DIO_vidSetPinValue(LCD_CONTROL_PORT,RW,LOW);
		// pulse
		DIO_vidSetPinValue(LCD_CONTROL_PORT,E,HIGH);

		_delay_ms(1);
		DIO_vidSetPinValue(LCD_CONTROL_PORT,E,LOW);
		_delay_ms(2);
		return;
}

void LCD_vidClear_Display4Bit(void)
{
	LCD_vidSendCommand4Bit(0b00000001);
	return;
}

void LCD_vidReturn_home4Bit(void)
{
	LCD_vidSendCommand4Bit(0b00000010);
	return;
}

void LCD_vidSendString4Bit(u8* u8StringPtrCPY)
{
	while(*u8StringPtrCPY)
	{
		LCD_vidSendData4Bit(*u8StringPtrCPY);
		u8StringPtrCPY++;
 	}
	return;
}

void LCD_vidSendNumber4Bit(u32 u32NumberCPY)
 {
	 u32 u32CopyLOC;
	 u8 u8LenghtLOC=0 , arr[10]={0} ;
	 u8 asky[10] = {'0','1','2','3','4','5','6','7','8','9'} ;
	 s8 i;
	 u32CopyLOC=u32NumberCPY;
	 if(u32NumberCPY==0)
	 {
		 LCD_vidSendData4Bit('0');
	 }
	 else
	 {
	 while(u32CopyLOC != 0)
	 {
		 u8LenghtLOC++;
		 u32CopyLOC/=10;
	 }
	 for(i=0;i<u8LenghtLOC;i++)
	 {
		 arr[i] = u32NumberCPY % 10;
		 u32NumberCPY/=10;
	 }
	 for(i=u8LenghtLOC-1;i>=0;i--)
	 {
		 LCD_vidSendData4Bit(asky[arr[i]]);
	 }
	 }
	 return;
 }

void LCD_vidSetDisply_Cursor4Bit(u8 u8CommandCPY)
{
	LCD_vidSendCommand4Bit(u8CommandCPY);
	return;
}






#endif













