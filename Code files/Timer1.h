 /******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: Timer1.h
 *
 * Description: Header file for the Timer1 driver
 *
 *******************************************************************************/


#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Timer1_init(void);
uint16 Timer1_getTime(void);
void Timer1_clearTimerValue(void);



#endif /* TIMER1_H_ */
