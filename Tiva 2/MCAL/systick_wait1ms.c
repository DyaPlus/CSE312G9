#include "systick.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"

#define CLOCK_CYCLES_PER_MS 80000

void systick_wait1ms(void){
	NVIC_ST_RELOAD_R = CLOCK_CYCLES_PER_MS - 1;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R&NVIC_ST_CTRL_COUNT) != NVIC_ST_CTRL_COUNT);
}

/*void systick_wait1ms(void){
	uint32_t elapsedTime;
  uint32_t startTime = NVIC_ST_CURRENT_R;
  do{
    elapsedTime = (startTime - NVIC_ST_CURRENT_R)&0x00FFFFFF;
  }
  while(elapsedTime <= CLOCK_CYCLES_PER_MS);
}*/
