#include <at89c51RC2.h>
#include "Delay.h"
#include "UART.h"

unsigned char time;

void main()
{
	Uart1_Init();
	while(1)
	{
		Uart_SendByte(time);
		time++;
		Delay(1000);
	}
}