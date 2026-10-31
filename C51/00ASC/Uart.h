#ifndef __UART_H__
#define __UART_H__

void Uart1_Init(void);
void Uart_SendByte(unsigned char byte);
void Uart_SendString(unsigned char code *str);

#endif