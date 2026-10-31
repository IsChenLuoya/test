#include <at89c51RC2.h>
#include "Delay.h"
#include "Nixie.h"
#include "MatrixLED.h"
#include "Timer0.h"
#include "Key.h"
#include "Uart.h"
#include "Init.h"
#include "Buzzer.h"
#include "MatrixKey.h"

unsigned char mode;
unsigned char Keynum,KeyFlag=0;
unsigned char confirm=0,confirm1=0;
unsigned char uartopen;
unsigned char term=10;
unsigned char Keynum2;
char key1=1,key5=1;
unsigned char lightud=50;
unsigned char j;
unsigned char KeyScan;



unsigned char code Animation[]={
0x3F,0x44,0x84,0x84,0x44,0x3F,0x00,0x00,0x70,0x89,0x89,0x89,0x89,0x06,0x00,0x00,
0x7E,0x81,0x81,0x81,0x81,0x81,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF2,0x91,
0x91,0x91,0x8E,0x00,0x00,0x00,0x43,0x85,0x89,0x89,0x71,0x00,0x00,0x00,0x7E,0x85,
0x89,0x91,0xA1,0x7E,0x00,0x00,0x70,0x88,0x84,0xC2,0x21,0xC2,0x84,0x88,0x70,0x00,
0x3F,0x44,0x84,0x84,0x44,0x3F,0x00,0x00
};


void ev(unsigned int t)
{
	while(t--);
}


void main()
{
	MatrixLED_Init();
	Timer0_Init();
	Uart1_Init();
	_74H595_WriteByte(0x00);
	Nixie(1,-1);
	Init();
	mode=1;
	while(1)
	{
		
		if(KeyFlag==2)
		{
			P2_0=1;
			SCON = 0x40;
			KeyFlag=0;
		}
		else if(KeyFlag==3)
		{
			P2_0=0;
			SCON = 0x50;
			KeyFlag=0;
		}
		if(confirm==1)                                             //模式确认
		{
			Nixie(1,mode);
			Buzzer_Time(100);
			Delay(100);
			Buzzer_Time(100);
			switch(mode)
			{
				case 1:
				{
					break;
				}
				case 2:
				{
					break;
				}
				case 3:
				{
					unsigned char i,Offset=3,Count=0;
					while(1)
					{
						if(KeyFlag==4)
						{
							confirm=0;
							_74H595_WriteByte(0x00);
							Buzzer_Time(100);
							Delay(100);
							Buzzer_Time(100);
							KeyFlag=0;
							break;
						}
						for(i=0;i<8;i++)
						{
							MatrixLED_ShowColumn(i,Animation[i+Offset]);
						}
						Count++;
						if(Count>5)
						{
							Count=0;
							Offset++;
							if(Offset>63)
							{
								Offset=0;
							}
						}
					}
					break;
				}
				case 4:                                                  //PWM
				{
					confirm1=1;
					while(1)
					{
						Keynum2=MatrixKey(); 
						if(KeyFlag==4)
						{
							confirm=0;
							confirm1=0;
							P2=0xFF;
							Buzzer_Time(100);
							Delay(100);
							Buzzer_Time(100);
							KeyFlag=0;
							break;
						}
						if(Keynum2)                     // 矩阵键调音调
						{
							unsigned char k2=Keynum2;
							Keynum2=0;
							if(k2==1) key1=-key1;
							else if(k2==2&&term > 2)  term-=1;
							else if(k2==3&&term < 20) term+=1;
							else if(k2==5) key5=-key5;
							else if(k2==6) lightud+=5;
							else if(k2==7) lightud-=5;
						}
						if(key1==1)
						Buzzer_Control(term);
					}	
					break;
			 }
		  }
	  } 
		if(confirm==0)                               //菜单选择
		{
			  Nixie(1,mode);
				Delay(500);
			if(confirm==0)
			{
				Nixie(1,-1);
				Delay(500);
			}
				if(KeyFlag==1)
				{
					unsigned char k=Keynum;
					KeyFlag=0;
					if(k==1)
					{
						if(mode>1) mode--;
						else mode=4;
					}
					else if(k==2)
					{
						if(mode<4) mode++;
						else mode=1;
					}
				}
		 }	
		
	}
}


void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	static unsigned char KeyScan;
	static unsigned char PWMCount;
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	T0Count++;
	
	if(confirm1==1&&key5==1)
	{
		PWMCount++;
		if(PWMCount>=20) 
			PWMCount=0;
		if(PWMCount<(lightud/5))
		{
			P2_0=0;
			P2_1=0;
			P2_2=0;
			P2_3=0;
			P2_4=0;
			P2_6=0;
			P2_7=0;
		}
		else
		{
			P2_0=1;
			P2_1=1;
			P2_2=1;
			P2_3=1;
			P2_4=1;
			P2_6=1;
			P2_7=1;
		}
	}
	else if(confirm1==1&&key5==-1)
	{
			P2_0=1;
			P2_1=1;
			P2_2=1;
			P2_3=1;
			P2_4=1;
			P2_6=1;
			P2_7=1;
	}
	else
	{
		PWMCount = 0;
	}
	
	
	if(T0Count>=10)  
    {
      T0Count=0;
			KeyScan=Key();
			if(KeyScan==1||KeyScan==2)
			{
				 Keynum=KeyScan;
				 KeyFlag=1;
			}
			else if(KeyScan==3)
			{
				 Keynum=KeyScan;
				 confirm=1;
				 KeyFlag=1;
			}
			else if(KeyScan==5)
			{
				 KeyFlag=2;
			}
			else if(KeyScan==6)
			{
				 KeyFlag=3;
			}
			else if(KeyScan==4)
			{
				 KeyFlag=4;
			}
		}
}
