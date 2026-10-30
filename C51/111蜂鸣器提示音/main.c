#include <at89c51RC2.h>
#include "Delay.h"
#include "Nixie.h"
#include "Key.h"
#include "Buzzer.h"

unsigned char Keynumber;

void main()
{
	Nixie(1,0);
	while(1)
	{
		Keynumber=Key();
		if(Keynumber)
		{
			Buzzer_Time(1000);
			Nixie(1,Keynumber);
		}
	}
}