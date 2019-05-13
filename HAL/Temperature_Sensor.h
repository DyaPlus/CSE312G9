#ifndef TEMPERATURE_SENSOR_H_
#define TEMPERATURE_SENSOR_H_

#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "ADC.h"
void Temperature_Sensor_Init(void);
uint8_t Read_Temp_Sensor_Value(void);

#endif