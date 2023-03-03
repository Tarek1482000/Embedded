/******************************************************************************
 *
 * Module: External interrupts
 *
 * File Name: ex_interrupt.h
 *
 * Description: Header file for the AVR External interrupts driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/
#ifndef MCAL_EX_INTERRUPT_H_
#define MCAL_EX_INTERRUPT_H_


#include "../mcu_config/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define    EX_INT0_PORT_ID    PORTD_ID
#define    EX_INT0_PIN_ID     PIN2_ID

#define    EX_INT1_PORT_ID    PORTD_ID
#define    EX_INT1_PIN_ID     PIN3_ID


#define    EX_INT2_PORT_ID    PORTB_ID
#define    EX_INT2_PIN_ID     PIN2_ID



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	EX_INT0, EX_INT1, EX_INT2
}Ex_INT_SELECT;

typedef enum
{
	LOW_LEVEL, ANY_LOGICAL_CHANGE , FALLING_EDGE ,RAISING_EDGE
}Ex_INT_Sense_Control;

typedef enum
{
	NORMAL_EX_INT_PIN,PULLUP_EX_INT_PIN
}EX_INT_PIN;



typedef struct
{
	Ex_INT_SELECT INT;
	Ex_INT_Sense_Control option;
	EX_INT_PIN PIN;
}Ex_INT_ConfigType;



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/*
 * Select an External Interrupt and setup it's configuration
 */
void Ex_INT_init(const Ex_INT_ConfigType *Config_Ptr);



/*
 * External Interrupt 0 call back function
 */
void INT0_setCallBack(void(*a_ptr)(void));



/*
 * External Interrupt 1 call back function
 */
void INT1_setCallBack(void(*a_ptr)(void));



/*
 * External Interrupt 2 call back function
 */
void INT2_setCallBack(void(*a_ptr)(void));


#endif /* MCAL_EX_INTERRUPT_H_ */
