#include "ADC.h"


#define ADC0_SS0_PRI 			0x3
#define ADC0_SS1_PRI 			(0x2 << 4)
#define ADC0_SS2_PRI 			(0x1 << 8)
#define ADC0_SS3_PRI 			(0x0 << 12)
#define ADC0_ACTSS_SS3     0x8
#define ADC0_EMUX_SS3			(0x0 << 12)                                              //  processor trigger
#define ADC0_SSMUX3				 0x0	                                                   // AIN0->PE3
#define ADC0_SSCTL3_IE0		(0x1 << 2)
#define ADC0_SSCTL3_END0	(0x1 << 1)
#define GPIO_PE3_M         (1  << 4)
#define ADC0_PSSI_SS3			(0x1 << 3)
#define ADC0_RIS_INR3			(0x1 << 3)
#define ADC0_SSCTL3_TS0    (1  << 3 )

void ADC0_Init(void){
	SYSCTL_RCGCADC_R |= SYSCTL_RCGCADC_R0;                                           //enable ADC   ->(1<<0)
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;                                         // CLOCK       ->(1<<4)
	//............CONFIGRATION OF SEQUENCER................//
	ADC0_SSPRI_R |= (ADC0_SS1_PRI | ADC0_SS0_PRI | ADC0_SS2_PRI | ADC0_SS3_PRI);     //32 BIT  GIVE PRIORITY TO SS3 THEN 2 1 0
	
	ADC0_ACTSS_R &= ~(ADC0_ACTSS_SS3);                                               //DISABLE SEQUENCER 3  WHICH IS bit 4 in register 
	ADC0_EMUX_R |=  (ADC0_EMUX_SS3) ;                      	                         //tell mc which option will use to start conversation -- iused processor

	#ifndef TEMPERTURE_SENSOR
	ADC0_SSMUX3_R= ADC0_SSMUX3;                                                      //SELECT AIN0->PE3 CHANNEL TO BE TRIGGERED
  ADC0_SSCTL3_R |=(ADC0_SSCTL3_IE0|ADC0_SSCTL3_END0); 	                           // TO AVOID WRONG CONV END0->1 IE0->1 TO MAKE BIT INR IN RIS REG BE 1 AFTER ENDING CONV
  #else
	ADC0_SSCTL3_R |=(ADC0_SSCTL3_IE0|ADC0_SSCTL3_END0|ADC0_SSCTL3_TS0);              // TO AVOID WRONG CONV END0->1 IE0->1 TO MAKE BIT INR IN RIS REG BE 1 AFTER ENDING CONV
 #endif

	ADC0_ACTSS_R |= ADC0_ACTSS_SS3;                                                  //ENABLE  SEQUENCER 3  WHICH IS bit 4 in register
		//............CONFIGRATION OF GPIO PORT E................//
	GPIO_PORTE_DIR_R &= ~GPIO_PE3_M;
	GPIO_PORTE_AFSEL_R |= GPIO_PE3_M;
  GPIO_PORTE_DEN_R &= ~GPIO_PE3_M;
  GPIO_PORTE_AMSEL_R |= GPIO_PE3_M;
}

void ADC0_SS3_In(uint16_t *data){
	ADC0_PSSI_R = ADC0_PSSI_SS3;
	while((ADC0_RIS_R&ADC0_RIS_INR3)!=ADC0_RIS_INR3);
	*data = ADC0_SSFIFO3_R&0xFFF;
	ADC0_ISC_R = ADC0_RIS_INR3;
}

///  uint16_t temp_value(uint16_t *d){}
/*
uint16_t ADC0_SS3_In(void){
	
	 ADC0_PSSI_R = ADC0_PSSI_SS3;
while((ADC0_RIS_R&ADC0_RIS_INR3)!=ADC0_RIS_INR3);	                                 //polling on bit INR3 for sequencer 3 till be assigned to end conv
	 ADC0_ISC_R = ADC0_RIS_INR3;                                                     //clear bit INR3 by assign 1 in bit 3 in isc
	return (ADC0_SSFIFO3_R&0xFFF);                                                   //return value on fifo
	
	
}
*/