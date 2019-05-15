#include "tm4c123gh6pm.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Static_Config.h"
#include "std_type.h"
#include "PWM.h"
#include "pll.h"
#include "LED.h"
#include "UART.h"
#include "systick.h"
#include "Temperature_Sensor.h"
#include "stdio.h"
#include "delay.h"
#include "stdint.h"
#include "stepper.h"
#include "semphr.h"
#include "string.h"
#include "stdlib.h"
#define GPIO_PF321_M				0x0EU 	//Pins 3, 2, and 1 are connected to RGB LED

/*   Task.....Handler     */
TaskHandle_t MyTask1Handler =NULL;
TaskHandle_t MyTask2Handler =NULL;
TaskHandle_t MyTask3Handler =NULL;
SemaphoreHandle_t led_mutex=0;            //DEFINE_MUTEX
//.............................................................//
char Main_Command [10];       // *->Stepper_Command    $->Led_Intensity_Command
char step[10];
//...............................Send_Temperature_Task....................................//
void Send_Temperature(void *p)
{
	//..............Define..Delay....................//
	const TickType_t xDelay = pdMS_TO_TICKS(100);        
  TickType_t xLastWakeTime = xTaskGetTickCount();
	char Temp[10];
	//..............Send_Temperature_Value....................//
while(1)
{
		sprintf(Temp,"%d",Read_Temp_Sensor_Value());
	    	UART7_sendString(Temp);
	      UART7_sendString("*");
	
	vTaskDelayUntil(&xLastWakeTime, xDelay);
	}	
}
//..................................Stepper_Task......................................//
void Recieve_Stepper_Command (void *p) {
	//..............Define..Delay....................//
	const TickType_t xDelay = pdMS_TO_TICKS(100);
  TickType_t xLastWakeTime = xTaskGetTickCount();
char command[10];                            // 1-> clockwise    3-> Anti clockwise
	while(1){

		if(xSemaphoreTake(led_mutex,1500 ))                          //acquire_mutex
		{  
			if(!strcmp(Main_Command,"*")){
			UART7_receiveString(command);
			if(!strcmp(command,"1"))
			{
				step_forword();
			}
			else if(!strcmp(command,"3"))
			{
				step_backword();
			}	
		}
	   xSemaphoreGive(led_mutex);                                  //release_mutex
		}
		vTaskDelayUntil(&xLastWakeTime, xDelay);
	}
}
//.....................................Led_Task.......................................//
void Receive_Led_Intensity(void* p) {
	const TickType_t xDelay = pdMS_TO_TICKS(100);
  TickType_t xLastWakeTime = xTaskGetTickCount();
	int i;
	char command[10];
	char intensity[10];
	while (1) 
	{  
 if(xSemaphoreTake(led_mutex,1500 ))                              //acquire_mutex
		{
			UART7_receiveString(Main_Command);
			if(!strcmp(Main_Command,"$"))
			{
	   	UART7_receiveString(intensity);
			i=atoi(intensity);
			LED_Intensity(i);
				
      }
	   xSemaphoreGive(led_mutex);                                  //release_mutex
		}
	
	vTaskDelayUntil(&xLastWakeTime, xDelay);

	}
}
//.......................................................................//
int main(void){
	//...................Create_Mutex.......................//
   led_mutex = xSemaphoreCreateMutex();
	//...................System_Initilization...............//
	PLL_Init();	
	systick_init();
	LED_Init();	
	UART7_Init();
	Temperature_Sensor_Init();
	stepper_init();
//......................Define&Create_Os_Services.........................................//
	xTaskCreate(Receive_Led_Intensity, "Pot", 200, NULL, 1, &MyTask1Handler);
	xTaskCreate(Recieve_Stepper_Command, "Pot1", 200, NULL, 1, &MyTask2Handler);
	xTaskCreate(Send_Temperature, "Pot2", 200, NULL, 1, &MyTask3Handler);
	vTaskStartScheduler();
	while (1) 	
	{  

	}

}
 
	
