/*
 * Timer1.c
 *
 *  Created on: Mar 25, 2021
 *
 */
#include "Timer1.h"

void Timer1_init(void)
{
	TCCR1A = (1<<FOC1A) | (1<<FOC1B); /* Normal mode*/
	TCCR1B = (1<<CS10) ; /* no prescaler */
	TCNT1 = 0; /* reseting timer value */
}

uint16 Timer1_getTime(void)
{
	return TCNT1;
}
void Timer1_clearTimerValue(void)
{
	TCNT1 = 0;
}

