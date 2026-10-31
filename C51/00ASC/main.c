#include <at89c51RC2.h>
#include <string.h>
#include <intrins.h>
#include "Delay.h"
#include "Nixie.h"
#include "MatrixLED.h"
#include "Timer0.h"
#include "Key.h"
#include "Uart.h"
#include "Init.h"
#include "Buzzer.h"
#include "MatrixKey.h"
#include "LCD1602.h"
#include "Calculate.h"
#include "SetLED.h"

unsigned char mode;
unsigned char Keynum,KeyFlag=0;
unsigned char confirm=0,confirm1=0;
unsigned char uartopen;
unsigned char term=10;
unsigned char Keynum2;
char key1=1,key5=1,key01=0;
unsigned char lightud=50;
unsigned char j;
unsigned char KeyScan;
unsigned lit;
unsigned LEDmode=1,LEDmode2=0,LEDmode3=0,LEDmode3Flag=0;
unsigned char LED0[8];
char LEDi;
unsigned char LEDNum=0;
unsigned char t;
unsigned char stayCnt=0;
unsigned char LEDflag=0;
unsigned char covered=0;
unsigned char uart_data=0;



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
			SCON = 0x40;
			KeyFlag=0;
			ES=0;
		}
		else if(KeyFlag==3)
		{
			SCON = 0x50;
			ES=1;
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
					unsigned char iLED=0;
					Uart_SendString("模式一进入");
					lit=500;
					if(LEDNum == 0)
					{
							LEDNum = 8;
							for(t = 0; t < 8; t++)
							{
									 LED0[t] = (1u << t); 
							}
					}
					stayCnt=0;
					LEDflag=0;
					P2 = ~LED0[LEDi];
					key01=1;
					while(1)
					{
						if(KeyFlag==4)
						{
							Uart_SendString("模式一退出");
							confirm=0;
							key01=0;
							P2=0xFF;
							_74H595_WriteByte(0x00);
							LEDmode=1;
							LEDmode2=0;
							LEDmode3=0;
							Buzzer_Time(100);
							Delay(100);
							Buzzer_Time(100);
							KeyFlag=0;
							break;
						}
						if(LEDmode3==0)
						{
							Keynum2=MatrixKey();
							if((Keynum2==1||Keynum2==2)&&LEDmode3==0)
							{
								unsigned char k2=Keynum2;
								Keynum2=0;
								if(k2==2){lit+=50;Uart_SendString("减速");}
								else if(k2==1&&lit>50){lit-=50;Uart_SendString("加速");}
							}
							if(Keynum2 &&LEDmode3==0)
							{
								unsigned char k2=Keynum2;
								Keynum2=0;
								if(k2==3){if(LEDmode==1)LEDmode=2;else if(LEDmode==2)LEDmode=1;Uart_SendString("改序");}
								else if(k2==4)
								{
									Uart_SendString("回灯");
									if(LEDmode2==0)
									{
										if(LEDmode==1)
											LEDmode2=1;
										else if(LEDmode==2)
											LEDmode2=2;
									}
									else if(LEDmode2)
										LEDmode2=0;
								}
								else if(k2==5)
								{
									Uart_SendString("编辑模式");
									LEDmode3Flag=1;
									LEDmode=0;
									LEDmode2=0;
									P2=0x00;
									Delay(1000);
									P2=0xFF;
									LEDmode3=1;
									LEDNum=0;
									LEDi=0;
									stayCnt=0;
									LEDflag=0;
									covered=0;
								}
							}
						}							
						else if(LEDmode3==1)
						{
								unsigned char g=MatrixKey_LEDRaw();

								if(g!=0)
								{
										Delay(20);
										g|=MatrixKey_LEDRaw();

										if(LEDNum<8)
										{
												LED0[LEDNum]=g;
												LEDNum++;
												covered|=g;

												P2&=~g;
										}

										while(MatrixKey_LEDRaw()!=0);
										Delay(20);

										if(covered==0xFF)
										{
												P2=0xFF;
												LEDmode3Flag=0;
												LEDmode=1;
												LEDmode3=0;
												LEDi=0;
												stayCnt=0;
												LEDflag=0;
										}
								}
						}
					}
					
					break;
				}
				case 2:
				{	
					long sum=0;
					unsigned int Num=0;
					unsigned char n=1;
					unsigned char n2=0;
					xdata unsigned long a[8];
					xdata unsigned char op[7];
					Uart_SendString("模式二进入");
					memset(op,0,sizeof(op));
					memset(a,0,sizeof(a));
					LCD_Init();
					while(1)
					{
						if(KeyFlag==4)
						{
							Uart_SendString("模式二退出");
							confirm=0;
							_74H595_WriteByte(0x00);
							Buzzer_Time(100);
							Delay(100);
							Buzzer_Time(100);
							KeyFlag=0;
							P2=0xFF;
							break;
						}
						Keynum2=MatrixKey(); 
						if(Keynum2)
						{
							unsigned char k2=Keynum2;
							Keynum2=0;
							if(k2==2){LCD_ShowNum(1,n,1,1);n++;a[n2]=a[n2]*10+1;}
							else if(k2==3){LCD_ShowNum(1,n,2,1);n++;a[n2]=a[n2]*10+2;}
							else if(k2==4){LCD_ShowNum(1,n,3,1);n++;a[n2]=a[n2]*10+3;}
							else if(k2==5){LCD_ShowNum(1,n,4,1);n++;a[n2]=a[n2]*10+4;}
							else if(k2==6){LCD_ShowNum(1,n,5,1);n++;a[n2]=a[n2]*10+5;}
							else if(k2==7){LCD_ShowNum(1,n,6,1);n++;a[n2]=a[n2]*10+6;}
							else if(k2==8){LCD_ShowNum(1,n,7,1);n++;a[n2]=a[n2]*10+7;}
							else if(k2==9){LCD_ShowNum(1,n,8,1);n++;a[n2]=a[n2]*10+8;}
							else if(k2==10){LCD_ShowNum(1,n,9,1);n++;a[n2]=a[n2]*10+9;}
							else if(k2==1){LCD_ShowNum(1,n,0,1);n++;a[n2]=a[n2]*10;}
							else if(k2==11)
							{
								LCD_Init();
								n=1;
								n2=0;
								memset(op, 0, sizeof(op));
								memset(a, 0, sizeof(a));
							}
							
							else if(k2==13)
							{
								LCD_ShowChar(1,n,'+');
								op[n2]=1;
								n2++;
								n++;
							}
							else if(k2==14)
							{
								LCD_ShowChar(1,n,'-');
								op[n2]=2;
								n2++;
								n++;
							}
							else if(k2==15)
							{
								LCD_ShowChar(1,n,'*');
								op[n2]=3;
								n2++;
								n++;
							}
							else if(k2==16)
							{
								LCD_ShowChar(1,n,'/');
								op[n2]=4;
								n2++;
								n++;
							}
							else if(k2==12)
							{
								LCD_ShowChar(1,n,'=');
								LCD_ShowSignedLongNum(2,1,calculate(a,op),16);
							}
						}
					}
					break;	
				}
				case 3:
				{
					unsigned char i,Offset=3,Count=0;
					Uart_SendString("模式三进入");
					while(1)
					{
						if(KeyFlag==4)
						{
							Uart_SendString("模式三退出");
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
					Uart_SendString("模式四进入");
					while(1)
					{
						Keynum2=MatrixKey(); 
						if(KeyFlag==4)
						{
							Uart_SendString("模式四退出");
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
							if(k2==1) {key1=-key1;Uart_SendString("蜂鸣器开关");}
							else if(k2==2&&term > 2)  {term-=1;Uart_SendString("频率升");}
							else if(k2==3&&term < 20) {term+=1;Uart_SendString("频率降");}
							else if(k2==5) {key5=-key5;Uart_SendString("呼吸灯开关");}
							else if(k2==6) {lightud+=5;Uart_SendString("亮度升");}
							else if(k2==7) {lightud-=5;Uart_SendString("亮度降");}
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
	static unsigned int T0Count1;
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
	
	if(key01==1 && LEDmode3Flag==0 && LEDNum > 0)
	{
			T0Count1++;
			if(T0Count1>=lit)
			{
					T0Count1=0;
					P2|=LED0[LEDi];
					if(LEDmode==1&&LEDmode2==0)
					{
							LEDi++;
							if(LEDi>=LEDNum) LEDi=0;
					}
					else if(LEDmode==2&&LEDmode2==0)    
					{
							if(LEDi==0) LEDi=LEDNum-1;
							else LEDi--;
					}
					else if(LEDmode2==1)                 
					{
							if(LEDi==LEDNum-1) LEDflag=1;
							else if(LEDi == 0) LEDflag=0;
							if(LEDflag) LEDi--;
							else LEDi++;
					}
					else if(LEDmode2==2)              
					{
							if(LEDi==LEDNum-1) LEDflag=0;
							else if(LEDi==0) LEDflag=1;
							if(LEDflag) LEDi++;
							else LEDi--;
					}

					P2&=~LED0[LEDi];  
			}
	}
						
						
						
						
											
	if(T0Count>=10)  
    {
      T0Count=0;
			KeyScan=Key();
			if(KeyScan==0)
			{
				KeyScan=uart_data;
				uart_data=0;
			}
			
			
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




void UART_Routine() interrupt 4
{
	if(RI==1)
	{
		uart_data=SBUF;
		RI=0;
	}
	if(TI==1)
  {
    TI=0;
  }
}

