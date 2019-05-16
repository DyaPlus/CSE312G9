
#include "lcd.h"
#include "Port.h"
#include "DIO.h"
#include "delay.h"



void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); //clear display 
}
