#include <stm32f4xx.h>
#include "lcd.h"
#include "usart_dt.h"
#include "touch.h"
#include "touchevent.h"
#include "status.h"
#include "delay.h"
u8 Button_Release;

unsigned char Button_Event(u16 CoordiX, u16 CoordiY, u8 *ChWord,u16 Length, u16 Width,u16 Touch_X,u16 Touch_Y, u8 FontStyle, u32 FontColor, u32 BackColor)
{
	
	if(Touch_X>=CoordiX&&Touch_Y>=CoordiY&&Touch_X<=CoordiX+Length&&Touch_Y<=CoordiY+Width)
	{
		Button_Touched(CoordiX,CoordiY, ChWord, Length,Width,ASCII1206,FontColor, FontColor);
		Button_Release=1;
	}
	
	if(Button_Release==1)
	{
		Delay(1500);		
		Button(CoordiX,CoordiY, ChWord, Length,Width,ASCII1206,FontColor, BackColor);
		Button_Release=0;
		return 1;
	}
}

unsigned char MenuButton_Event(u16 CoordiX, u16 CoordiY, u8 *ChWord,u16 Length, u16 Width,u16 Touch_X,u16 Touch_Y, u8 FontStyle, u32 FontColor, u32 BackColor)
{
	if(Touch_X>=Sp3D_X-60&&Touch_Y>=Sp3D_Y-70&&Touch_X<=Sp3D_X+110&&Touch_Y<=Sp3D_Y-55)
	{
		if(Touch_X>=CoordiX&&Touch_Y>=CoordiY&&Touch_X<=CoordiX+Length&&Touch_Y<=CoordiY+Width)
		{
			Button_Touched(CoordiX,CoordiY, ChWord, Length,Width,ASCII1206,FontColor, FontColor);
			return 1;
		}
		else 
			{Button(CoordiX,CoordiY, ChWord, Length,Width,ASCII1206,FontColor, BackColor);
			return 0;
			}
	}	
}

u8 _3dstatus_Flag=0;
u8 Campus_Flag=0;
u8 WaveForm_Flag=0;

void Touch_Event( u16 Touch_X ,u16 Touch_Y)
{
		if(Button_Event(63,193,"Reset",35,35,Touch_X,Touch_Y,ASCII1206,Yellow, Black)==1)
		{Uart1_Put_Char(0x12);Delay(5000);}
		if(Button_Event(263,193,"Reset",35,35,Touch_X,Touch_Y,ASCII1206,Yellow, Black)==1)
		{Uart1_Put_Char(0x34);Delay(5000);}
		if(MenuButton_Event(Sp3D_X-60,Sp3D_Y-70, "3D Status", 60,15,Touch_X,Touch_Y,ASCII1206,Blue, Black)==1)
		{_3dstatus_Flag=1;Campus_Flag=0;WaveForm_Flag=0;}
		if(MenuButton_Event(Sp3D_X,Sp3D_Y-70, " Campus ", 50,15,Touch_X,Touch_Y,ASCII1206,Blue, Black)==1)
		{Campus_Flag=1;_3dstatus_Flag=0;WaveForm_Flag=0;}
		if(MenuButton_Event(Sp3D_X+50,Sp3D_Y-70, " WaveForm", 60,15,Touch_X,Touch_Y,ASCII1206,Blue, Black)==1)
		{WaveForm_Flag=1;_3dstatus_Flag=0;Campus_Flag=0;}
}