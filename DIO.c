#include "typedefs.h"
#include "tm4c123gh6pm.h"

#define HWREG(x) 						(*((volatile unsigned long *)(x)))
enum Dio_LevelType {
	 STD_LOW = 0  , STD_HIGH = 1 
};

uint8 DIO_ReadPort(uint8 port_index , uint8 pins_mask)
{
	switch (port_index)
	{
		case 0 : 

		return GPIO_PORTA_DATA_R & pins_mask;
		break;

		case 1 : 
		return GPIO_PORTB_DATA_R & pins_mask;
		break;

		case 2 :
		return GPIO_PORTC_DATA_R & pins_mask;
		break;

		case 3 : 
		return GPIO_PORTD_DATA_R & pins_mask;
		break;

		case 4 : 
		return GPIO_PORTE_DATA_R & pins_mask;
		break;

		case 5 : 
		return GPIO_PORTF_DATA_R & pins_mask;
		break;
	}
	return 0;
}


void DIO_WritePort1(unsigned char word,uint32 port, uint8 mask) {
		word = word & (mask);
		HWREG(port+0x3FC) = (word);
}


void DIO_WritePort(uint8 port_index , uint8 pins_mask , enum Dio_LevelType pins_level)
{
	switch (port_index)
	{
		case 0 : 
		if (pins_level == STD_LOW)
		{
			GPIO_PORTA_DATA_R &= ~pins_mask;
		}
		else 
		{
			GPIO_PORTA_DATA_R |= pins_mask;
		}
		break;

		case 1 : 
		if (pins_level == STD_LOW)
		{
			GPIO_PORTB_DATA_R &= ~pins_mask;
		}
		else 
		{
			GPIO_PORTB_DATA_R |= pins_mask;
		}
		break;

		case 2 :

		if (pins_level == STD_LOW)
		{
			GPIO_PORTC_DATA_R &= ~pins_mask;
		}
		else 
		{
			GPIO_PORTC_DATA_R |= pins_mask;
		}
		break;

		case 3 : 
		if (pins_level == STD_LOW)
		{
			GPIO_PORTD_DATA_R &= ~pins_mask;
		}
		else 
		{
			GPIO_PORTD_DATA_R |= pins_mask;
		}
		break;

		case 4 : 
		if (pins_level == STD_LOW)
		{
			GPIO_PORTE_DATA_R &= ~pins_mask;
		}
		else 
		{
			GPIO_PORTE_DATA_R |= pins_mask;
		}
		break;

		case 5 : 
		if (pins_level == STD_LOW)
		{
			GPIO_PORTF_DATA_R &= ~pins_mask;
		}
		else 
		{
			GPIO_PORTF_DATA_R |= pins_mask;
		}
		break;
	}
} 

void DIO_FlipPort(uint8 port_index , uint8 pins_mask)
{
	switch (port_index)
	{
		case 0 : 

		GPIO_PORTA_DATA_R ^= pins_mask;
		break;

		case 1 : 
		GPIO_PORTB_DATA_R ^= pins_mask;
		break;

		case 2 :
		GPIO_PORTC_DATA_R ^= pins_mask;
		break;

		case 3 : 
		GPIO_PORTD_DATA_R ^= pins_mask;
		break;

		case 4 : 
		GPIO_PORTE_DATA_R ^= pins_mask;
		break;

		case 5 : 
		GPIO_PORTF_DATA_R ^= pins_mask;
		break;
	}
}