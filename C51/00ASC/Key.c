#include <at89c51RC2.h>
#include "delay.h"
#include "Buzzer.h"

unsigned char Key(void)
{
    static unsigned char lastraw=0;
    static unsigned char stable=0;
    static unsigned char count=0;
    static unsigned int  hold=0;
    static unsigned char Long=0;
    unsigned char raw=0;
	
	
    if(P3_1==0) raw=1;
    else if(P3_0==0) raw=2;
    else if(P3_2==0) raw=3;
    else if(P3_3==0) raw=4;
	
	
    if(raw==lastraw)
    {
        if(count<2) count++;
    }
    else
    {
        lastraw=raw;
        count=0;
        return 0;
    }
    if(count<2) return 0;
		
		
    if(raw!=stable)
    {
			  unsigned char old=stable;
        stable=raw;
        hold=0;
			if(raw!=0)
			{
				if(raw==1||raw==2) 
					return raw;
				return 0;
			}
      else
			{

				if(!Long&&(old==3||old==4))
				{
					Long=0;
					return old;
				}
				Long=0;
				return 0;
      }
				
    }

    if((stable==3||stable==4)&&!Long)
    {
        if(++hold>100)
        {
            Long=1;
					if(stable==3)
            return 5;
					else if(stable==4)
            return 6;
        }
    }

    return 0;
}