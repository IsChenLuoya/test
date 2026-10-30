#include <at89c51RC2.h>

sbit LED=P2^0;

void ev(unsigned int t)
{
	while(t--);
}


void main()
{
	unsigned char Time,i;
	while(1)
	{
		for(Time=0;Time<100;Time++)
		{
			for(i=0;i<20;i++)
			{
				LED=0;
				ev(Time);
				LED=1;
				ev(100-Time);
			}
		}
		for(Time=100;Time>0;Time--)
		{
			for(i=0;i<20;i++)
			{
				LED=0;
				ev(Time);
				LED=1;
				ev(100-Time);
			}
		}
	}
}