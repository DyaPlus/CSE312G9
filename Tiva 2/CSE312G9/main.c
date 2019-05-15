#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "stdio.h"
#include <string.h>

#include "lcd.h"
#include "typedefs.h"
#include "MCAL.h"



#include "PLL.h"
#include "ADC.h"
#include "UART.h"
#include "delay.h"
#include "systick.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#define GPIO_PF321_M				0x0EU 	//Pins 3, 2, and 1 are connected to RGB LED
#define GPIO_PF4_M					0x10U		// Pin 4 is connected to switch
#define GPIO_PF3_M					0x08U		// Pin 3 is connected to green	
#define GPIO_PF2_M					0x04U		// Pin 2 is connected to blue
#define GPIO_PF1_M					0x02U		// Pin 1 is connected to red
#define GPIO_PCTL_PF321_M		(GPIO_PCTL_PF3_M | GPIO_PCTL_PF2_M | GPIO_PCTL_PF1_M) // To combine masks, OR them together

#define GPIO_PA10_M 0x03

SemaphoreHandle_t led_mutex;            //DEFINE_MUTEX

void RGBLED_Init(void){
	volatile unsigned long delay;
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;  // PortF clock enable
  delay = SYSCTL_RCGCGPIO_R;        				// Delay   
  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;   			// Unlock PortF Commit register  
  GPIO_PORTF_CR_R |= 0xFF;          // Allow changes to PF321       
  GPIO_PORTF_AMSEL_R &= ~0xFF;      // Disable analog function
  GPIO_PORTF_PCTL_R &= ~0xFFFFF;  // GPIO clear bit PCTL  
  GPIO_PORTF_AFSEL_R &= ~0xFF;      // No alternate function
	GPIO_PORTF_DIR_R |= GPIO_PF321_M;         // PF321 output
	GPIO_PORTF_DIR_R &= ~0x11 ;
  GPIO_PORTF_DEN_R |= 0xFF;         // Enable digital pins PF4-PF0
	GPIO_PORTF_DATA_R &= ~0xFF;
	GPIO_PORTF_PUR_R |= 0x11;
	
}
void intToString(uint16_t data,char buff [])
{
  sprintf(buff,"%d",data); 
}
int toString(char a[]) {
  int c, sign, offset, n;
 
  if (a[0] == '-') {  // Handle negative integers
    sign = -1;
  }
 
  if (sign == -1) {  // Set starting position to convert
    offset = 1;
  }
  else {
    offset = 0;
  }
 
  n = 0;
 
  for (c = offset; a[c] != '\0'; c++) {
    n = n * 10 + a[c] - '0';
  }
 
  if (sign == -1) {
    n = -n;
  }
 
  return n;
}

void sendPotReading(void* p) {
	
	 const TickType_t xDelay = pdMS_TO_TICKS(200);
   TickType_t xLastWakeTime = xTaskGetTickCount();
//.........//
	int pre_value=-1;
//.........//
	while (1) 
	{
	uint16_t pout;
	char g [10];
	pout = ADC0_SS3_In();
	pout = (pout*100) / 4096;
		if(pout != pre_value)
		{
	intToString(pout,g);
	UART0_Write("$#"); // Initiating Char for Potentiometer (Choose depending on your target)
	UART0_Write(g);
	UART0_Write("#"); // Initiating Char for Potentiometer (Choose depending on your target)
		pre_value=pout;
    }
	vTaskDelayUntil(&xLastWakeTime, xDelay);
/*		pout = 0;
	pout = (pout*100) / 4096;
	intToString(pout,g);
	UART0_Write("$#"); // Initiating Char for Potentiometer (Choose depending on your target)
	UART0_Write(g);
	UART0_Write("#"); // Initiating Char for Potentiometer (Choose depending on your target)

		vTaskDelayUntil(&xLastWakeTime, xDelay);*/
	}
}
void sendBut1Reading(void* p) {
	const TickType_t xDelay = pdMS_TO_TICKS(100);
   TickType_t xLastWakeTime = xTaskGetTickCount();
	while (1) {
	
		uint16_t pout;
	char g [10];
	pout = 1;
	if (!(GPIO_PORTA_DATA_R & (0x08)))
	{			
			intToString(pout,g);
			UART0_Write("*#"); // Initiating Char for Increment (Choose depending on your target)
			UART0_Write(g);
			UART0_Write("#"); 
		//GPIO_PORTF_DATA_R ^= (1<<3);
		while (!(GPIO_PORTA_DATA_R & (0x08)));
	}
	//UART0_Write("\n"); // Ending Char for Console (Choose depending on your target
	

	vTaskDelayUntil(&xLastWakeTime, xDelay);
	} 
	
}

void ReceiveTemp(void* p) {
	const TickType_t xDelay = pdMS_TO_TICKS(100);
  TickType_t xLastWakeTime = xTaskGetTickCount();
	uint16_t pout;
	char g [10];
	uint8_t i = 0;
	char buff;
	while (1) {
	while (1)
		{
			buff = UART0_Read();
			if (buff == '*') break; 
			g[i++] = buff;
			i = i % 10; 			
		}
	pout = toString(g); // Integer value of the received value
	i = 0;
	
//	LCD_displayStringRowColumn(1,1,"Ramadan Kareem"); // Ending Char for Console (Choose depending on your target
	LCD_displayStringRowColumn(0,4,"Temp = ");
	LCD_displayStringRowColumn(0,11,g);
	memset(g,0,sizeof(g));

	vTaskDelayUntil(&xLastWakeTime, xDelay);
	}
}

void sendBut2Reading(void* p) {
const TickType_t xDelay = pdMS_TO_TICKS(100);
   TickType_t xLastWakeTime = xTaskGetTickCount();
	while (1) {
	
		uint16_t pout;
	char g [10];
	pout = 3;
	if (!(GPIO_PORTF_DATA_R & (0x10)))
	{			
			intToString(pout,g);
			UART0_Write("*#"); // Initiating Char for Increment (Choose depending on your target)
			UART0_Write(g);
			UART0_Write("#");
		while (!(GPIO_PORTF_DATA_R & (0x10)));
	}
	//UART0_Write("\n"); // Ending Char for Console (Choose depending on your target
	

	vTaskDelayUntil(&xLastWakeTime, xDelay);
	} 
	
}
void blink_led(void* p) {
	
	const TickType_t xDelay = pdMS_TO_TICKS(1000);
  TickType_t xLastWakeTime = xTaskGetTickCount();
	while(1) 
	{
	GPIO_PORTF_DATA_R ^= 0x2;
	vTaskDelayUntil(&xLastWakeTime, xDelay);
	}
}


int main(void){	

	Port_Init(0);
	Port_Init(3);
	Port_SetPinDirection(0,0x08,PORT_PIN_IN);
	Port_SetPinPullUp(0,0x08,1);

	
	RGBLED_Init();
	PLL_Init();
	UART0_Init();
	ADC0_Init();
	systick_init();
	
	LCD_init();
	LCD_clearScreen();
	
	
	xTaskCreate(sendBut1Reading, "Button Reading", 200, NULL, 1, NULL);
	xTaskCreate(sendBut2Reading, "Button Reading2", 200, NULL, 1, NULL);

	xTaskCreate(sendPotReading, "Pot reading", 200, NULL, 1, NULL);
	//xTaskCreate(blink_led, "Pot reading", 200, NULL, 1, NULL);
	xTaskCreate(ReceiveTemp, "Pot", 200, NULL, 1, NULL);

	vTaskStartScheduler();
	
	// should not reach this line
	//while(1);
	/*uint16_t pout;
	char g [10];
	pout = 3;
	if (!(GPIO_PORTF_DATA_R & (0x10)))
	{			
			intToString(pout,g);
			UART0_Write("*#"); // Initiating Char for Increment (Choose depending on your target)
			UART0_Write(g);
			UART0_Write("#");
	}*/
		//delay(3000);	
		//delay(2000);
		//sendBut1Reading();
		//nk,k,sendBut2Reading();
		//UART0_Write("\n");
		
	/*	while (1)
		{
			
				if (!(GPIO_PORTF_DATA_R & (0x10)))
			{			
			
			GPIO_PORTF_DATA_R = (1<<3);
			while (!(GPIO_PORTF_DATA_R & (0x10)));
			}
		}
*/		
}
