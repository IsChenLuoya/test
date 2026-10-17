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

int main()
{	
	while(1)
	{
		if(P3_1==0)
		{
			delay(20);
			while(P3_1==0);
			delay(20);
			P2_0=~P2_0;
		}
	}
}

