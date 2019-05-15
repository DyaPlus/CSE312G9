#include "button.h"

char isPressed(char Port_index , char Pin_Number)
{	

			case(Port_index)
			{
				case 0: 
				return (GPIO_PORTA_DATA_R & (1 << Pin_Number) 
				break;
				case 1: 
				return (GPIO_PORTB_DATA_R & (1 << Pin_Number) 
				break;
				case 3: 
				return (GPIO_PORTC_DATA_R & (1 << Pin_Number) 
				break;
				case 4: 
				return (GPIO_PORTD_DATA_R & (1 << Pin_Number) 
				break;
				case 5: 
				return (GPIO_PORTE_DATA_R & (1 << Pin_Number) 
				break;
				case 6: 
				return (GPIO_PORTF_DATA_R & (1 << Pin_Number) 
				break;
			}			
}		