#include <at89c51RC2.h>
#include "timer0.h"
#include "key.h"
#include <intrins.h>

unsigned char KeyNumber,LEDMode;

void main()
{
	Timer0_Init();
	P2=0xFE;
	while(1)
	{
		KeyNumber=Key();
		if(KeyNumber)
		{
			if(KeyNumber==1)
			{
				LEDMode++;
				if(LEDMode>1)
					LEDMode=0;
			}
		}
		
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	T0Count++;
	if(T0Count>500)   //1s计时
	{
		T0Count=0;
		if(LEDMode==0)
			P2=_crol_(P2,1);
		if(LEDMode==1)
			P2=_cror_(P2,1);
	}
}