#include <at89c51RC2.h>
#include "LCD1602.h"

int main()
{
	LCD_Init();
	LCD_ShowChar(1,1,'A');
	LCD_ShowString(1,3,"91AV");
	while(1)
	{
		
	}
}