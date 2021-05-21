/*
 * measure_duty_cycle.c
 *
 *  Created on: Mar 25, 2021
 *
 */

#include "lcd.h"
#include "Timer1.h"
#include "INT0.h"


volatile uint8 g_edgeCount = 0;
volatile uint16 g_timeHigh = 0;
volatile uint16 g_timePeriod = 0;
volatile uint16 g_timePeriodPlusHigh = 0;



void APP_edgeProcessing(void)
{
	g_edgeCount++;
		if(g_edgeCount == 1)
		{
			/*
			 * Clear the timer counter register to start measurements from the
			 * first detected rising edge
			 */
			Timer1_clearTimerValue();
			/* Detect falling edge */
			INT0_fallingEdge();
		}
		else if(g_edgeCount == 2)
		{
			/* Store the High time value */
			g_timeHigh = Timer1_getTime();
			/* Detect rising edge */
			INT0_risingEdge();
		}
		else if(g_edgeCount == 3)
		{
			/* Store the Period time value */
			g_timePeriod = Timer1_getTime();
			/* Detect falling edge */
			INT0_fallingEdge();
		}
		else if(g_edgeCount == 4)
		{
			/* Store the Period time value + High time value */
			g_timePeriodPlusHigh = Timer1_getTime();
			/* Clear the timer counter register to start measurements again */
			Timer1_clearTimerValue();
			/* Detect rising edge */
			INT0_risingEdge();
		}

}

int main()
{
	uint32 LowTime,PeriodTime, dutyCycle = 0;

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	/* Set the Call back function pointer in the INT0 driver */
	INT0_setCallBack(APP_edgeProcessing);

	/* Initialize the LCD, INT0 and Timer1 driver */
	LCD_init();
	INT0_init();
	Timer1_init();

	while(1)
	{
		if(g_edgeCount == 4)
		{
			INT0_DeInit(); /* Disable INT0 */
			g_edgeCount = 0;
			LCD_displayString("Duty = ");
			/* calculate the dutyCycle */
			LowTime= g_timePeriodPlusHigh-g_timePeriod;
			PeriodTime = g_timePeriodPlusHigh - g_timeHigh;
			dutyCycle = ((float)LowTime/PeriodTime) * 100;
			/* display the dutyCycle on LCD screen */
			LCD_intgerToString(dutyCycle);
			LCD_displayCharacter('%');
		}
	}
}
