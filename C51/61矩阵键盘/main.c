#include <at89c51RC2.h>
#include "DELAY.H"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char kn;
void main()
{
	LCD_Init();
	while(1)
	{
		kn=MatrixKey();
		LCD_ShowString(1,1,"91AV");
		if(kn)
		{
			LCD_ShowNum(2,1,kn,2);
		}
	}
}