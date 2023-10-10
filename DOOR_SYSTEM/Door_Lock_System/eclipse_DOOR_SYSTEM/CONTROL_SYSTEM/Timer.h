/*
 * Timer.h
 *
 *  Created on: Oct 29, 2022
 *      Author: Meriam Ehab
 */

#ifndef Timer_H_
#define Timer_H_

#include "std_types.h"

/* So7aby ely a5ado m3ak el sana ely fatet 2loly ht7tremny lw 3mla timer driver 7lw */
/*eh ra2yak :) */

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	TIMER_0, TIMER_1, TIMER_2
}Timer_ID;

typedef enum
{
	NO_CHANNEL, CHANNEL_A, CHANNEL_B
}Channel_ID;

typedef enum
{
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
}Timer_prescaler;

typedef enum
{
	OVERFLOW, COMPARE
}Timer_mood;

typedef struct
{
	Timer_ID timer;
	Channel_ID 	channel;
	Timer_mood mode;
	Timer_prescaler prescaler;
	uint8 initialValue;
	uint16 compareValue;

}TIMER_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description: Function to initialize TIMER0 driver
 * 1. Set the required clock.
 * 2. Set the required mood.
 * 3. and the required initial and compare value (in case of compare mode).
 */
void TIMER_init(TIMER_ConfigType * Config_Ptr);

/*
 * Function to set the Call Back function address.
 */
void TIMER0_setCallBack(void(*ptr)(void));
void TIMER1_setCallBack(void(*ptr)(void));
void TIMER2_setCallBack(void(*ptr)(void));


void TIMER_DeInit(void);

#endif /* TIMER0_H_ */
