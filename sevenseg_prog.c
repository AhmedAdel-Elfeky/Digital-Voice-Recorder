/*
 * _7seg_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: AHMED ADEL
 */
#include "std_types.h"
#include "DIO_int.h"
#include "sevenseg_int.h"

#define ALL_OUTPUT 255

#if SEVENSEG_MODE == SEVENSEG_COM_CATHODE

void SEVENSEG_vidDisplay(u8 u8DataPortCPY,u8 u8NumCPY)
{

	switch(u8NumCPY)
	{

	case 0:
	{
		DIO_vidWriteChannnelGroup(u8DataPortCPY,1,0xfe,0x7e);
		break;
	}
	case 1:
	{
		DIO_vidWriteChannnelGroup(u8DataPortCPY,1,0xfe,0x30);
		break;
	}
	case 2:
	{
		DIO_vidWriteChannnelGroup(u8DataPortCPY,1,0xfe,0x6d);
		break;
	}
	case 3:
	{
		DIO_vidWriteChannnelGroup(u8DataPortCPY,1,0xfe,0x79);
		break;
	}
	case 4:
	{
		DIO_vidWriteChannnelGroup(u8DataPortCPY,1,0xfe,0x33);
		break;
	}
	case 5:
	{
		DIO_vidWriteChannnelGroup(u8DataPortCPY,1,0xfe,0x5b);
		break;
	}
	case 6:
	{
		DIO_vidWriteChannnelGroup(u8DataPortCPY,1,0xfe,0x5f);
		break;
	}
	case 7:
	{
		DIO_vidWriteChannnelGroup(u8DataPortCPY,1,0xfe,0x70);
		break;
	}case 8:
	{
		DIO_vidWriteChannnelGroup(u8DataPortCPY,1,0xfe,0xff);
		break;
	}
	case 9:
	{
		DIO_vidWriteChannnelGroup(u8DataPortCPY,1,0xfe,0x7b);
		break;
	}

	default:break;
	}
}

void SEVENSEG_vidDisplayOff(void)
{
	DIO_vidWriteChannnelGroup(SEVENSEG_PORT,1,0xfe,0x00);
	return;
}

#else
void SEVENSEG_vidDisplay7 (u8 u8DataPortCPY,u8 u8NumCPY )
{
    DIO_vidSetPortValue(u8DataPortCPY,ALL_OUTPUT);
    switch(u8NumCPY)
    {
        case 0:
        {
        	DIO_vidSetPortValue(u8DataPortCPY,0b0100000 );
        	break;
        }
        case 1:
        {
        	DIO_vidSetPortValue(u8DataPortCPY,0b1111001 );
        	break;
        }
        case 2:
        {
            DIO_vidSetPortValue(u8DataPortCPY,0b1000100 );
            break;
        }
        case 3:
        {
            DIO_vidSetPortValue(u8DataPortCPY,0b1010000 );
            break;

        }
        case 4:
        {
            DIO_vidSetPortValue(u8DataPortCPY,0b0011001 );
            break;
        }
        case 5:
        {
            DIO_vidSetPortValue(u8DataPortCPY,0b0010010 );
            break;
        }
        case 6:
        {
            DIO_vidSetPortValue(u8DataPortCPY,0b0000010 );
            break;

        }
        case 7:
        {
            DIO_vidSetPortValue(u8DataPortCPY,0b1111000 );
            break;

        }
        case 8:
        {
            DIO_vidSetPortValue(u8DataPortCPY,0b0000000 );
            break;

        }
        case 9:
        {
            DIO_vidSetPortValue(u8DataPortCPY,0b0010000 );
            break;

        }
        default:
        {
            DIO_vidSetPortValue(u8DataPortCPY,ALL_OUTPUT );

        }
     }
    return;
}

#endif


