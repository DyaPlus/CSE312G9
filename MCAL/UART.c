#include "UART.h"

#define IBRD (F_CPU/(scale*BAUD_RATE))
#define FBRD (int)((IBRD-(int)IBRD)*64+0.5)
#define GPIO_PA10_M 0x03

void UART7_Init(void){
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R7;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
	
	UART7_CTL_R &= ~UART_CTL_UARTEN;
	UART7_IBRD_R = 520;    
  UART7_FBRD_R = 53;
	UART7_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
	UART7_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
	GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;   			// Unlock PortF Commit register  
  GPIO_PORTE_CR_R |= GPIO_PA10_M;          // Allow changes to PF321       
	GPIO_PORTE_AFSEL_R |= GPIO_PA10_M;
	GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFFFFFF00) | (GPIO_PCTL_PE1_U7TX | GPIO_PCTL_PE0_U7RX);
	GPIO_PORTE_DEN_R |= GPIO_PA10_M;
	GPIO_PORTE_AMSEL_R &= ~GPIO_PA10_M;   
}
//.........................//
uint8_t UART7_Available(void){
	return ((UART7_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
}
//.........................//
void UART7_sendByte(const uint8_t data){

	while((UART7_FR_R&UART_FR_TXFF) != 0) {};
		UART7_DR_R = data;

}
//.........................//
uint8_t UART7_recieveByte(void){

	while(UART7_Available() != 1);
	return (uint8_t)(UART7_DR_R&0xFF);
}
//.........................//
void UART7_sendString(const uint8_t *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		UART7_sendByte(Str[i]);
		i++;
	}
}
//..........................//
void UART7_receiveString(uint8_t *Str)
{
	uint8_t i = 0;
	Str[i] = UART7_recieveByte();
//	UART_sendByte(Str[i]);
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART7_recieveByte();
	//	UART_sendByte(Str[i]);
	}
	Str[i] = '\0';
}
//........................................................................//

void UART0_Init(void){
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
	UART0_CTL_R &= ~UART_CTL_UARTEN;
	UART0_IBRD_R = IBRD;
  UART0_FBRD_R = FBRD;
	UART0_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
	UART0_CTL_R |= UART_CTL_UARTEN;
	GPIO_PORTA_AFSEL_R |= GPIO_PA10_M;
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00) | (GPIO_PCTL_PA1_U0TX | GPIO_PCTL_PA0_U0RX);
	GPIO_PORTA_DEN_R |= GPIO_PA10_M;
}
//.........................//
uint8_t UART0_Available(void){
	return ((UART0_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
}
//.........................//
void UART0_sendByte(const uint8_t data){

	while((UART0_FR_R&UART_FR_TXFF) != 0);
		UART0_DR_R = data;

}
//.........................//
uint8_t UART0_recieveByte(void){

	while(UART0_Available() != 1);
	return (uint8_t)(UART0_DR_R&0xFF);
}
//.........................//
void UART0_sendString(const uint8_t *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		UART0_sendByte(Str[i]);
		i++;
	}
}
//..........................//
void UART0_receiveString(uint8_t *Str)
{
	uint8_t i = 0;
	Str[i] = UART0_recieveByte();
	UART0_sendByte(Str[i]);
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART0_recieveByte();
		UART0_sendByte(Str[i]);
	}
	Str[i] = '\0';
}

