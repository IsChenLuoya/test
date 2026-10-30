#include <at89c51RC2.h>
#include "Delay.h"

void Init()
{
	  P2_0=0;Delay(100);
		P2_1=0;Delay(100);
		P2_2=0;Delay(100);
		P2_3=0;Delay(100);
		P2_4=0;Delay(100);
		P2_5=0;Delay(100);
		P2_6=0;Delay(100);
		P2_7=0;Delay(100);
		P2=0xFF;Delay(250);
		P2=0x00;Delay(250);
		P2=0xFF;Delay(250);
		P2=0x00;Delay(250);
		P2=0xFF;
}
	