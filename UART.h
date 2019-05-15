#ifndef __UART_H__
#define	__UART_H__

#include "stdint.h"

void UART0_Init(void);

uint8_t UART0_Available(void);

uint8_t UART0_Read(void);

void UART0_Write(char []);

#endif // __UART_H__