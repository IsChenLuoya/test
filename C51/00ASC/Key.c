#include <at89c51RC2.h>
#include "delay.h"
#include "Buzzer.h"


unsigned char Key()
{
	unsigned int time=0,flag=0;
	if(P3_1==0){Delay(20);while(P3_1==0);Delay(20);return 1;}
	if(P3_0==0){Delay(20);while(P3_0==0);Delay(20);return 2;}
	if(P3_2==0)
	{
		time=0;
		Delay(20);
		while(P3_2==0)
		{
			time++;
			if(time>20000)
			{
				Buzzer_Time(100);
				Delay(100);
				Buzzer_Time(100);
				while(P3_2==0);
				return 5;
			}
		}
		Delay(20);
		return 3;
	}
	if(P3_3==0)
	{
		time=0;
		Delay(20);
		while(P3_3==0)
		{
			time++;
			if(time>20000)
			{
				Buzzer_Time(100);
				Delay(100);
				Buzzer_Time(100);
				while(P3_3==0);
				return 6;
			}
		}
		Delay(20);
		return 4;
	}
	return 0;
}
