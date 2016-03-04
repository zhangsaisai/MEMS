#include "main.h"
#include "usart_dt.h"
#include "touchevent.h"
#include "status.h"

void Window_Init()
{
	LCD_Clear(Black);
	TFT_PutStr(10,12, " Dolphin Mirco-Quadrotor ", ASCII1608,Blue, Black);	
	_3dstatus_Window(Sp3D_X,Sp3D_Y,Sp3D_R); 
	RC_Window(10,10);
	Angle_Window(10,10);
	ACCGRYO_Window(10,10);
	BAT_Window(10,10);
	Moto_Window(10,10);

}
void FUN_Select()
{
	u8 static FUN=0;	
	if(Campus_Flag)
	{
	TFT_DrawRectangleFull(Sp3D_X-56,Sp3D_Y-48, 167,110,Black);
	Campus_Window(Campus_X,Campus_Y);
	Campus_Flag=0;
	FUN=1;
	}
	if(_3dstatus_Flag)	
	{
	TFT_DrawRectangleFull(Sp3D_X-56,Sp3D_Y-48, 167,110,Black);
	_3dstatus_Window(Sp3D_X,Sp3D_Y,Sp3D_R);
	FUN=0;
	_3dstatus_Flag=0;
	 }
	
	if(WaveForm_Flag)
	{
	TFT_DrawRectangleFull(Sp3D_X-56,Sp3D_Y-48, 167,110,Black);
	WaveForm_Window(Sp3D_X,Sp3D_Y);
	WaveForm_Flag=0;
	FUN=2;
	}
	
	if(FUN==0)_3dstatus_Data(Sp3D_X,Sp3D_Y,Sp3D_R);	
	if(FUN==2)WaveForm_Data(Sp3D_X,Sp3D_Y);
	if(FUN==1)Campus_Data(Campus_X,Campus_Y);
}
void Window_DataFresh()
{
	FUN_Select();
	RC_Data(10,10);
	Angle_Data(10,10);
	ACCGRYO_Data(10,10);
	BAT_Data(10,10);
	Moto_Data(10,10);
	
}

int main(void)
{
	Uart1_Init(115200);
	MyLCD_Init();
	LCD_Clear(Black);
	ADS7843_Init();
	Nvic_Init();
	Window_Init();	
	
	while(1)
	{
			Uart_CheckEvent();	
			Window_DataFresh();
			if(GPIO_ADS7843_INT_VALID)
      {			
        ARMJISHU_TouchScreen_ADS7843();
      }
	}
}


