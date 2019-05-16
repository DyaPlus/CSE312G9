// 0.Documentation Section 
// port_init function
// Runs on  TM4C123
// Authors: khaled ahmed abdelgalil
// Date: 18/3/2019


// 1. Pre-processor Directives Section
#include "tm4c123gh6pm.h"
#include "typedefs.h"
#include "Port.h"



void PortA_Init() {
	GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;				// unlock PORTA
	GPIO_PORTA_AMSEL_R &= ~0xFF;      				// Disable analog function
  	GPIO_PORTA_PCTL_R &= ~0xFF;  					// GPIO clear bit PCTL  
  	GPIO_PORTA_AFSEL_R &= ~0xFF;      				// No alternate function
  	GPIO_PORTA_DEN_R |= 0xFF; 						// digital enable PORTA

}

void PortB_Init() {
		GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;				// unlock PORTB
		GPIO_PORTB_CR_R |= 0xFF;
		GPIO_PORTB_AMSEL_R &= ~0xFF;      				// Disable analog function
  	GPIO_PORTB_PCTL_R &= ~0xFF;  					// GPIO clear bit PCTL  
  	GPIO_PORTB_AFSEL_R &= ~0xFF;      				// No alternate function
  	GPIO_PORTB_DEN_R |= 0xFF; 						// digital enable PORTB

}

void PortC_Init() {
		GPIO_PORTC_LOCK_R = GPIO_LOCK_KEY;				// unlock PORTC
		GPIO_PORTC_AMSEL_R &= ~0xF0;      				// Disable analog function
  	GPIO_PORTC_PCTL_R &= ~0xFF;  					// GPIO clear bit PCTL  
  	GPIO_PORTC_AFSEL_R &= ~0xF0;      				// No alternate function
  	GPIO_PORTC_DEN_R |= 0xF0; 						// digital enable PORTC

}

void PortD_Init() {
	GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;				// unlock PORTD
	GPIO_PORTD_CR_R|=0x80;                    //to allow changes to pD7
	GPIO_PORTD_AMSEL_R &= ~0xFF;      				// Disable analog function
  	GPIO_PORTD_PCTL_R &= ~0xFF;  					// GPIO clear bit PCTL  
  	GPIO_PORTD_AFSEL_R &= ~0xFF;      				// No alternate function
  	GPIO_PORTD_DEN_R |= 0xFF; 						// digital enable PORTD

}

void PortE_Init() {
	GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;				// unlock PORTE
	GPIO_PORTE_AMSEL_R &= ~0xFF;      				// Disable analog function
  	GPIO_PORTE_PCTL_R &= ~0xFF;  					// GPIO clear bit PCTL  
  	GPIO_PORTE_AFSEL_R &= ~0xFF;      				// No alternate function
  	GPIO_PORTE_DEN_R |= 0xFF; 						// digital enable PORTE

}

void PortF_Init() {
		GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;				// unlock PORTF
		GPIO_PORTF_CR_R |= 0x1F;          				// Allow changes to PortF
		GPIO_PORTF_AMSEL_R &= ~0xFF;      				// Disable analog function
  	GPIO_PORTF_PCTL_R &= ~0xFFFFF;  					// GPIO clear bit PCTL  
  	GPIO_PORTF_AFSEL_R &= ~0xFF;      				// No alternate function
  	GPIO_PORTF_DEN_R |= 0x1F; 						// digital enable PORTF

}



void Port_Init (uint8 port_index){
	
		volatile unsigned long delay;
		SYSCTL_RCGCGPIO_R |= (1 << port_index);          // Enable clock of port
		delay = SYSCTL_RCGCGPIO_R;        				// Dummy Delay 
	
	switch (port_index)

	{	

		case 0 : PortA_Init();
		break;


		case 1 : PortB_Init();
		break;


		case 2 : PortC_Init();
		break;


		case 3 : PortD_Init(); 
		break;


		case 4 : PortE_Init();
		break;


		case 5 : PortF_Init();
		break;
	}
}


