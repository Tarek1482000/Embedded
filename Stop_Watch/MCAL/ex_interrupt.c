/******************************************************************************
 *
 * Module: External interrupts
 *
 * File Name: ex_interrupt.c
 *
 * Description: Source file for the AVR External interrupts driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/


#include "../mcu_config/common_macros.h"
#include "../mcu_config/private.h"
#include "ex_interrupt.h"
#include <avr/interrupt.h>
#include "gpio.h"


/*
 * Initialize External Interrupts call back pointer
 */
static volatile void (*g_callBackPtr0)(void) = NULL_PTR;
static volatile void (*g_callBackPtr1)(void) = NULL_PTR;
static volatile void (*g_callBackPtr2)(void) = NULL_PTR;


/*
 * External Interrupts ISR
 */

ISR(INT0_vect)
{
	if(g_callBackPtr0 != NULL_PTR)
	{
		(*g_callBackPtr0)();
	}

}

ISR(INT1_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		(*g_callBackPtr1)();
	}

}

ISR(INT2_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		(*g_callBackPtr2)();
	}

}

void Ex_INT_init(const Ex_INT_ConfigType *Config_Ptr)
{

	switch (Config_Ptr->INT)
	{
	case EX_INT0:

		/*
		 * Setup Pin direction
		 * Enable External Interrupt 0
		 */
		GPIO_setupPinDirection(EX_INT0_PORT_ID, EX_INT0_PORT_ID, PIN_INPUT);
		SET_BIT(GICR,INT0);


		/*
		 * Select Pin state (Flow or Full up)
		 */
		if((Config_Ptr->PIN)==PULLUP_EX_INT_PIN)
		{
			GPIO_writePin(EX_INT0_PORT_ID, EX_INT0_PORT_ID, LOGIC_HIGH);
		}
		else
		{
			GPIO_writePin(EX_INT0_PORT_ID, EX_INT0_PORT_ID, LOGIC_LOW);
		}


		switch (Config_Ptr->option)
		{
		case LOW_LEVEL:
			CLEAR_BIT(MCUCR,ISC00);
			CLEAR_BIT(MCUCR,ISC01);
			break;

		case ANY_LOGICAL_CHANGE:
			SET_BIT(MCUCR,ISC00);
			CLEAR_BIT(MCUCR,ISC01);
			break;
		case FALLING_EDGE:
			SET_BIT(MCUCR,ISC01);
			CLEAR_BIT(MCUCR,ISC00);
			break;
		case RAISING_EDGE:
			SET_BIT(MCUCR,ISC01);
			SET_BIT(MCUCR,ISC00);
			break;
		}

		break;

		case EX_INT1:
			/*
			 * Setup Pin direction
			 * Enable External Interrupt 1
			 */
			GPIO_setupPinDirection(EX_INT1_PORT_ID, EX_INT1_PORT_ID, PIN_INPUT);
			SET_BIT(GICR,INT1);


			/*
			 * Select Pin state (Flow or Full up)
			 */
			if((Config_Ptr->PIN)==PULLUP_EX_INT_PIN)
			{
				GPIO_writePin(EX_INT1_PORT_ID, EX_INT1_PORT_ID, LOGIC_HIGH);
			}
			else
			{
				GPIO_writePin(EX_INT1_PORT_ID, EX_INT1_PORT_ID, LOGIC_LOW);
			}

			switch (Config_Ptr->option)
			{
			case LOW_LEVEL:
				CLEAR_BIT(MCUCR,ISC10);
				CLEAR_BIT(MCUCR,ISC11);
				break;

			case ANY_LOGICAL_CHANGE:
				SET_BIT(MCUCR,ISC10);
				CLEAR_BIT(MCUCR,ISC11);
				break;
			case FALLING_EDGE:
				SET_BIT(MCUCR,ISC11);
				CLEAR_BIT(MCUCR,ISC10);
				break;
			case RAISING_EDGE:
				SET_BIT(MCUCR,ISC10);
				SET_BIT(MCUCR,ISC11);
				break;
			}

			break;

			case EX_INT2:

				/*
				 * Setup Pin direction
				 * Enable External Interrupt 2
				 */
				GPIO_setupPinDirection(EX_INT2_PORT_ID, EX_INT2_PORT_ID, PIN_INPUT);
				SET_BIT(GICR,INT2);


				/*
				 * Select Pin state (Flow or Full up)
				 */
				if((Config_Ptr->PIN)==PULLUP_EX_INT_PIN)
				{
					GPIO_writePin(EX_INT2_PORT_ID, EX_INT2_PORT_ID, LOGIC_HIGH);
				}
				else
				{
					GPIO_writePin(EX_INT2_PORT_ID, EX_INT2_PORT_ID, LOGIC_LOW);
				}

				break;

				switch (Config_Ptr->option)
				{
				case LOW_LEVEL:
				case ANY_LOGICAL_CHANGE:

				case FALLING_EDGE:
					CLEAR_BIT(MCUCSR,ISC2);
					break;
				case RAISING_EDGE:
					SET_BIT(MCUCSR,ISC2);
					break;
				}
	}
}




/*
 * External Interrupts call back functions
 */
void INT0_setCallBack(void(*a_ptr)(void))
{

	g_callBackPtr0=a_ptr;
}


void INT1_setCallBack(void(*a_ptr)(void))
{

	g_callBackPtr1=a_ptr;
}


void INT2_setCallBack(void(*a_ptr)(void))
{

	g_callBackPtr2=a_ptr;
}
