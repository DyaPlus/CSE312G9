#include "lcd.h"
#include "Port.h"
#include "DIO.h"
#include "delay.h"


void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}