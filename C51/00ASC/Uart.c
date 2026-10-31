#include <at89c51RC2.h>

void Uart1_Init(void)	//4800bps@11.0592MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x40;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器时钟12T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xF4;			//设置定时初始值
	TH1 = 0xF4;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
	EA=1;
}

void Uart_SendByte(unsigned char byte)
{
	ES=0;
	SBUF=byte;
	while(TI==0);
	TI=0;
	ES=1;
}

void Uart_SendString(unsigned char code *str)
{
  while(*str!='\0')
  {
      Uart_SendByte(*str);
      str++;
  }
}


/*串口中断函数模板
void UART_Routine() interrupt 4
{
	if(RI==1)
	{
		=SBUF;
		RI=0;
	}
}
*/