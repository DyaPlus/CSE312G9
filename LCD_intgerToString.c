#include "lcd.h"
#include "MCAL.h"
#include "delay.h"

void LCD_intgerToString(int data)
{
  char buff[16]; /* String to hold the ascii result */
  itoa(data,buff,10); /* 10 for decimal */
  LCD_displayStringRowColumn(0,7,buff);
}