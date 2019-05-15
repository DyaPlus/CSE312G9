#ifndef __ADC_H__
#define __ADC_H__

#include <stdint.h>
#define ADC_RESOLUTION	(3.3 / 4096)

void ADC0_Init(void);

uint16_t ADC0_SS3_In(void);

#endif // __ADC_H__
