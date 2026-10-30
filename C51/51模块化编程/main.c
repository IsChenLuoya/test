#include <at89c51RC2.h>
#include "Delay.h"
#include "NIXIE.h"
int main()
{
	while(1)
	{
		Nixie(1,3);
		Delay(500);
		Nixie(1,-1);
		Delay(500);
	}
}