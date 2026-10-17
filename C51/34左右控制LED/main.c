#include <at89c51RC2.h>
#include <intrins.h>
void delay(unsigned int t)	//@11.0592MHz
{
	unsigned char data i, j;
	while(t)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		t--;
	}
}

unsigned char n;

void main()
{
	P2_0=0;
	while(1)
	{
		if(P3_0==0)
		{
			delay(20);
			while(P3_0==0);
			delay(20);
			n++;
			if(n>=8)
				n=0;
			P2=~(0x01<<n);
		}
		if(P3_1==0)
		{
			delay(20);
			while(P3_1==0);
			delay(20);
			if(n==0)
				n=7;
			else
				n--;
			P2=~(0x01<<n);
		}
	}
}