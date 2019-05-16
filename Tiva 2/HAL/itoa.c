#include "lcd.h"
#include "Port.h"
#include "DIO.h"
#include "delay.h"

void itoa (int data,char buffer[] , int base)
{
	int x=data/100;
	data=data-x*100;
	char c=(int)'0'+x;
	buffer[0]=c;
	x=data/10;
	c=(int)'0'+x;
	buffer[1]=c;
	data=data-x*10;
	x=data;
	c=(int)'0'+x;
	buffer[2]=c;
}