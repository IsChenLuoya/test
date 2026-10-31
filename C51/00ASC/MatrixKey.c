#include <at89c51RC2.h>

unsigned char MatrixKey(void)
{
	static unsigned char Lastraw  = 0;   
	static unsigned char stable   = 0;   
	static unsigned char count    = 0;   
	unsigned char raw = 0;
	
	P1 = 0xFF; 
	P1_3 = 0;
  if(P1_7 == 0) raw = 1;
	else if(P1_6 == 0) raw = 5;
  else if(P1_5 == 0) raw = 9; 
	else if(P1_4 == 0) raw = 13;
  if(raw == 0) 
		{ 
			P1 = 0xFF; 
			P1_2 = 0;
      if(P1_7 == 0) raw = 2;
			else if(P1_6 == 0) raw = 6;
      else if(P1_5 == 0) raw = 10;
  		else if(P1_4 == 0) raw = 14; 
		}
	if(raw == 0) 
		{ 
			P1 = 0xFF;
			P1_1 = 0;
      if(P1_7 == 0) raw = 3;
			else if(P1_6 == 0) raw = 7;
      else if(P1_5 == 0) raw = 11;
		  else if(P1_4 == 0) raw = 15; 
		}
	if(raw == 0) 
		{ 
			P1 = 0xFF; 
			P1_0 = 0;
      if(P1_7 == 0) raw = 4; 
			else if(P1_6 == 0) raw = 8;
      else if(P1_5 == 0) raw = 12; 
		  else if(P1_4 == 0) raw = 16; 
		}
	P1 = 0xFF;
	if(raw==Lastraw)
	{
		if(count<2)
			count++;
	}
	else
	{
		Lastraw=raw;
		count=0;
		return 0;
	}
	if(count<2)
		return 0;
	if(raw!=stable)
	{
		stable=raw;
		if(raw!=0)
			return raw;
	}
	return 0;
}


