#include "PWM.h"
void PWM1_Init(void){
	
SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R1;   // enable pwm for pwm1           
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5; //enable clock for port f
SYSCTL_RCC_R |= SYSCTL_RCC_USEPWMDIV;
SYSCTL_RCC_R |= SYSCTL_RCC_PWMDIV_64;   

//.........................(PWM_1_) (GEN3_GENB)_ (COMPARETORA-ACTION)..........................//
	
	PWM1_3_CTL_R = STOP_COUNTER;
	PWM1_3_GENB_R =0X0000008C;
	PWM1_3_LOAD_R = LOAD_VALUE;
	PWM1_3_CMPA_R = COMPA_VALUE;
	PWM1_3_CTL_R = START_COUNTER;
	PWM1_ENABLE_R = PWM_ENABLE_PWM7EN;	
}

void SetDutyCycle(uint8_t duty_cycle){
		PWM1_3_CMPA_R = (uint16_t)(LOAD_VALUE* (1 - (duty_cycle / 100.0)) - 1);
}