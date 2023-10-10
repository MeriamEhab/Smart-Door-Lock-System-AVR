/*
 * control.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Meriam Ehab
 */



#ifndef CONTROL_H_
#define CONTROL_H_

#include"std_types.h"
#include "micro_config.h"

#define PASS_READY		0x01
#define	CONFIRM_READY	0x02
#define	UART1_READY		0x03
#define UART2_READY	    0x04
#define CHECK			0x05

#define OPTION			0x06

#define TWI_ADDRESS    0b00000010
#define PASSWORD_SIZE          5
#define OPENING_DOOR_TIME     15
#define HOLDING_DOOR_TIME      3
#define CLOSING_DOOR_TIME     15
#define WARNING_TIME          60
#define MAX_NUM_OF_MISTAKES    3

#define PASS_ADDRESS		0x0311
#define	RECONFIRM_ADDRESS	0x0339

#define MISMATCHED             0
#define MATCHED                1
#define OPEN_DOOR             '+'
#define CHANGE_PASSWORD       '-'

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Description :
 * function that set a new password
 * if : The application start for the first time
 *      Or user wants to change the password
 */
void create_password(void);

/* Description :
 * function that save the matched password in EEPROM
 */
void EEPROM_WRITE_PASS(uint8 arr[]);
void EEPROM_WRITE_CONFRIM(uint8 arr[]);

void option_processing(void);

void motorTimer(void);

#endif /* CONTROL_H_ */

#ifndef CONTROL_H_
#define CONTROL_H_

#define TWI_ADDRESS    0b0000001
#define PASSWORD_SIZE          5
#define OPENING_DOOR_TIME     15
#define HOLDING_DOOR_TIME      3
#define CLOSING_DOOR_TIME     15
#define WARNING_TIME          60
#define SEND_RECEIVE_TIME     10
#define STORE_TIME            70
#define MAX_NUM_OF_MISTAKES    3


/*   definitions for uart commands with hmi_ecu   */
#define MISMATCHED             0
#define MATCHED                1
#define OPEN_DOOR             '+'
#define CHANGE_PASSWORD       '-'
#define SEND_CHECK_PASSWORD   ','
#define OPENING_DOOR          '!'
#define WRONG_PASSWORD        '_'
#define CHANGING_PASSWORD     '#'
#define READY_TO_SEND         '$'
#define READY_TO_RECEIVE      '&'
#define RECEIVE_DONE          '/'
#define SEND_FIRST_PASSWORD   '@'
#define SEND_CONFIRM_PASSWORD '~'
#define SEND_CHECK_PASSWORD   ','
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Description :
 * function that set a new password
 * if : The application start for the first time
 *      Or user wants to change the password
 */
void APP_newPassword(void);

/* Description :
 * function takes the password send for hmi_ecu by uart
 * store it in the argument a_Password[]
 */
void APP_receivePassword(char a_Password[], char SIZE);

/* Description :
 * function that compare the two passwords sent from hmi_ecu by uart
 * and return if they are matched or not
 */
char APP_comparePassword(char a_password1[], char a_password2[], char SIZE1, char SIZE2);

/* Description :
 * function that save the matched password in EEPROM
 */
void APP_savePassword(char a_receivedPassword[], char SIZE);

/* Description :
 * function that gets the password from EEPROM
 * and store it in a_storedPassword
 */
void APP_readPassword(char a_storedPassword[], char SIZE);

/* Description :
 * function that initiate the timer with the required configuration
 * to calculate the seconds
 */
void APP_startTimer(void);

/* Description :
 * function that set the call back with timer
 */
void TimerCallBackProcessing(void);

/* Description :
 * function that start the wrong password task
 * opens the buzzer if the password mistakes was 3
 */
void APP_wrongPassword(void);


#endif /* CONTROL_H_ */
