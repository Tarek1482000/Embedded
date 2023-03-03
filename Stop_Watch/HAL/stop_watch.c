/******************************************************************************
 *
 * Module: Stop Watch
 *
 * File Name: stop_watch.c
 *
 * Description: Source file for the AVR stop watch driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/
#include "../MCAL/ex_interrupt.h"
#include "../MCAL/timer.h"
#include "../MCAL/gpio.h"
#include "stop_watch.h"
#include <util/delay.h>

/*
 * stop watch counters
 */

uint8
g_counter_sec=0,

g_counter_min=0,

g_counter_hour=0;


/*
 * External Interrupts configuration
 */
Ex_INT_ConfigType
Ex_INT0_Config_Ptr = {EX_INT0, FALLING_EDGE, NORMAL_EX_INT_PIN},
Ex_INT1_Config_Ptr = {EX_INT1, RAISING_EDGE, NORMAL_EX_INT_PIN},
Ex_INT2_Config_Ptr = {EX_INT2, FALLING_EDGE, NORMAL_EX_INT_PIN};


/*
 * Timer1 configuration
 */
Timer1_ConfigType Timer1_Config_Ptr1 = {0 ,1000 ,0 ,F_CPU_1024_TIMER1, CTC_TIMER1,TIMER1_PIN_OUTPUT_PULLUP_A,TIMER1_PIN_OUTPUT_PULLUP_B};




void STOPwatch_init(void)
{

	STOPwatch_pins_setup();

	Timer1_init(&Timer1_Config_Ptr1);

	Timer1_setCallBack(STOPwatch_counter);

	Ex_INT_init(&Ex_INT0_Config_Ptr);
	INT0_setCallBack(STOPwatch_Reset);

	Ex_INT_init(&Ex_INT1_Config_Ptr);
	INT1_setCallBack(STOPwatch_Pause);

	Ex_INT_init(&Ex_INT2_Config_Ptr);
	INT2_setCallBack(STOPwatch_Resume);
}


void STOPwatch_start(void)
{
	STOPwatch_enable_seven_segment(SEC0);
	GPIO_writePort(STOP_WATCH_PORT_ID, (g_counter_sec % 10) & 0x0F);
	_delay_ms(1);

	STOPwatch_enable_seven_segment(SEC1);
	GPIO_writePort(STOP_WATCH_PORT_ID, (g_counter_sec / 10) & 0x0F);
	_delay_ms(1);


	STOPwatch_enable_seven_segment(MIN0);
	GPIO_writePort(STOP_WATCH_PORT_ID, (g_counter_min % 10) & 0x0F);
	_delay_ms(1);

	STOPwatch_enable_seven_segment(MIN1);
	GPIO_writePort(STOP_WATCH_PORT_ID, (g_counter_min / 10) & 0x0F);
	_delay_ms(1);

	STOPwatch_enable_seven_segment(HOUR0);
	GPIO_writePort(STOP_WATCH_PORT_ID, (g_counter_hour % 10) & 0x0F);
	_delay_ms(1);

	STOPwatch_enable_seven_segment(HOUR1);
	GPIO_writePort(STOP_WATCH_PORT_ID, (g_counter_hour / 10) & 0x0F);
	_delay_ms(1);
}








void STOPwatch_pins_setup(void)
{	/*
 * setup decoder pins
 */
	GPIO_setupPinDirection(STOP_WATCH_PORT_ID, STOP_WATCH_PIN0_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(STOP_WATCH_PORT_ID, STOP_WATCH_PIN1_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(STOP_WATCH_PORT_ID, STOP_WATCH_PIN2_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(STOP_WATCH_PORT_ID, STOP_WATCH_PIN3_ID, PIN_OUTPUT);

	GPIO_writePin(STOP_WATCH_PORT_ID, STOP_WATCH_PIN0_ID, LOGIC_LOW);
	GPIO_writePin(STOP_WATCH_PORT_ID, STOP_WATCH_PIN1_ID, LOGIC_LOW);
	GPIO_writePin(STOP_WATCH_PORT_ID, STOP_WATCH_PIN2_ID, LOGIC_LOW);
	GPIO_writePin(STOP_WATCH_PORT_ID, STOP_WATCH_PIN3_ID, LOGIC_LOW);

	/*
	 * setup 7_segments enable pins
	 */
	GPIO_setupPinDirection(STOP_WATCH_ENABLE_PORT_ID, STOP_WATCH_SEC0_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(STOP_WATCH_ENABLE_PORT_ID, STOP_WATCH_SEC1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(STOP_WATCH_ENABLE_PORT_ID, STOP_WATCH_MIN0_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(STOP_WATCH_ENABLE_PORT_ID, STOP_WATCH_MIN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(STOP_WATCH_ENABLE_PORT_ID, STOP_WATCH_HOUR0_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(STOP_WATCH_ENABLE_PORT_ID, STOP_WATCH_HOUR1_PIN_ID, PIN_OUTPUT);

	GPIO_writePin(STOP_WATCH_ENABLE_PORT_ID, STOP_WATCH_SEC0_PIN_ID, LOGIC_LOW);
	GPIO_writePin(STOP_WATCH_ENABLE_PORT_ID, STOP_WATCH_SEC1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(STOP_WATCH_ENABLE_PORT_ID, STOP_WATCH_MIN0_PIN_ID, LOGIC_LOW);
	GPIO_writePin(STOP_WATCH_ENABLE_PORT_ID, STOP_WATCH_MIN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(STOP_WATCH_ENABLE_PORT_ID, STOP_WATCH_HOUR0_PIN_ID, LOGIC_LOW);
	GPIO_writePin(STOP_WATCH_ENABLE_PORT_ID, STOP_WATCH_HOUR1_PIN_ID, LOGIC_LOW);
}








void STOPwatch_Reset(void)
{
	g_counter_sec=0;

	g_counter_min=0;

	g_counter_hour=0;

	Timer1_turn_on_clock(&Timer1_Config_Ptr1);
}



void STOPwatch_Pause(void)
{
	Timer1_turn_off_clock();
}




void STOPwatch_Resume(void)
{
	Timer1_turn_on_clock(&Timer1_Config_Ptr1);
}



void STOPwatch_counter(void)
{
	g_counter_sec++;

	if(60 == g_counter_sec)
	{
		g_counter_sec = 0;
		g_counter_min++;
	}

	if(60 == g_counter_min)
	{
		g_counter_sec=0;
		g_counter_min=0;
		g_counter_hour++;
	}

	if(24 == g_counter_hour)
	{
		g_counter_sec=0;
		g_counter_min=0;
		g_counter_hour=0;
	}

}


void STOPwatch_enable_seven_segment(SEVEN_Segment sev_seg)
{
	switch(sev_seg)
	{
	case SEC0:
		GPIO_writePort(STOP_WATCH_ENABLE_PORT_ID, SEC0 & 0x3F);
		break;
	case SEC1:
		GPIO_writePort(STOP_WATCH_ENABLE_PORT_ID, SEC1 & 0x3F);
		break;
	case MIN0:
		GPIO_writePort(STOP_WATCH_ENABLE_PORT_ID, MIN0 & 0x3F);
		break;
	case MIN1:
		GPIO_writePort(STOP_WATCH_ENABLE_PORT_ID, MIN1 & 0x3F);
		break;
	case HOUR0:
		GPIO_writePort(STOP_WATCH_ENABLE_PORT_ID, HOUR0 & 0x3F);
		break;
	case HOUR1:
		GPIO_writePort(STOP_WATCH_ENABLE_PORT_ID, HOUR1 & 0x3F);
		break;
	}
}

