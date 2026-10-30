#include <at89c51RC2.h>
#include "Delay.h"

sbit RCK=P3^5;
sbit SCK=P3^6;
sbit SER=P3^4;

void _74H595_WriteByte(unsigned char byte)
{
	unsigned int i;
	for(i=0;i<8;i++)
	{
		SER=byte&(0x80>>i);
		SCK=1;
		SCK=0;
	}
	RCK=1;
	RCK=0;
}

void MatrixLED_ShowColumn(unsigned char column,Data)
{
	_74H595_WriteByte(Data);
	P0=~(0x80>>(column-1));
	Delay(1);
	P0=0xFF;
}

void main()
{
	SCK=0;
	RCK=0;
	
	while(1)
	{
		MatrixLED_ShowColumn(1,0x3c);//3c 42 a9 85 85 a9 42 3c
		MatrixLED_ShowColumn(2,0x42);
		MatrixLED_ShowColumn(3,0xa9);
		MatrixLED_ShowColumn(4,0x85);
		MatrixLED_ShowColumn(5,0x85);
		MatrixLED_ShowColumn(6,0xa9);
		MatrixLED_ShowColumn(7,0x42);
		MatrixLED_ShowColumn(8,0x3c);
	}
}