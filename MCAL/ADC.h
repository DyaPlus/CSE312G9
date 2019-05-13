#ifndef UART_H_
#define UART_H_
#define TEMPERTURE_SENSOR 
#include "tm4c123gh6pm.h"
#include "stdint.h"

void ADC0_Init(void);
void ADC0_SS3_In(uint16_t *data);

#endif