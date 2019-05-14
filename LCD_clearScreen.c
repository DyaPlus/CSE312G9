
#include "lcd.h"
#include "MCAL.h"
#include "delay.h"



void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); //clear display 
}
