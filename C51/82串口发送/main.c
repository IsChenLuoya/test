#include <at89c51RC2.h>
#include "Delay.h"
#include "UART.h"

unsigned char time;

void main()
{
	Uart1_Init();
	while(1)
	{
		
	}
}

void UART_Routine() interrupt 4
{
	if(RI==1)
	{
		P2=~SBUF;
		Uart_SendByte(SBUF);
		RI=0;
	}
}