/*
 * INTERUPT_TIMER1.h
 *
 *  Created on: Sep 20, 2022
 *      Author: tarek
 */

#ifndef INTERUPT_TIMER1_h_
#define INTERUPT_TIMER1_h_

unsigned char g_count_s=0;//Seconds counter
unsigned char g_count_m=0;//Minutes counter
unsigned char g_count_h=0;//Hours counter

ISR(TIMER1_COMPA_vect)//Timer1 task
{
	//Set time counters
	g_count_s++;
	if(59==g_count_s)//Seconds
	{
		g_count_s=0;
		g_count_m++;
	}


	if(59==g_count_m)//Minutes
	{
		g_count_m=0;
		g_count_h++;
	}


	if(24==g_count_h)//Hours
	{
		g_count_s=0;
		g_count_m=0;
		g_count_h=0;
	}
}



ISR(INT0_vect)//Interrupt0 task(Reset)
{
	g_count_s=0;
	g_count_m=0;
	g_count_h=0;
}


ISR(INT1_vect)//Interrupt1 task(Pause)
{
	//Not right
	TCCR1A=0;
	TCCR1B=0;
}



ISR(INT2_vect)//Interrupt2 task(Continue)
{
	TCCR1A|=(1<<FOC1A)|(1<<FOC1A);//Non PWM
	TCCR1B|=(1<<WGM12) |(1<<CS10) |(1<<CS12);//MODE:CTC  N=1024
}


void Timer1_comp(void)//Timer1 Driver
{
	TCNT1=0;//Initial start
	OCR1A=1000;//COMARE VAULE
	TIMSK|=(1<<OCIE1A);//COMPARE
	TCCR1A|=(1<<FOC1A)|(1<<FOC1A);//Non PWM
	TCCR1B|=(1<<WGM12) |(1<<CS10) |(1<<CS12);//MODE:CTC  N=1024
}


void INT0_Init(void)//Interrupt0 Driver
{
	MCUCR|=(1<<ISC01);//Falling edge
	DDRD&=0XFB;//1111 1011 PIN PD2
	GICR|=(1<<INT0);
}


void INT1_Init(void)//Interrupt1 Driver
{
	MCUCR|=(1<<ISC10) |(1<<ISC11);//Raising edge
	DDRD&=0XF7;//1111 0111 PIN PD3
	GICR|=(1<<INT1);
}

void INT2_Init(void)//Interrupt2 Enable
{
	DDRB&=0XFB;//1111 1011 PIN PB2
	GICR|=(1<<INT2);
}

#endif /* INTERUPT_TIMER1_h_ */
