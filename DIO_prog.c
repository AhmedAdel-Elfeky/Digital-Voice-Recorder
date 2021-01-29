
#include "std_types.h"
#include "AVR_DIOReg.h"
#include "DIO_int.h"



void DIO_vidSetPortDirection(u8 u8PortCPY , u8 u8DirectionCPY)
{
	switch (u8PortCPY)
	{
		case PORT_A:
		{
			DDRA_REG=u8DirectionCPY;
			break;
		}
		case PORT_B:
		{
			DDRB_REG=u8DirectionCPY;
			break;
		}
		case PORT_C:
		{
			DDRC_REG=u8DirectionCPY;
			break;
		}
		case PORT_D:
		{
			DDRD_REG = u8DirectionCPY;
			break;
		}
		default :break;
     }
}

void DIO_vidSetPortValue(u8 u8PortCPY , u8 u8ValueCPY)
{
	switch (u8PortCPY)
		{
			case PORT_A:
			{
				PORTA_REG=u8ValueCPY;
				break;
			}
			case PORT_B:
			{
				PORTB_REG=u8ValueCPY;
				break;
			}
			case PORT_C:
			{
				PORTC_REG=u8ValueCPY;
				break;
			}
			case PORT_D:
			{
				PORTD_REG=u8ValueCPY;
				break;
			}
			default :break;
	     }
}

u8 DIO_u8GetPortValue(u8 u8PortCPY)
{
	u8 u8PinRegLOC;

	switch (u8PortCPY)
		{
			case PORT_A:
			{
				u8PinRegLOC= PINA_REG;
				break;
			}
			case PORT_B:
			{
				u8PinRegLOC= PINB_REG;
				break;
			}
			case PORT_C:
			{
				u8PinRegLOC= PINC_REG;
				break;
			}
			case PORT_D:
			{
				u8PinRegLOC= PIND_REG;
				break;
			}
			default :break;
		}
	return u8PinRegLOC;
}

void DIO_vidSetPinDirection(u8 u8PortCPY,u8 u8PinCPY,u8 u8DirectionCPY)
{
	switch(u8PortCPY)
	{
	case PORT_A:
		{
			switch(u8DirectionCPY)
			{
			case OUTPUT:
			{
				(DDRA_REG)|=(1<<(u8PinCPY));
				break;
			}
			case INPUT:
			{
				(DDRA_REG)&=~(1<<(u8PinCPY));
				break;
			}default:break;
			}
			break;
		}
	case PORT_B:
		{
			switch(u8DirectionCPY)
			{
			case OUTPUT:
			{
				(DDRB_REG)|=(1<<(u8PinCPY));
				break;
			}
			case INPUT:
			{
				(DDRB_REG)&=~(1<<(u8PinCPY));
				break;
			}default:break;
			}
			break;
		}
	case PORT_C:
		{
			switch(u8DirectionCPY)
			{
			case OUTPUT:
			{
				(DDRC_REG)|=(1<<(u8PinCPY));
				break;
			}
			case INPUT:
			{
				(DDRC_REG)&=~(1<<(u8PinCPY));
				break;
			}default:break;
			}
			break;
		}
	case PORT_D:
		{
			switch(u8DirectionCPY)
			{
			case OUTPUT:
			{
				(DDRD_REG)|=(1<<(u8PinCPY));
				break;
			}
			case INPUT:
			{
				(DDRD_REG)&=~(1<<(u8PinCPY));
				break;
			}default:break;
			}
			break;
		}
	default :break;
	}
}

void DIO_vidSetPinValue(u8 u8PortCPY,u8 u8PinCPY,u8 u8ValueCPY)
{
	switch(u8PortCPY)
	{
	case PORT_A:
	{
		switch(u8ValueCPY)
		{
		case HIGH:
		{
			(PORTA_REG)|=(1<<(u8PinCPY));
			break;
		}
		case LOW :
		{
			(PORTA_REG)&=~(1<<(u8PinCPY));
			break;
		}
		default:break;
		}
		break;
	}
	case PORT_B:
	{
		switch(u8ValueCPY)
		{
		case HIGH:
		{
			(PORTB_REG)|=(1<<(u8PinCPY));
			break;
		}
		case LOW :
		{
			(PORTB_REG)&=~(1<<(u8PinCPY));
			break;
		}
		default:break;
		}
		break;
	}
	case PORT_C:
	{
		switch(u8ValueCPY)
		{
		case HIGH:
		{
			(PORTC_REG)|=(1<<(u8PinCPY));
			break;
		}
		case LOW :
		{
			(PORTC_REG)&=~(1<<(u8PinCPY));
			break;
		}
		default:break;
		}
		break;
	}
	case PORT_D:
	{
		switch(u8ValueCPY)
		{
		case HIGH:
		{
			(PORTD_REG)|=(1<<(u8PinCPY));
			break;
		}
		case LOW :
		{
			(PORTD_REG)&=~(1<<(u8PinCPY));
			break;
		}
		default:break;
		}
		break;
	}
	default :
			break;
	}
}



u8 DIO_u8GetPinValue(u8 u8PortCPY,u8 u8PinCPY)
{
	u8 u8GetPinLOC;
	switch(u8PortCPY)
	{
	case PORT_A:
	{
		u8GetPinLOC=((PINA_REG&(1<<u8PinCPY))>>u8PinCPY);
		break;
	}
	case PORT_B:
    {
    	 u8GetPinLOC=((PINB_REG&(1<<u8PinCPY))>>u8PinCPY);
	     break;
	}
	case PORT_C:
	{
	   	 u8GetPinLOC=((PINC_REG&(1<<u8PinCPY))>>u8PinCPY);
	     break;
	}
	case PORT_D:
	{
	     u8GetPinLOC=((PIND_REG&(1<<u8PinCPY))>>u8PinCPY);
	     break;
	}
	default :break;

	}

	return u8GetPinLOC;
}


void DIO_vidWriteChannnelGroup(u8 PortIdLOC,u8 OffsetLOC , u8 MaskLOC,u8 Level)
{
		u8 *PortPtr ;
		switch(PortIdLOC)
		{
		case PORT_A :
		{
			PortPtr = (u8 *)(&PORTA_REG);
			break;
		}
		case PORT_B :
		{
			PortPtr = (u8 *)(&PORTB_REG);
			break;
		}
		case PORT_C :
		{
			PortPtr = (u8 *)(&PORTC_REG);
			break;
		}
		case PORT_D :
		{
			PortPtr = (u8 *)(&PORTD_REG);
			break;
		}
		default:break;
		}

		(*PortPtr) = ((*PortPtr)&(~(MaskLOC)))|(Level<<OffsetLOC);

}

void DIO_vidWriteDirectionGroup(u8 PortIdLOC,u8 OffsetLOC , u8 MaskLOC,u8 Direction)
{
	u8 *PortPtr;
	switch(PortIdLOC)
	{
	case PORT_A :
	{
		PortPtr = (u8 *)(&DDRA_REG);
		break;
	}
	case PORT_B :
	{
		PortPtr = (u8 *)(&DDRB_REG);
		break;
	}
	case PORT_C :
	{
		PortPtr = (u8 *)(&DDRC_REG);
		break;
	}
	case PORT_D :
	{
		PortPtr = (u8 *)(&DDRD_REG);
		break;
	}
	default:break;
	}
	(*PortPtr) = ((*PortPtr)&(~(MaskLOC)))|(Direction<<OffsetLOC);
}
