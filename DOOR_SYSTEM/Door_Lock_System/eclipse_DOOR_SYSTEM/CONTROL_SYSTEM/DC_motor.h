/*
 * DC_motor.h
 *
 *  Created on: Oct 8, 2022
 *      Author: Meriam Ehab
 */

#ifndef DC_H_
#define DC_H_

#pragma once

#include "std_types.h"
#include "micro_config.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PORT_IN1             PORTB_ID
#define PORT_IN2             PORTB_ID
#define PORT_E               PORTB_ID

#define PIN_IN1              PIN0_ID
#define PIN_IN2              PIN1_ID
#define PIN_E                PIN3_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

typedef enum
{
	CW , A_CW , STOP
} DcMotor_State;

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state);

#endif  /* MOTOR_H_ */s

