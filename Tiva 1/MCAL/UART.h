/*
 * UART.h
 *
 *  Created on: Apr 9, 2019
 *      Author: lenovo
 */

#ifndef UART_H_
#define UART_H_

#include "tm4c123gh6pm.h"
#include "Static_Config.h"
#include "stdint.h"
#include "std_type.h"

#define BAUD_RATE 9600
#define scale 16

void UART7_Init(void);

void UART7_sendByte(const uint8_t data);

uint8_t UART7_recieveByte(void);

void UART7_sendString(const uint8_t *Str);

void UART7_receiveString(uint8_t *Str);
//...........//
void UART0_Init(void);

void UART0_sendByte(const uint8_t data);

uint8_t UART0_recieveByte(void);

void UART0_sendString(const uint8_t *Str);

void UART0_receiveString(uint8_t *Str);


#endif /* UART_H_ */
