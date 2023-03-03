/******************************************************************************
 *
 * Module: Stop Watch
 *
 * File Name: stop_watch.h
 *
 * Description: Header file for the AVR stop watch driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/
#ifndef HAL_STOP_WATCH_H_
#define HAL_STOP_WATCH_H_

#include "../mcu_config/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


#define STOP_WATCH_PORT_ID             PORTC_ID
#define STOP_WATCH_PIN0_ID             PIN0_ID
#define STOP_WATCH_PIN1_ID             PIN1_ID
#define STOP_WATCH_PIN2_ID             PIN2_ID
#define STOP_WATCH_PIN3_ID             PIN3_ID

#define STOP_WATCH_ENABLE_PORT_ID      PORTA_ID
#define STOP_WATCH_SEC0_PIN_ID         PIN0_ID
#define STOP_WATCH_SEC1_PIN_ID         PIN1_ID
#define STOP_WATCH_MIN0_PIN_ID         PIN2_ID
#define STOP_WATCH_MIN1_PIN_ID         PIN3_ID
#define STOP_WATCH_HOUR0_PIN_ID        PIN4_ID
#define STOP_WATCH_HOUR1_PIN_ID        PIN5_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/



typedef enum
{
	SEC0  = 0X01,
	SEC1  = 0X02,
	MIN0  = 0X04,
	MIN1  = 0X08,
	HOUR0 = 0X10,
	HOUR1 = 0X20
}SEVEN_Segment;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Setup the direction of the required pin input/output.
 */
void STOPwatch_pins_setup(void);


/*
 * Description :
 * Setup the direction of the required pin input/output.
 * Setup External Interrupts and Timer and set their call back functions
 */
void STOPwatch_init(void);


/*
 * Description :
 * Start displaying the time on the seven segments
 */
void STOPwatch_start(void);


/*
 * Description :
 * Start the counters of the time
 */
void STOPwatch_counter(void);

/*
 * Description :
 * Reset the counters of time
 */
void STOPwatch_Reset(void);

/*
 * Description :
 * Pause the time
 */
void STOPwatch_Pause(void);

/*
 * Description :
 * Resume the time
 */
void STOPwatch_Resume(void);

/*
 * Description :
 * Select the seven segment to display the time on it
 */
void STOPwatch_enable_seven_segment(SEVEN_Segment sev_seg);


#endif /* HAL_STOP_WATCH_H_ */
