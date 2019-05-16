// 0.Documentation Section 
// port_setPinDirection function
// Runs on LM4F120 or TM4C123
// Authors: khaled ahmed abdelgalil
// Date: 18/3/2019

// 1. Pre-processor Directives Section
#include "tm4c123gh6pm.h"
#include "typedefs.h"
#include "MCAL.h"


// function to set direction of selected pins of port
//INPUTS:port_index,selected_pins,direction
//outputs:void
void Port_SetPinDirection (uint8 port_index , uint8 pins_mask , enum Port_PinDirectionType pins_direction)
{

	switch (port_index)
	{
		case 0 : 

		if (pins_direction == PORT_PIN_IN)  
		{
			GPIO_PORTA_DIR_R &= ~pins_mask;
		}
		else if (pins_direction == PORT_PIN_OUT) 
		{
			GPIO_PORTA_DIR_R |= pins_mask;
		}
		break;

		case 1 : 
		
		if (pins_direction == PORT_PIN_IN) 
		{
			GPIO_PORTB_DIR_R &= ~pins_mask;
		}
		else if (pins_direction == PORT_PIN_OUT) 
		{
			GPIO_PORTB_DIR_R |= pins_mask;
		}
		break;

		case 2 :

		if (pins_direction == PORT_PIN_IN) 
		{
			GPIO_PORTC_DIR_R &= ~pins_mask;
		}
		else if (pins_direction == PORT_PIN_OUT) 
		{
			GPIO_PORTC_DIR_R |= pins_mask;
		}
		break;

		case 3 : 

		if (pins_direction == PORT_PIN_IN) 
		{
			GPIO_PORTD_DIR_R &= ~pins_mask;
		}
		else if (pins_direction == PORT_PIN_OUT) 
		{
			GPIO_PORTD_DIR_R |= pins_mask;
		}
		break;

		case 4 : 

		if (pins_direction == PORT_PIN_IN) 
		{
			GPIO_PORTE_DIR_R &= ~pins_mask;
		}
		else if (pins_direction == PORT_PIN_OUT) 
		{
			GPIO_PORTE_DIR_R |= pins_mask;
		}

		case 5 : 

		if (pins_direction == PORT_PIN_IN) 
		{
			GPIO_PORTF_DIR_R &= ~pins_mask;
		}
		else if (pins_direction == PORT_PIN_OUT) 
		{
			GPIO_PORTF_DIR_R |= pins_mask;
		}
		break;
	}
}



