/*
 * INT0.c
 *
 *  Created on: Mar 25, 2021
 *
 */

#include "INT0.h"

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

void INT0_init(void)
{
	DDRD &= ~(1<<PD2); /* PD2 Input pin*/
	GICR |= (1<<INT0) ; /* enable INT0 interrupt*/
	MCUCR |= (1<<ISC00) ;
	MCUCR |= (1<<ISC01) ; /* interrupt triggered at rising edge*/
}

ISR(INT0_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		g_callBackPtr();
	}
}

void INT0_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}


void INT0_fallingEdge(void)
{
	MCUCR &= ~(1<<ISC00) ;
	MCUCR |= (1<<ISC01) ; /* interrupt triggered at Falling edge*/
}
void INT0_risingEdge(void)
{
	MCUCR |= (1<<ISC00) ;
	MCUCR |= (1<<ISC01) ; /* interrupt triggered at rising edge*/
}

void INT0_DeInit(void)
{
	GICR &= ~(1<<INT0) ; /* disable INT0 interrupt*/
}
