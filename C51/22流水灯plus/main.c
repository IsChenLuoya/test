#include <at89c51RC2.h>
#include <INTRINS.H>

void Delay1ms(unsigned int xms)	//@11.0592MHz
{
	unsigned char data i, j;
	while(xms)
	{
		_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
	xms--;
	}
}

int main()
{
	while(1)
	{
		P2=0xFE;
		Delay1ms(100);
		P2=0xFD;
		Delay1ms(100);
		P2=0xFB;
		Delay1ms(100);
		P2=0xF7;
		Delay1ms(100);
		P2=0xEF;
		Delay1ms(100);
		P2=0xDF;
		Delay1ms(100);
		P2=0xBF;
		Delay1ms(100);
		P2=0x7F;
		Delay1ms(100);
	}	
}
