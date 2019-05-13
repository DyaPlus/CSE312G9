#include "Temperature_Sensor.h"

void Temperature_Sensor_Init(void){
	 ADC0_Init();
}


uint8_t Read_Temp_Sensor_Value(void){	
	uint16_t data;
	ADC0_SS3_In(&data);

  return (147.5-((247.5*(data))/4096));	
}
