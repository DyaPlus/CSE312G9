
#include "lcd.h"
#include "MCAL.h"
#include "delay.h"
void LCD_init(void)
{
	Port_SetPinDirection(PORT_D_INDEX, PORT_LOWER, PORT_PIN_OUT); /* Configure the data port as output port */
	Port_SetPinDirection(PORT_A_INDEX, PORT_UPPER, PORT_PIN_OUT); /* Configure the data port as output port */
	Port_SetPinDirection(PORT_F_INDEX,LOWER_3_PINS,PORT_PIN_OUT); /* Configure the control pins(E,RS,RW) as output pins */
	
	delay(200);
	
	
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
	delay(20);
	
	LCD_sendCommand(DISPLAY_OFF_CURSOR_OFF); 
	delay(20);
	
	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
	delay(20);
	
	LCD_sendCommand(SHIFT_CURSOR_TO_RIGHT); 
	delay(20);
	
	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	delay(20);
}