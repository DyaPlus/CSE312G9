#ifndef LED_H_
#define LED_H_
#include "pwm.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "Static_Config.h"
#include "std_type.h"

void LED_Init(void);
void LED_Intensity(uint8_t duty_cycle);
#endif