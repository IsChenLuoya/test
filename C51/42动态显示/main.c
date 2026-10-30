#include <at89c51RC2.h>
#include <intrins.h>

void Delay(int k)	//@11.0592MHz
{
	unsigned char data i, j;
  while(k--)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

void Nixie(unsigned char Location,Number)
{
	switch(Location)
	{
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
	}
	switch(Number)
	{
		case 0:P0=0x3F;break;
		case 1:P0=0x06;break;
		case 2:P0=0x5B;break;
		case 3:P0=0x4F;break;
		case 4:P0=0x66;break;
		case 5:P0=0x6D;break;
		case 6:P0=0x7D;break;
		case 7:P0=0x07;break;
		case 8:P0=0x7F;break;
		case 9:P0=0x6F;break;
	}
	Delay(1);
}
int main()
{
	while(1)
	{
		Nixie(1,1);
		Nixie(2,2);
		Nixie(3,3);
	}
}