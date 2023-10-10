/*
 * buzzer.h
 *
 *  Created on: Oct 29, 2022
 *      Author: Meriam Ehab
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"
#include "micro_config.h"
/*******************************************************************************
 *                              Definitions                                    *
 *******************************************************************************/
/* The Ports and Pins IDs for the buzzer pin */
#define BUZZER_PORT_ID   PORTD_ID
#define BUZZER_PIN_ID    PIN6_ID


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void BUZZER_init(void);

void BUZZER_on(void);

void BUZZER_off(void);

#endif /* BUZZER_H_ */
