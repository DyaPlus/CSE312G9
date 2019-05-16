#include "tm4c123gh6pm.h"
#include "ADC.h"
#include <stdint.h>

#define ADC0_SS0_PRI 			0x3
#define ADC0_SS1_PRI 			(0x2 << 4)
#define ADC0_SS2_PRI 			(0x1 << 8)
#define ADC0_SS3_PRI 			(0x0 << 12)
#define ADC0_ACTSS_SS3 		0x8
#define ADC0_EMUX_SS3			(0x0 << 12) // Processor Trigger
#define ADC0_SSMUX3				0x0					// AIN0 (PE3)
#define ADC0_SSCTL3_IE0		(0x1 << 2)
#define ADC0_SSCTL3_END0	(0x1 << 1)
#define ADC0_PSSI_SS3			(0x1 << 3)
#define ADC0_RIS_INR3			(0x1 << 3)
#define GPIO_PE3_M				(0x1 << 3)

void ADC0_Init(void){
	SYSCTL_RCGCADC_R |= SYSCTL_RCGCADC_R0;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
	ADC0_SSPRI_R = (ADC0_SS3_PRI | ADC0_SS2_PRI | ADC0_SS1_PRI | ADC0_SS0_PRI);
	ADC0_ACTSS_R &= ~ADC0_ACTSS_SS3;
	ADC0_EMUX_R = (ADC0_EMUX_R&0x0FFF) | ADC0_EMUX_SS3;
	ADC0_SSMUX3_R = ADC0_SSMUX3;
	ADC0_SSCTL3_R |= (ADC0_SSCTL3_IE0 | ADC0_SSCTL3_END0);
	ADC0_ACTSS_R |= ADC0_ACTSS_SS3;
	GPIO_PORTE_DIR_R &= ~GPIO_PE3_M;
	GPIO_PORTE_AFSEL_R |= GPIO_PE3_M;
  GPIO_PORTE_DEN_R &= ~GPIO_PE3_M;
  GPIO_PORTE_AMSEL_R |= GPIO_PE3_M;
}

uint16_t ADC0_SS3_In(void){
	ADC0_PSSI_R = ADC0_PSSI_SS3;
	while((ADC0_RIS_R&ADC0_RIS_INR3)!=ADC0_RIS_INR3);
	ADC0_ISC_R = ADC0_RIS_INR3;
	uint16_t data = ADC0_SSFIFO3_R&0xFFF;
	return data;
}
