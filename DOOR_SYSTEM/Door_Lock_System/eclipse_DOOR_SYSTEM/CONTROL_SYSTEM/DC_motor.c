/*
 * DC_motor.c
 *
 *  Created on: Oct 8, 2022
 *      Author: Meriam Ehab
 */

#include "avr/io.h"
#include "common_macros.h"
#include "DC_motor.h"
#include "gpio.h"

void DcMotor_Init(void)
{
	GPIO_setupPinDirection(PORT_IN1, PIN_IN1, PIN_OUTPUT);
	GPIO_setupPinDirection(PORT_IN2, PIN_IN2, PIN_OUTPUT);
	GPIO_setupPinDirection(PORT_E, PIN_E, PIN_OUTPUT);

	GPIO_writePin(PORT_IN1, PIN_IN1, LOGIC_LOW);
	GPIO_writePin(PORT_IN2, PIN_IN2, LOGIC_LOW);
    /* Motor is stop at the beginning */

}

void DcMotor_Rotate(DcMotor_State state)
{
	switch (state)
	{
	case CW:
	{
		GPIO_writePin(PORT_IN1, PIN_IN1, LOGIC_HIGH);
		GPIO_writePin(PORT_IN2, PIN_IN2, LOGIC_LOW);
		break;
	}
	case A_CW:
	{
		GPIO_writePin(PORT_IN1, PIN_IN1, LOGIC_LOW);
		GPIO_writePin(PORT_IN2, PIN_IN2, LOGIC_HIGH);
		break;
	}
	case STOP:
	{
		GPIO_writePin(PORT_IN1, PIN_IN1, LOGIC_LOW);
		GPIO_writePin(PORT_IN2, PIN_IN2, LOGIC_LOW);
		break;
	}

	}

}



