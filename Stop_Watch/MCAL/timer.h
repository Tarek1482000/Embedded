/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.h
 *
 * Description: header file for the Timer driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "../mcu_config/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	DISNABLE_INTERRUPT_TIMER0,ENABLE_INTERRUPT_TIMER0
}Timer0_INTERRUPT;

typedef enum
{
	NO_CLOCK_TIMER0,
	F_CPU_CLOCK_TIMER0,
	F_CPU_8_TIMER0,
	F_CPU_64_TIMER0,
	F_CPU_256_TIMER0,
	F_CPU_1024_TIMER0,
	External_Clock_Falling_Edge_TIMER0,
	External_Clock_Rising_Edge_TIMER0
}Timer0_Prescaler;


typedef enum
{
	NORMAL_TIMER0 , PWM_PHASE_CORRECT_TIMER0 , CTC_TIMER0 ,FAST_PWM_TIMER0
}Timer0_Mode;


typedef enum
{
	NORMAL_OUT_TIMER0, TOGGLE_OUT_TIMER0, CLEAR_OUT_TIMER0, SET_OUT_TIMER0
}Timer0_Compare_Output_Mode_NON_PWM;

typedef enum
{
	NORMAL_OUT_PWM_TIMER0, REVERSED_OUT_PWM_TIMER0, NON_INVERTINGOUT_PWM_TIMER0, INVERTINGOUT_PWM_TIMER0
}Timer0_Compare_Output_Mode_FAST_PWM;


typedef enum
{
	TIMER0_PIN_NOT_OUTPUT,
	TIMER0_PIN_OUTPUT,
	TIMER0_PIN_OUTPUT_PULLUP
}Timer0_PIN;


typedef struct
{
	uint8 initial_value; // Start count from this value
	uint8 compare_value; // it will be used in compare mode only.
	Timer0_Prescaler prescaler;
	Timer0_Mode mode;
	Timer0_Compare_Output_Mode_NON_PWM pin_output0;
	Timer0_Compare_Output_Mode_FAST_PWM pin_output_PWM0;
	Timer0_INTERRUPT timer0_int;
	Timer0_PIN timer0_pin;
}Timer0_ConfigType;



typedef enum
{
	NO_CLOCK_TIMER1,
	F_CPU_CLOCK_TIMER1,
	F_CPU_8_TIMER1,
	F_CPU_64_TIMER1,
	F_CPU_256_TIMER1,
	F_CPU_1024_TIMER1,
	External_Clock_Falling_Edge_TIMER1,
	External_Clock_Rising_EdgeTIMER2
}Timer1_Prescaler;



typedef enum
{
	NORMAL_TIMER1 , CTC_TIMER1=4 ,FAST_PWM_ICR1=14
}Timer1_Mode;



typedef enum
{
	TIMER1_PIN_NOT_OUTPUT_A,
	TIMER1_PIN_OUTPUT_A,
	TIMER1_PIN_OUTPUT_PULLUP_A
}Timer1_PIN_A;


typedef enum
{
	TIMER1_PIN_NOT_OUTPUT_B,
	TIMER1_PIN_OUTPUT_B,
	TIMER1_PIN_OUTPUT_PULLUP_B
}Timer1_PIN_B;

typedef struct
{
	uint16 initial_value; // Start count from this value
	uint16 compare_value; // it will be used in compare mode only.
	uint16 ICR1_value; // it will be used in compare mode only.
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
	Timer1_PIN_A timer1_pin_A;
	Timer1_PIN_B timer1_pin_B;
}Timer1_ConfigType;



typedef enum
{
	DISNABLE_INTERRUPT_TIMER2,ENABLE_INTERRUPT_TIMER2
}Timer2_INTERRUPT;
typedef enum
{
	NO_CLOCK_TIMER2,
	F_CPU_CLOCK_TIMER2,
	F_CPU_8_TIMER2,
	F_CPU_32_TIMER2,
	F_CPU_64_TIMER2,
	F_CPU_128_TIMER2,
	F_CPU_256_TIMER2,
	F_CPU_1024_TIMER2
}Timer2_Prescaler;

typedef enum
{
	NORMAL_TIMER2 , PWM_PHASE_CORRECT_TIMER2 , CTC_TIMER2 ,FAST_PWM_TIMER2
}Timer2_Mode;



typedef enum
{
	NORMAL_OUT_TIMER2, TOGGLE_OUT_TIMER2, CLEAR_OUT_TIMER2, SET_OUT_TIMER2
}Timer2_Compare_Output_Mode_NON_PWM;

typedef enum
{
	NORMAL_OUT_PWM_TIMER2, REVERSED_OUT_PWM_TIMER2, NON_INVERTINGOUT_PWM_TIMER2, INVERTINGOUT_PWM_TIMER2
}Timer2_Compare_Output_Mode_FAST_PWM;



typedef enum
{
	TIMER2_PIN_NOT_OUTPUT,
	TIMER2_PIN_OUTPUT,
	TIMER2_PIN_OUTPUT_PULLUP
}Timer2_PIN;


typedef struct
{
	uint8 initial_value; // Start count from this value
	uint8 compare_value; // it will be used in compare mode only.
	Timer2_Prescaler prescaler;
	Timer2_Mode mode;
	Timer2_Compare_Output_Mode_NON_PWM pin_output2;
	Timer2_Compare_Output_Mode_FAST_PWM pin_output_PWM2;
	Timer2_INTERRUPT timer2_int;
	Timer2_PIN timer2_pin;
}Timer2_ConfigType;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/*
 * Setup Timer configuration
 */
void Timer0_init(const Timer0_ConfigType *Config_Ptr);
void Timer1_init(const Timer1_ConfigType *Config_Ptr);
void Timer2_init(const Timer2_ConfigType *Config_Ptr);


/*
 * Clear Timer registers
 */
void Timer0_deInit(void);
void Timer1_deInit(void);
void Timer2_deInit(void);


/*
 * Clear Timer clock
 */
void Timer0_turn_off_clock(void);
void Timer1_turn_off_clock(void);
void Timer2_turn_off_clock(void);


/*
 * Restore Timer clock
 */
void Timer0_turn_on_clock(const Timer0_ConfigType *Config_Ptr);
void Timer1_turn_on_clock(const Timer1_ConfigType *Config_Ptr);
void Timer2_turn_on_clock(const Timer2_ConfigType *Config_Ptr);


/*
 * Select Timer duty cycle
 */
void TIMER0_set_OCR0(uint8 duty);
void TIMER1_set_OCR1A(uint16 duty);
void TIMER2_set_OCR2(uint8 duty);



/*
 * Timer call back function
 */
void Timer0_setCallBack(void(*a_ptr)(void));

void Timer1_setCallBack(void(*a_ptr)(void));

void Timer2_setCallBack(void(*a_ptr)(void));


#endif /* TIMER_H_ */
