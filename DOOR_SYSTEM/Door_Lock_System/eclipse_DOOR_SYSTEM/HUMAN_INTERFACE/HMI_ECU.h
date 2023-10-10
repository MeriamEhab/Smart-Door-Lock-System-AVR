/*
 * HMI_ECU.h
 *
 *  Created on: Nov 6, 2022
 *      Author: Meriam Ehab
 */

#ifndef HMI_ECU_H_
#define HMI_ECU_H_

#ifndef HMI_H_
#define HMI_H_

#include"std_types.h"



#define PASSWORD_READY		0x01
#define	CONFIRM_READY	0x02
#define	UART1_READY		0x03
#define UART2_READY 		0x04
#define CHECK			0x05
#define OPTION			0x06
#define PASSWORD_SIZE          5
#define MAX_NUM_OF_MISTAKES    3
#define OPENING_DOOR_TIME     15
#define HOLDING_DOOR_TIME      3
#define CLOSING_DOOR_TIME     15
#define WARNING_TIME          60

void Welcome_Screen (void);
void create_password(void);
void send_password(uint8 arr[]);
void send_confirm(uint8 arr[]);
void Main_Menu(void);

void Door_Locking(void);
void Door_Unlocking(void);
void messageTimer(void);

#endif /* HMI_H_ */


#endif /* HMI_ECU_H_ */
