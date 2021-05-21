 /******************************************************************************
 *
 * Module: INT0
 *
 * File Name: INT0.h
 *
 * Description: Header file for the INT0 driver
 *
 *******************************************************************************/

#ifndef INT0_H_
#define INT0_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void INT0_init(void);
void INT0_fallingEdge(void);
void INT0_risingEdge(void);
void INT0_setCallBack(void(*a_ptr)(void));
void INT0_DeInit(void);
ISR(INT0_vect);


#endif /* INT0_H_ */
