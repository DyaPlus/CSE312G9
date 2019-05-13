#include "stepper.h"


unsigned int count = 1;

void stepper_init(void)
{
	unsigned int motor_steps[HALF_WAVE_STEPS] = {1,5,4,6,2,10,8,9};
	   SYSCTL_RCGCGPIO_R  |=(1<<3);           //ENABLE CLOCK FOR PORTD
     while((SYSCTL_PRGPIO_R & 0x08)==0)     //WAIT UNTILL PORT D ARE READY TO BE ACCESSED
	   {};
		 GPIO_PORTD_LOCK_R  =0x4C4F434B;        //LOCK PORTD USING MAGICAL CODE
		 GPIO_PORTD_CR_R=0x0F;                  //LOCK ALL PINS FOR PORTD                 
		 GPIO_PORTD_DEN_R=0X0F;                 //ENABLE AS  1-->DIGITAL
		 GPIO_PORTD_AFSEL_R=0X00;               //ENABLE AS  0-->I/O
		 GPIO_PORTD_PCTL_R=0X00000000;          //ONLY I/O IS ENABLE FOR PORTD NO OTHER FUNCTION
		 GPIO_PORTD_AMSEL_R=0X00;               //DISABLE  0-->ANALOG MODE
		 GPIO_PORTD_DIR_R=0X0F; 
		 GPIO_PORTD_DATA_R = (motor_steps[0] & 0x0F) | (GPIO_PORTD_DATA_R & 0xF0);
}

void step_forword(void)
{
	  unsigned int step = 0;
	unsigned int motor_steps[HALF_WAVE_STEPS] = {1,5,4,6,2,10,8,9};
		while (step !=33)
		  {
		GPIO_PORTD_DATA_R = (motor_steps[count & 7] & 0x0F) | (GPIO_PORTD_DATA_R & 0xF0);
		count++;
		step++;
		delay(20);
	  }
}


void step_backword(void)
{
		unsigned int step = 0;
	unsigned int motor_steps[HALF_WAVE_STEPS] = {1,5,4,6,2,10,8,9};
		while (step !=33)
		  {
		GPIO_PORTD_DATA_R = (motor_steps[count & 7] & 0x0F) | (GPIO_PORTD_DATA_R & 0xF0);
		count--;
		step++;
		delay(20);
	  }	
}
