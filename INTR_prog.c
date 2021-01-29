/*
 * INTR_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: AHMED ADEL
 */
//////////////////////////////////////
#include "std_types.h"
#include "utils.h"
#include "INTP_int.h"
//#include "avr/interrupt.h"


#define MCUCR  *((volatile u8*)0x55)
#define MCUCSR *((volatile u8*)0x54)
#define GICR   *((volatile u8*)0x5B)
#define GIFR   *((volatile u8*)0x5A)
#define SREG   *((volatile u8*)0x5F)


/////////////////////////////////////

// set the PIF
void INT_vidSetInterruptEvent(u8 u8InterruptNumCPY, u8 u8EventCPY)
{
	switch(u8InterruptNumCPY)
	{
	case INT_0:
		{
			switch(u8EventCPY)
			{
			case INT_FALLING_EDGE:
				{
					SETBIT(MCUCR,1);
					RESETBIT(MCUCR,0);
					break;
				}
			case INT_RISING_EDGE:
				{
					SETBIT(MCUCR,1);
					SETBIT(MCUCR,0);
	     			break;
				}
			case INT_LOW_LEVEL:
				{
					RESETBIT(MCUCR,0);
					RESETBIT(MCUCR,1);
					break;
				}
			case INT_ANY_LOGIC_CHANGE:
			    {
			    	SETBIT(MCUCR,0);
			    	RESETBIT(MCUCR,1);
					break;
				}
			default:
				{
					break;
				}
		    }
			break;
		}
	case INT_1:
		{
			switch(u8EventCPY)
			{
			case INT_FALLING_EDGE:
				{
					SETBIT(MCUCR,3);
					RESETBIT(MCUCR,2);
					break;
				}
			case INT_RISING_EDGE:
				{
					SETBIT(MCUCR,3);
					SETBIT(MCUCR,2);
		   			break;
				}
			case INT_LOW_LEVEL:
				{
					RESETBIT(MCUCR,2);
					RESETBIT(MCUCR,3);
					break;
				}
			case INT_ANY_LOGIC_CHANGE:
			    {
			    	SETBIT(MCUCR,2);
			    	RESETBIT(MCUCR,3);
					break;
				}
		    default:
				{
			    	break;
				}
		   }
		   break;
		}
	case INT_2:
		{
			switch(u8EventCPY)
			{
			case INT_FALLING_EDGE:
				{
					RESETBIT(MCUCSR,6);
					break;
				}
			case INT_RISING_EDGE:
				{
					SETBIT(MCUCSR,6);
	     			break;
				}
			default:
				{
					break;
				}
		    }
			break;
		}
	default:break;
	}
 return ;
}

// set the PIE

void INT_vidSetInterruptEnable(u8 u8InterruptNumCPY,u8 u8StateCPY)
{
	switch(u8InterruptNumCPY)
	{
	case INT_0:
		{
			switch(u8StateCPY)
			{
			case INT_ENABLE:
				{
					 SETBIT(GICR,6);
					 break;
				}
			case INT_DISABLE:
				{
					RESETBIT(GICR,6);
					break;
				}
			default:{break;}
			}
			break;
		}
	case INT_1:
		{
			switch(u8StateCPY)
			{
			case INT_ENABLE:
				{
					 SETBIT(GICR,7);
		     		 break;
				}
			case INT_DISABLE:
				{
			    	 RESETBIT(GICR,7);
	                 break;
				}
			default:{break;}
			}
			break;
		}
	case INT_2:
		{
			switch(u8StateCPY)
			{
			case INT_ENABLE:
				{
					 SETBIT(GICR,5);
		     		 break;
				}
			case INT_DISABLE:
				{
			    	 RESETBIT(GICR,5);
	                 break;
		     	}
			default:{break;}
			}
			break;
		}
	default:
		{
		    break;
		}
	}
	return;
}


// set the GIE

void INT_vidSetInterruptGeneral(u8 u8StateCPY)
{
	switch(u8StateCPY)
	{
	case INT_DISABLE:
		{
			RESETBIT(SREG,7);
			break;
		}
	case INT_ENABLE:
		{
			SETBIT(SREG,7);
			break;
		}
	default:{break;}
	}
    return;
}
