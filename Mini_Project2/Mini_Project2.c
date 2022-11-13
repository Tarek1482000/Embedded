/*
 * Mini_Project2.c
 *
 *  Created on: Sep 20, 2022
 *      Author: tarek
 */
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include"INTERUPT_TIMER1.h"

void main(void)
{
	DDRC|=0X0F;// 0000 1111 first 4 pins output (decoder)
	PORTC &=0xF0;//Turn off first 4 pins at beginning (decoder)
	DDRA|=0X3F;//0011 1111  first 6 pins output (7-SEG ENABLE)
	PORTA&=0XC0;  //Turn off first 6 pins PORTA (ALL 7-SEG ENABLE)
	SREG|=(1<<7);//Enable I-Bit

	Timer1_comp();//Timer1
	INT0_Init();//Interrupt 0
	INT1_Init();//Interrupt 1
	INT2_Init();//Interrupt 2

	for(;;)
	{
			//Sec0
			PORTA=(PORTA & 0XC0)|(0X01);//Enable 7-Segment Second0 
			PORTC =(PORTC & 0XF0)|((g_count_s%10) & 0X0F) ;
			_delay_ms(1);
			//**********************************************************************************************
			//Sec1
			PORTA=(PORTA & 0XC0)|0X02;//Enable 7-Segment Second1 
			PORTC =(PORTC & 0XF0)|((g_count_s/10) & 0X0F) ;
			_delay_ms(1);
			//**********************************************************************************************
			//Min0
			PORTA=(PORTA & 0XC0)|0X04;//Enable 7-Segment Minutes0 
			PORTC =(PORTC & 0XF0)|(g_count_m%10 & 0X0F) ;
			_delay_ms(1);
			//**********************************************************************************************
			//Min1
			PORTA=(PORTA & 0XC0)|0X08;//Enable 7-Segment Minutes1 
			PORTC =(PORTC & 0XF0)|(g_count_m/10 & 0X0F) ;
			_delay_ms(1);

			//**********************************************************************************************
			//Hour0
			PORTA=(PORTA & 0XC0)|0X10;//Enable 7-Segment Hours0 
			PORTC =(PORTC & 0XF0)|(g_count_h%10 & 0X0F) ;
			_delay_ms(1);
			//**********************************************************************************************
			//Hour1
			PORTA=(PORTA & 0XC0)|0X20;//Enable 7-Segment Hours1
			PORTC =(PORTC & 0XF0)|(g_count_h/10 & 0X0F) ;
			_delay_ms(1);
	}
}



