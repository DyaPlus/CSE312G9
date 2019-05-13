#include "LED.h"

void LED_Init(void){
	GPIO_PORTF_AFSEL_R |= GPIO_PF3_M;
	GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFF0FFF) | (GPIO_PCTL_PF3_M1PWM7);
	GPIO_PORTF_DIR_R |= GPIO_PF3_M;
	GPIO_PORTF_DEN_R |= GPIO_PF3_M;
}

void LED_Intensity(uint8_t duty_cycle){
	SetDutyCycle(duty_cycle);
}