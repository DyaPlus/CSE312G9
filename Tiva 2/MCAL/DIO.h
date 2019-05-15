#include "tm4c123gh6pm.h"
#include "typedefs.h"

#ifndef DIO_H_
#define DIO_H_

enum Dio_LevelType {
	 STD_LOW = 0  , STD_HIGH = 1 
};

//functions prototype
uint8 DIO_ReadPort(uint8 port_index , uint8 pins_mask);
void DIO_WritePort(uint8 port_index , uint8 pins_mask , enum Dio_LevelType);
void DIO_WritePort1(unsigned char word,uint32 port, uint8 mask);
void DIO_FlipPort(uint8 port_index , uint8 pins_mask);

#endif 