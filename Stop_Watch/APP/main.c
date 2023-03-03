/******************************************************************************
 *
 * Module: PROJECT
 *
 * File Name: MAIN.c
 *
 * Description: Source file for the AVR APP driver
 *
 * Author: Tarek Ahmed
 *
 *******************************************************************************/
#include "../mcu_config/private.h"
#include "../HAL/stop_watch.h"
void main(void)
{
	/*Interrupts Enable */
	sei()

			STOPwatch_init();

	for(;;)
	{
		STOPwatch_start();
	}
}
