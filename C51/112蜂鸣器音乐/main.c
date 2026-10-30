#include <at89c51RC2.h>
#include "Delay.h"
#include "Timer0.h"
#include "Key.h"

sbit Buzzer=P2^5;

unsigned char Keynum;
unsigned int i;
unsigned int FreqTable[]={
	0,
	63628,63731,63835,63928,64021,64103,64185,64260,64331,64400,64463,64528,
	64580,64633,64684,64732,64777,64820,64860,64898,64934,64968,65000,65030,
	65058,65085,65110,65134,65157,65178,65198,65217,65235,65252,65268,65283,
};

void main()
{
	Timer0_Init();
	while(1)
	{
		Keynum=Key();
		if(Keynum)
		{
			if(Keynum==1 && i<34)
				i++;
			else if(Keynum==2 && i!=0)
				i--;
		}
	}
}

void Timer0_Routine() interrupt 1
{
	TL0 = (FreqTable[i])%256;				//设置定时初始值
	TH0 = (FreqTable[i])/256;				//设置定时初始值
	Buzzer=!Buzzer;
}