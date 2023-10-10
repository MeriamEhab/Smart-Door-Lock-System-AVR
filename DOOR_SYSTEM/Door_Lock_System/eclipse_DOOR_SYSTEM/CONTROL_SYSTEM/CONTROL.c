/*
 * CONTROL.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Meriam Ehab
 */

#include "micro_config.h"
#include "control.h"
#include "std_types.h"
#include "buzzer.h"
#include "DC_motor.h"
#include "uart.h"
#include "twi.h"
#include "external_eeprom.h"
#include "Timer.h"
#include <util/delay.h>


uint8 key = 0;
uint8 counter = 0;
uint8 matching = 0;

uint8 pass[PASSWORD_SIZE]={0};
uint8 confirm[PASSWORD_SIZE]={0};

uint8 eeprom_match = 0;
uint8 passEEPROM[PASSWORD_SIZE] = {0};
uint8 confirmEEPROM = 0;

uint8 option = 0;
uint8 check_pass[PASSWORD_SIZE]={0};
volatile uint8 motor_time = 0;
uint8 pass_error = 0;

int main(void)
{

	/*********	Timer1_Configuration structure	*********/
	TIMER_ConfigType TIMER_Config = {TIMER_1, CHANNEL_A, COMPARE, F_CPU_1024, 0, 8000};

	/*********	UART_Configuration structure	*********/
	UART_ConfigTypes UART_Config = {DATA_BITS_8, ONE_STOP_BIT, NO_PARITY, 9600};

	/*********	TWI_Configuration structure		*********/
	TWI_ConfigType TWI_Configuration = {TWI_ADDRESS,400000};


	UART_init(&UART_Config);		//Initialize UART
	DcMotor_Init();						//Initialize DC Motor
	TWI_init(&TWI_Configuration);		//Initialize TWI
	BUZZER_init();						//Initialize Buzzer


	TIMER1_setCallBack(motorTimer);


	while(1)
	{
		/****	RECIEVE PASS and CONFIRM from HMI_ECU ****/

		while(matching == 0)
		{
			create_password();			//Call create_pass function to check on passwords
			UART_sendByte(CHECK);	//Sending CHECK instruction to HMI_ECU
			while(UART_recieveByte()!= UART1_READY){}	//Wait for MC1_Ready instruction
			UART_sendByte(matching);				//Send the check result whether passwords are matched or not

			if(matching == 1)
			{
				/****** SAVE PASS in EEPROM *******/
				EEPROM_WRITE_PASS(pass);
				EEPROM_WRITE_CONFRIM(confirm);
			}
		}

		/***** RECIEVE OPTION *****/
		option_processing();

		/***** Activate Buzzer when Password is entered wrong 3 times *****/
		if(eeprom_match == 0 && pass_error == MAX_NUM_OF_MISTAKES)
		{
			TIMER_init (&TIMER_Config);	//Initialize Timer1
			motor_time = 0;						//Set seconds to 0
			BUZZER_on();						//Activate Buzzer
			while(motor_time <= 60){			//Delay 60 seconds using Timer1
			}
			TIMER_DeInit();					//Deactivate Timer1
			BUZZER_off();						//Deactivate Buzzer

			pass_error = 0;						//Reset Password error variable
		}
		/***** Handling the operation chosen by the user if entered password is correct *****/

		if (eeprom_match == 1 && option == '+')
		{
			TIMER_init(&TIMER_Config);	//Initialize Timer1
			motor_time = 0;						//Set seconds to 0
			DcMotor_Rotate(CW);			//Activate DC Motor
			while(motor_time < OPENING_DOOR_TIME)
			{
				//Delay 15 seconds using Timer1
			}
			motor_time = 0;						//Set seconds to 0 to reset counting
			DcMotor_Rotate(STOP);			//Deactivate DC Motor
			while(motor_time < HOLDING_DOOR_TIME)
			{
				//Delay 3 seconds using Timer1
			}
			motor_time = 0;						//Set seconds to 0 to reset counting
			DcMotor_Rotate(CW);			//Activate DC Motor
			while(motor_time < CLOSING_DOOR_TIME)
			{
				//Delay 15 seconds using Timer1
			}
			DcMotor_Rotate(STOP);			//Deactivate DC Motor
			TIMER_DeInit();					//Deactivate Timer1
		}
		else if(eeprom_match == 1 && option == '-'){
			matching = 0;						/***** Reset pass_match to go back to create_pass function *****/
		}

		eeprom_match = 0;						/***** Reset eeprom_match to go back to option screen *****/
	}

}

/**********************************	Function Definitions ************************************/

void motorTimer(void)
{
	//SET CALLBACK Function
	motor_time++;		//Increment number of seconds every time interrupt occurs and set callback function is called
}

void option_processing(void){
	pass_error = 0;
	while(UART_recieveByte()!= OPTION){}	// Wait for option instruction
	UART_sendByte(UART2_READY);				// Send ready to receive the option
	option = UART_recieveByte();			// Store the option
	if(option == '+' || option == '-')
	{
		while(eeprom_match == 0 && pass_error < MAX_NUM_OF_MISTAKES )
		{

			UART_sendByte(UART2_READY);					// Send ready to receive the password
			while(UART_recieveByte()!= PASS_READY){}	// Wait for password confirmation from HMI_ECU
			counter = 0;
			UART_sendByte(UART2_READY);					// Send ready to receive the password
			for(counter = 0; counter< PASSWORD_SIZE; counter++)
			{
				check_pass[counter] = UART_recieveByte();
			}

			EEPROM_readByte(PASS_ADDRESS, passEEPROM);  		/* Read PASS from the external EEPROM */
			_delay_ms(10);
			EEPROM_readByte(PASS_ADDRESS+0x8, passEEPROM+1);  		/* Read PASS from the external EEPROM */
			_delay_ms(10);
			EEPROM_readByte(PASS_ADDRESS+0x10, passEEPROM+2);  		/* Read PASS from the external EEPROM */
			_delay_ms(10);
			EEPROM_readByte(PASS_ADDRESS+0x18, passEEPROM+3);  		/* Read PASS from the external EEPROM */
			_delay_ms(10);
			EEPROM_readByte(PASS_ADDRESS+0x20, passEEPROM+4);  		/* Read PASS from the external EEPROM */
			_delay_ms(10);
			for(counter = 0; counter< PASSWORD_SIZE; counter++)
			{
				if(check_pass[0] == passEEPROM[0] ){					// Check if password is correct
					eeprom_match = 1;
				}else{
					eeprom_match = 0;
					break;
				}
			}
			UART_sendByte(CHECK);					//Send CHECK instruction to HMI_ECU
			while(UART_recieveByte()!= UART1_READY){}	//Wait for HMI_ECU to be ready
			UART_sendByte(eeprom_match);			//Send the result of whether the password entered matches EEPROM Pass
			if(eeprom_match == 0){
				pass_error++;						//Increment error value (Error limit = 3)
			}
		}
	}
}

void create_password(void)
{
	while(UART_recieveByte()!= PASS_READY){}	/****	Wait for PASS_READY instruction  ****/
	UART_sendByte(UART2_READY);					/****	Send READY	instruction to HMI_ECU to receive PASSWORD	****/
	for(counter=0; counter< PASSWORD_SIZE; counter++)
	{
		pass[counter] = UART_recieveByte();		/**** Receive PASSWORD form HMI_ECU	****/
	}

	while(UART_recieveByte()!= CONFIRM_READY){}	/****	Wait for CONFIRM_READY instruction  ****/
	UART_sendByte(UART2_READY);					/****	Send READY	instruction to HMI_ECU to receive the CONFIRM_PASS	****/
	for(counter=0; counter < PASSWORD_SIZE; counter++)
	{
		confirm[counter] = UART_recieveByte();
	}

	for(counter = 0; counter < PASSWORD_SIZE; counter++)
	{
		if(pass[counter] == confirm[counter]){	//Compare between PASSWORD and CONFIRMATION PASSWORD
			matching = 1;
		}
		else{
			matching = 0;
			break;
		}
	}
}

void EEPROM_WRITE_PASS(uint8 arr[])
{
	/* To save each integer of the password in the EEPROM */
	EEPROM_writeByte(PASS_ADDRESS	, pass[0]);  		/* Write PASS in the external EEPROM */
	_delay_ms(10);
	EEPROM_writeByte(PASS_ADDRESS+0x8, pass[1]);  		/* Write PASS in the external EEPROM */
	_delay_ms(10);
	EEPROM_writeByte(PASS_ADDRESS+0x10, pass[2]);  		/* Write PASS in the external EEPROM */
	_delay_ms(10);
	EEPROM_writeByte(PASS_ADDRESS+0x18, pass[3]);  		/* Write PASS in the external EEPROM */
	_delay_ms(10);
	EEPROM_writeByte(PASS_ADDRESS+0x20, pass[4]);  		/* Write PASS in the external EEPROM */
	_delay_ms(10);
}
void EEPROM_WRITE_CONFRIM(uint8 arr[])
{
	EEPROM_writeByte(RECONFIRM_ADDRESS	, pass[0]);  		/* Write PASS in the external EEPROM */
	_delay_ms(10);
	EEPROM_writeByte(RECONFIRM_ADDRESS+ 0x8, pass[1]);  		/* Write PASS in the external EEPROM */
	_delay_ms(10);
	EEPROM_writeByte(RECONFIRM_ADDRESS+0x10, pass[2]);  		/* Write PASS in the external EEPROM */
	_delay_ms(10);
	EEPROM_writeByte(RECONFIRM_ADDRESS+0x18, pass[3]);  		/* Write PASS in the external EEPROM */
	_delay_ms(10);
	EEPROM_writeByte(RECONFIRM_ADDRESS+0x20, pass[4]);  		/* Write PASS in the external EEPROM */
	_delay_ms(10);
}
