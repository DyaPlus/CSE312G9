
// 1. Pre-processor Directives Section
#include "tm4c123gh6pm.h"
#include "typedefs.h"
#include "MCAL.h"

// function to set pulldown of selected pins of port
//INPUTS:port_index,selected_pins,enable
//outputs:void

void Port_SetPinPullDown (uint8 port_index , uint8 pins_mask , uint8 enable)
{
 switch (port_index)
	{
		case 0 : 

		if (enable == 1) 
		{
			GPIO_PORTA_PDR_R |= pins_mask;
		}
		else if (enable == 0) 
		{
			GPIO_PORTA_PDR_R &= ~pins_mask;
		}
		break;

		case 1 : 
		
		if (enable == 1) 
		{
			GPIO_PORTB_PDR_R |= pins_mask;
		}
		else if (enable == 0) 
		{
			GPIO_PORTB_PDR_R &= ~pins_mask;
		}
		break;

		case 2 :

		if (enable == 1) 
		{
			GPIO_PORTC_PDR_R |= pins_mask;
		}
		else if (enable == 0) 
		{
			GPIO_PORTC_PDR_R &= ~pins_mask;
		}
		break;

		case 3 : 

		if (enable == 1) 
		{
			GPIO_PORTD_PDR_R |= pins_mask;
		}
		else if (enable == 0) 
		{
			GPIO_PORTD_PDR_R &= ~pins_mask;
		}
		break;

		case 4 : 

		if (enable == 1) 
		{
			GPIO_PORTE_PDR_R |= pins_mask;
		}
		else if (enable == 0) 
		{
			GPIO_PORTE_PDR_R &= ~pins_mask;
		}
		case 5 : 

		if (enable == 1) 
		{
			GPIO_PORTF_PDR_R |= pins_mask;
		}
		else if (enable == 0) 
		{
			GPIO_PORTF_PDR_R &= ~pins_mask;
		}
		break;
	}

}