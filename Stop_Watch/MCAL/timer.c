/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.h
 *
 * Description: Source file for the Timer driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#include "timer.h"
#include "gpio.h"
#include "../mcu_config/common_macros.h"
#include "../mcu_config/private.h"
#include <avr/interrupt.h>

static volatile void (*g_callBackPtr0)(void) = NULL_PTR;
static volatile void (*g_callBackPtr1)(void) = NULL_PTR;
static volatile void (*g_callBackPtr2)(void) = NULL_PTR;


ISR(TIMER0_OVF_vect)
{

	if(g_callBackPtr0 != NULL_PTR)
	{
		(*g_callBackPtr0)();
	}

}


ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr0 != NULL_PTR)
	{
		(*g_callBackPtr0)();
	}
}



ISR(TIMER1_COMPA_vect)
{

	if(g_callBackPtr1 != NULL_PTR)
	{
		(*g_callBackPtr1)();
	}

}


ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		(*g_callBackPtr1)();
	}
}

ISR(TIMER2_OVF_vect)
{

	if(g_callBackPtr2 != NULL_PTR)
	{
		(*g_callBackPtr2)();
	}

}


ISR(TIMER2_COMP_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		(*g_callBackPtr2)();
	}
}


void Timer0_init(const Timer0_ConfigType *Config_Ptr)
{
	/* Clear All Timer1 Registers */
	TCNT0=0;
	OCR0=0;
	TCCR0=0;
	CLEAR_BIT(TIMSK,TOIE0);
	CLEAR_BIT(TIMSK,OCIE0);

	TCNT0 = Config_Ptr->initial_value;
	OCR0  = Config_Ptr->compare_value;


	TCCR0 |= (GET_BIT(Config_Ptr->mode,0)<<WGM00)
		    |(GET_BIT(Config_Ptr->mode,1)<<WGM01);

	if((Config_Ptr->mode) == NORMAL_TIMER0 )
	{
		TCCR0 |= (GET_BIT(Config_Ptr->pin_output0,0)<<COM00)
		   		|(GET_BIT(Config_Ptr->pin_output0,1)<<COM01)
				|(1<<FOC0);

		if((Config_Ptr->timer0_int) == ENABLE_INTERRUPT_TIMER0 )
		{
			SET_BIT(TIMSK,TOIE0);
		}
	}


	else if((Config_Ptr->mode) == CTC_TIMER0 )
	{
		TCCR0 |= (GET_BIT(Config_Ptr->pin_output0,0)<<COM00)
		 	   	|(GET_BIT(Config_Ptr->pin_output0,1)<<COM01)
				|(1<<FOC0);

		if((Config_Ptr->timer0_int) == ENABLE_INTERRUPT_TIMER0 )
		{
			SET_BIT(TIMSK,OCR0);
		}
	}

	else if((Config_Ptr->mode) == FAST_PWM_TIMER0 )
	{
		TCCR0 |= (GET_BIT(Config_Ptr->pin_output_PWM0,0)<<COM00)
				|(GET_BIT(Config_Ptr->pin_output_PWM0,1)<<COM01);

		if((Config_Ptr->timer0_int) == ENABLE_INTERRUPT_TIMER0 )
		{
			SET_BIT(TIMSK,OCR0);
		}
	}
	else if((Config_Ptr->mode) == PWM_PHASE_CORRECT_TIMER0 )
	{

	}

	TCCR0 =(TCCR0 & 0xF8) | ((Config_Ptr->prescaler) & 0x07);


	switch(Config_Ptr->timer0_pin)
	{
	case TIMER0_PIN_NOT_OUTPUT:
		GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_INPUT);
		break;

	case TIMER0_PIN_OUTPUT:
		GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
		GPIO_writePin(PORTB_ID, PIN3_ID, LOGIC_LOW);
		break;

	case TIMER0_PIN_OUTPUT_PULLUP:
		GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
		GPIO_writePin(PORTB_ID, PIN3_ID, LOGIC_HIGH);
		break;
	}
}



void Timer1_init(const Timer1_ConfigType *Config_Ptr)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
	CLEAR_BIT(TIMSK,TOIE1);
	CLEAR_BIT(TIMSK,OCIE1A);


	TCNT1=Config_Ptr->initial_value;

	OCR1A=Config_Ptr->compare_value; //750-2500

	ICR1=Config_Ptr->ICR1_value;

	if((Config_Ptr->mode)==NORMAL_TIMER1)
	{
		TIMSK |= (1<<TOIE1);

	}
	else if((Config_Ptr->mode)==CTC_TIMER1)
	{
		TIMSK |= (1<<OCIE1A);
	}


	if((Config_Ptr->mode)==FAST_PWM_ICR1)
	{
		TCCR1A |= (1<<COM1A1);
	}
	else
	{
		TCCR1A |= (1<<FOC1A) | (1<<FOC1B);
	}


	TCCR1A |= (GET_BIT((Config_Ptr->mode),0 ) << WGM10)
			 |(GET_BIT((Config_Ptr->mode),1 ) << WGM11);

	TCCR1B =(TCCR1B & 0xF8) | ((Config_Ptr->prescaler) & 0x07);

	TCCR1B |= (GET_BIT((Config_Ptr->mode),2 ) << WGM12)
		     |(GET_BIT((Config_Ptr->mode),3 ) << WGM13);


	switch(Config_Ptr->timer1_pin_A)
	{
	case TIMER1_PIN_NOT_OUTPUT_A:
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_INPUT);
		break;

	case TIMER1_PIN_OUTPUT_A:
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN3_ID, LOGIC_LOW);
		break;

	case TIMER1_PIN_OUTPUT_PULLUP_A:
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN5_ID, LOGIC_HIGH);
		break;
	}



	switch(Config_Ptr->timer1_pin_B)
	{
	case TIMER1_PIN_NOT_OUTPUT_B:
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_INPUT);
		break;

	case TIMER1_PIN_OUTPUT_B:
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN3_ID, LOGIC_LOW);
		break;

	case TIMER1_PIN_OUTPUT_PULLUP_B:
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN4_ID, LOGIC_HIGH);
		break;
	}
}


void Timer2_init(const Timer2_ConfigType *Config_Ptr)
{

	TCNT2=0;
	OCR2=0;
	TCCR2=0;
	CLEAR_BIT(TIMSK,TOIE2);
	CLEAR_BIT(TIMSK,OCIE2);

	TCNT2 = Config_Ptr->initial_value;
	OCR2  = Config_Ptr->compare_value;


	TCCR2 |= (GET_BIT(Config_Ptr->mode,0)<<WGM20)
		    |(GET_BIT(Config_Ptr->mode,1)<<WGM21);

	if((Config_Ptr->mode) == NORMAL_TIMER2 )
	{
		TCCR2 |= (GET_BIT(Config_Ptr->pin_output2,0)<<COM20)
		   		|(GET_BIT(Config_Ptr->pin_output2,1)<<COM21)
				|(1<<FOC2);

		if((Config_Ptr->timer2_int) == ENABLE_INTERRUPT_TIMER2 )
		{
			SET_BIT(TIMSK,TOIE2);
		}
	}


	else if((Config_Ptr->mode) == CTC_TIMER2 )
	{
		TCCR2 |= (GET_BIT(Config_Ptr->pin_output2,0)<<COM20)
		 	   	|(GET_BIT(Config_Ptr->pin_output2,1)<<COM21)
				|(1<<FOC2);

		if((Config_Ptr->timer2_int) == ENABLE_INTERRUPT_TIMER2 )
		{
			SET_BIT(TIMSK,OCR2);
		}
	}

	else if((Config_Ptr->mode) == FAST_PWM_TIMER0 )
	{
		TCCR2 |= (GET_BIT(Config_Ptr->pin_output_PWM2,0)<<COM00)
				|(GET_BIT(Config_Ptr->pin_output_PWM2,1)<<COM01);

		if((Config_Ptr->timer2_int) == ENABLE_INTERRUPT_TIMER2 )
		{
			SET_BIT(TIMSK,OCR2);
		}
	}
	else if((Config_Ptr->mode) == PWM_PHASE_CORRECT_TIMER2 )
	{

	}

	TCCR2 =(TCCR2 & 0xF8) | ((Config_Ptr->prescaler) & 0x07);


	switch(Config_Ptr->timer2_pin)
	{
	case TIMER2_PIN_NOT_OUTPUT:
		GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_INPUT);
		break;

	case TIMER2_PIN_OUTPUT:
		GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN3_ID, LOGIC_LOW);
		break;

	case TIMER2_PIN_OUTPUT_PULLUP:
		GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN7_ID, LOGIC_HIGH);
		break;
	}
}


void Timer0_deInit(void)
{
	/* Clear All Timer0 Registers */
	TCNT0=0;
	OCR0=0;
	TCCR0=0;
	CLEAR_BIT(TIMSK,TOIE0);
	CLEAR_BIT(TIMSK,OCIE0);
}


void Timer1_deInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
	CLEAR_BIT(TIMSK,TOIE1);
	CLEAR_BIT(TIMSK,OCIE1A);

}


void Timer2_deInit(void)
{
	/* Clear All Timer2 Registers */
	TCNT2=0;
	OCR2=0;
	TCCR2=0;
	TIMSK &=0x3F;
	CLEAR_BIT(TIMSK,TOIE2);
	CLEAR_BIT(TIMSK,OCIE2);
}


void Timer0_turn_off_clock(void)
{
	TCCR0 =(TCCR0 & 0xF8);
}


void Timer1_turn_off_clock(void)
{
	TCCR1B = (TCCR1B & 0xF8);
}



void Timer2_turn_off_clock(void)
{
	TCCR2 =(TCCR2 & 0xF8);
}





void Timer0_turn_on_clock(const Timer0_ConfigType *Config_Ptr)
{
	TCCR0 =(TCCR0 & 0xF8) | ((Config_Ptr->prescaler) & 0x07);
}
void Timer1_turn_on_clock(const Timer1_ConfigType *Config_Ptr)
{
	TCCR1B =(TCCR1B & 0xF8) | ((Config_Ptr->prescaler) & 0x07);
}

void Timer2_turn_on_clock(const Timer2_ConfigType *Config_Ptr)
{
	TCCR2 =(TCCR2 & 0xF8) | ((Config_Ptr->prescaler) & 0x07);
}




void TIMER0_set_OCR0(uint8 duty)
{
	Timer0_ConfigType timer0_config_ptr;

	Timer0_init(&timer0_config_ptr);
}


void TIMER1_set_OCR1A(uint16 duty)
{
	Timer1_ConfigType timer1_config_ptr={0,duty ,19999,F_CPU_8_TIMER1,FAST_PWM_ICR1};
	/* Setup the two motor pins as output pins */
	Timer1_init(&timer1_config_ptr);
}


void TIMER2_set_OCR2(uint8 duty)
{
	Timer0_ConfigType timer2_config_ptr;

	Timer0_init(&timer2_config_ptr);
}




void Timer0_setCallBack(void(*a_ptr)(void))
{

	g_callBackPtr0=a_ptr;
}

void Timer1_setCallBack(void(*a_ptr)(void))
{

	g_callBackPtr1=a_ptr;
}


void Timer2_setCallBack(void(*a_ptr)(void))
{

	g_callBackPtr2=a_ptr;
}
