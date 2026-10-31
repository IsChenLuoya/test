#include <at89c51RC2.h>
#include <Intrins.h>
#include "Delay.h"

sbit Buzzer=P2^5;

void Buzzer_Delay500us(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 227;
	while (--i);
}

void Buzzer_Delay100us(unsigned int term)	//@11.0592MHz
{
	unsigned char data i;
	while(term>0)
	{
		_nop_();
		i = 43;
		while (--i);
		term--;
	}
	
}


void Buzzer_Time(unsigned int ms)
{
	unsigned int i;
	for(i=0;i<ms*2;i++)
			{
				Buzzer=!Buzzer;
				Buzzer_Delay500us();
			}
}


void Buzzer_Control(unsigned int term)
{	
	unsigned int total=100/term;
  while (total--)
  {
     Buzzer = !Buzzer;
     Buzzer_Delay100us(term);
  }
}