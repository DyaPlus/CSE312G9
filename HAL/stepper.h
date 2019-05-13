#ifndef STEPPER_H_
#define STEPPER_H_
#include "tm4c123gh6pm.h"
#include "std_type.h"
#include "delay.h"

#define HALF_WAVE_STEPS 8


void stepper_init(void);
void step_forword(void);
void step_backword(void);
#endif 
