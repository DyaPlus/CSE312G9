#ifndef PWM_H_
#define PWM_H_
#include "tm4c123gh6pm.h"
#include "Static_Config.h"
#include "std_type.h"
 
 #define GPIO_PF3_M	0x08	
#define STOP_COUNTER 0x00000000;
#define START_COUNTER 0x00000001;
#define LOAD_VALUE  1250
#define COMPA_VALUE 1249

void PWM1_Init(void);
void SetDutyCycle(uint8_t duty_cycle);


#endif