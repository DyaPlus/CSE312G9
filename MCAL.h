// 0.Documentation Section 
// Runs on LM4F120 or TM4C123
// MCAL library contains initilazation-functions-prototypes of ports
// Authors: khaled ahmed abdelgalil
// Date: 18/3/2019
#include "tm4c123gh6pm.h"
#include "typedefs.h"

#ifndef MCAL_H_
#define MCAL_H_

/*Enum contains the direction of GPIO pins
0 for input 
1 for output
*/

//ports index and pins index
#define PORTA_P 0x40004000UL
#define PORTB_P 0x40005000UL
#define PORTD_P 0x40007000UL
#define PORT_A_INDEX  0
#define PORT_B_INDEX  1
#define PORT_C_INDEX  2
#define PORT_D_INDEX  3
#define PORT_E_INDEX  4
#define PORT_F_INDEX  5
#define PORT_UPPER  0xF0
#define PORT_LOWER  0x0F
#define LOWER_3_PINS 0x07
#define PIN_2 0x02
#define PIN_3 0x04



#define HWREG(x) 						(*((volatile unsigned long *)(x)))
enum Port_PinDirectionType {
	 PORT_PIN_IN = 0  , PORT_PIN_OUT = 1 
};

enum Dio_LevelType {
	 STD_LOW = 0  , STD_HIGH = 1 
};

//functions prototype
void Port_SetPinDirection (uint8 port_index , uint8 pins_mask , enum Port_PinDirectionType pins_direction);
void Port_Init (uint8 port_index);
void Port_SetPinPullUp (uint8 port_index , uint8 pins_mask , uint8 enable);
void Port_SetPinPullDown (uint8 port_index , uint8 pins_mask , uint8 enable);
uint8 DIO_ReadPort(uint8 port_index , uint8 pins_mask);
void DIO_WritePort(uint8 port_index , uint8 pins_mask , enum Dio_LevelType);
void DIO_WritePort1(unsigned char word,uint32 port, uint8 mask);
void DIO_FlipPort(uint8 port_index , uint8 pins_mask);

#endif /* MCAL_H_ */
