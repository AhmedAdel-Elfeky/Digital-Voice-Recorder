/*
 * SRAM_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: AHMED ADEL
 */
#include "utils.h"
#include "std_types.h"
#include "SRAM_init.h"
#include "DIO_int.h"

u16 Address = 0;

u16 SRAM_u16WriteData(u8 u8DataCPY)
{
	/* I/O High impedance */
	DIO_vidSetPinValue(WE_CTR_PORT,WE_CTR_PIN,HIGH);
	DIO_vidSetPinValue(OE_CTR_PORT,OE_CTR_PIN,HIGH);
	/* set value of  address on port address */
	DIO_vidSetPortValue(LOW_BYTE_ADDRESS_PORT,(Address&0x00ff));
	DIO_vidWriteChannnelGroup(LOW_NIBBLE_ADDRESS_PORT,4,0x70,((Address&0x0700)>>8));
	DIO_vidWriteChannnelGroup(HIGH_NIBBLE_ADDRESS_PORT,3,0xf8,((Address&0xf800)>>11));
	/* set data to port data*/
	DIO_vidSetPortValue(SRAM_DATA_PORT,u8DataCPY);
	/* write data instruction*/
	DIO_vidSetPinValue(WE_CTR_PORT,WE_CTR_PIN,LOW);
	/* I/O High impedance */
	DIO_vidSetPinValue(WE_CTR_PORT,WE_CTR_PIN,HIGH);
	DIO_vidSetPinValue(OE_CTR_PORT,OE_CTR_PIN,HIGH);
	/* go to the next address */

	Address++;

	return Address ;
}

u16 SRAM_u16WriteByteData(u16 u16AdressCPY,u8 u8DataCPY)
{
	/* I/O High impedance */
	DIO_vidSetPinValue(WE_CTR_PORT,WE_CTR_PIN,HIGH);
	DIO_vidSetPinValue(OE_CTR_PORT,OE_CTR_PIN,HIGH);
	/* set value of  address on port address */
	DIO_vidSetPortValue(LOW_BYTE_ADDRESS_PORT,(u16AdressCPY&0x00ff));
	DIO_vidWriteChannnelGroup(LOW_NIBBLE_ADDRESS_PORT,4,0x70,((u16AdressCPY&0x0700)>>8));
	DIO_vidWriteChannnelGroup(HIGH_NIBBLE_ADDRESS_PORT,3,0xf8,((u16AdressCPY&0xf800)>>11));
	/* set data to port data*/
	DIO_vidSetPortValue(SRAM_DATA_PORT,u8DataCPY);
	/* write data instruction*/
	DIO_vidSetPinValue(WE_CTR_PORT,WE_CTR_PIN,LOW);
	/* I/O High impedance */
	DIO_vidSetPinValue(WE_CTR_PORT,WE_CTR_PIN,HIGH);
	DIO_vidSetPinValue(OE_CTR_PORT,OE_CTR_PIN,HIGH);
	/* go to the next address */
	return u16AdressCPY;
}

u8 SRAM_u8ReadData(void)
{
	u8 u8DataCPY;

	/* set value of  address on port address */
	DIO_vidSetPortValue(LOW_BYTE_ADDRESS_PORT,(Address&0x00ff));
	DIO_vidWriteChannnelGroup(LOW_NIBBLE_ADDRESS_PORT,4,0x70,((Address&0x0700)>>8));
	DIO_vidWriteChannnelGroup(HIGH_NIBBLE_ADDRESS_PORT,3,0xf8,((Address&0xf800)>>11));

	/* read instruction */
	DIO_vidSetPinValue(WE_CTR_PORT,WE_CTR_PIN,HIGH);
	DIO_vidSetPinValue(OE_CTR_PORT,OE_CTR_PIN,LOW);

	/* put data */
	u8DataCPY = DIO_u8GetPortValue(SRAM_DATA_PORT);

	/* I/O High impedance */
	DIO_vidSetPinValue(WE_CTR_PORT,WE_CTR_PIN,HIGH);
	DIO_vidSetPinValue(OE_CTR_PORT,OE_CTR_PIN,HIGH);

	Address++;

	return u8DataCPY;
}

u8 SRAM_u8ReadByteData(u16 u16AdressCPY)
{
	u8 u8DataCPY;

	/* set value of  address on port address */
	DIO_vidSetPortValue(LOW_BYTE_ADDRESS_PORT,(u16AdressCPY&0x00ff));
	DIO_vidWriteChannnelGroup(LOW_NIBBLE_ADDRESS_PORT,4,0x70,((u16AdressCPY&0x0700)>>8));
	DIO_vidWriteChannnelGroup(HIGH_NIBBLE_ADDRESS_PORT,3,0xf8,((u16AdressCPY&0xf800)>>11));

	/* read instruction */
	DIO_vidSetPinValue(WE_CTR_PORT,WE_CTR_PIN,HIGH);
	DIO_vidSetPinValue(OE_CTR_PORT,OE_CTR_PIN,LOW);

	/* put data */
	u8DataCPY = DIO_u8GetPortValue(SRAM_DATA_PORT);

	/* I/O High impedance */
	DIO_vidSetPinValue(WE_CTR_PORT,WE_CTR_PIN,HIGH);
	DIO_vidSetPinValue(OE_CTR_PORT,OE_CTR_PIN,HIGH);
	return u8DataCPY;
}
