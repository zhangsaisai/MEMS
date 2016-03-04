#include "lcd.h"
#include "delay.h"


void LCD_LineConf(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE , ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                   GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                 GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  	GPIO_Init(GPIOE, &GPIO_InitStructure);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FSMC);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//(RS)
  	GPIO_Init(GPIOD, &GPIO_InitStructure);  
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);	   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//(CS) 
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);
}

void LCD_FSMCConf(void)
{
  	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  	FSMC_NORSRAMTimingInitTypeDef  p;

  	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
  	p.FSMC_AddressSetupTime = 5;
  	p.FSMC_AddressHoldTime = 0;
  	p.FSMC_DataSetupTime = 9;
  	p.FSMC_BusTurnAroundDuration = 0;
  	p.FSMC_CLKDivision = 0;
  	p.FSMC_DataLatency = 0;
  	p.FSMC_AccessMode = FSMC_AccessMode_A;
  	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;
  	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);   
  	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}

void LCD_WriteReg(u8 Reg, u16 Value)
{
  	LCD_REG=Reg;
  	LCD_RAM=Value;
}

u16 LCD_ReadReg(u8 Reg)
{
  	LCD_REG=Reg;
  	return (LCD_RAM);
}
u16 LCD_WR_REG(u16 Reg)
{
  	LCD_REG=Reg;
}

void LCD_WriteRAM(u16 RGB_Code)
{
  	LCD_RAM=RGB_Code;
}
void LCD_WR_Data(u16 data)
{
  LCD_RAM=data;
}
u16 LCD_ReadRAM(void)
{
  	u16 dummy;
  	LCD_REG=0x22; 
	dummy=LCD_RAM;
  	return LCD_RAM;
}

static u32 lcdid=0;
void MyLCD_Init(void)
{ 
   	LCD_LineConf();
  	LCD_FSMCConf();
  	delay_ms(5); 
  	lcdid=LCD_ReadReg(0x00);  
		lcdid = 0x9341;
		if(lcdid == 0x9341)
		{
		LCD_WR_REG(0xEF);
		LCD_WR_Data (0x03);
		LCD_WR_Data(0x80);
		LCD_WR_Data (0X02);

		LCD_WR_REG(0xCF);
		LCD_WR_Data (0x00);
		LCD_WR_Data (0xBA);
		LCD_WR_Data (0XB0);

		LCD_WR_REG(0xED);
		LCD_WR_Data (0x67);
		LCD_WR_Data(0x03);
		LCD_WR_Data(0X12);
		LCD_WR_Data (0X81);

		LCD_WR_REG(0xE8);
		LCD_WR_Data (0x85);
		LCD_WR_Data (0x11);
		LCD_WR_Data (0x79);

		LCD_WR_REG(0xCB);
		LCD_WR_Data (0x39);
		LCD_WR_Data (0x2C);
		LCD_WR_Data (0x00);
		LCD_WR_Data (0x34);
		LCD_WR_Data (0x06);

		LCD_WR_REG(0xF7);
		LCD_WR_Data (0x20);

		LCD_WR_REG(0xEA);
		LCD_WR_Data (0x00);
		LCD_WR_Data (0x00);

		LCD_WR_REG(0xC0); //Power control
		LCD_WR_Data (0x1D); //VRH[5:0]

		LCD_WR_REG(0xC1); //Power control
		LCD_WR_Data (0x12); //SAP[2:0];BT[3:0]

		LCD_WR_REG(0xC5); //VCM control
		LCD_WR_Data (0x44);
		LCD_WR_Data(0x3c);

		LCD_WR_REG(0xC7); //VCM control
		LCD_WR_Data (0x9E);

		LCD_WR_REG(0x3A); // Memory Access Control
		LCD_WR_Data (0x55);

		LCD_WR_REG(0x36); // Memory Access Control
		LCD_WR_Data (0x48);

		LCD_WR_REG(0xB1);
		LCD_WR_Data (0x00);
		LCD_WR_Data (0x17);

		LCD_WR_REG(0xB6); // Display Function Control
		LCD_WR_Data (0x0A);
		LCD_WR_Data(0x82);//A2	

		LCD_WR_REG(0xF2); // 3Gamma Function Disable
		LCD_WR_Data (0x00);

		LCD_WR_REG(0x26); //Gamma curve selected
		LCD_WR_Data (0x01);

		LCD_WR_REG(0xE0); //Set Gamma
		LCD_WR_Data (0x0F);
		LCD_WR_Data (0x22);
		LCD_WR_Data(0x1C);
		LCD_WR_Data (0x1B);
		LCD_WR_Data(0x08);
		LCD_WR_Data(0x0F);
		LCD_WR_Data (0x48);
		LCD_WR_Data(0xB8);
		LCD_WR_Data (0x34);
		LCD_WR_Data(0x05);
		LCD_WR_Data (0x0C);
		LCD_WR_Data(0x09);
		LCD_WR_Data(0x0F);
		LCD_WR_Data (0x07);
		LCD_WR_Data(0x00);

		LCD_WR_REG(0XE1); //Set Gamma
		LCD_WR_Data (0x00);
		LCD_WR_Data (0x23);
		LCD_WR_Data (0x24);
		LCD_WR_Data (0x07);
		LCD_WR_Data (0x10);
		LCD_WR_Data (0x07);
		LCD_WR_Data (0x38);
		LCD_WR_Data (0x47);
		LCD_WR_Data (0x4B);
		LCD_WR_Data (0x0A);
		LCD_WR_Data (0x13);
		LCD_WR_Data (0x06);
		LCD_WR_Data (0x30);
		LCD_WR_Data (0x38);
		LCD_WR_Data (0x0F);
		LCD_WR_REG(0x11); //Exit Sleep
		delay_ms(500);
		LCD_WR_REG(0x29); //Display on
		LCD_Mode(0);	
		LCD_WR_REG(0x2c);
		}					 
}


void LCD_Cursor(u16 Xpos, u16 Ypos)
{
  	LCD_WriteReg(0x20, Xpos);
  	LCD_WriteReg(0x21, Ypos);
}

//X,Y为窗口左下角座标,注意设置窗口后座标不要超出该范围
void LCD_Window(u16 Xpos, u16 Ypos, u16 Height, u16 Width)
{
  	LCD_WR_REG(0X2A); 
		LCD_WR_Data(Xpos>>8);	//start 起始位置的高8位
		LCD_WR_Data(Xpos-((Xpos>>8)<<8));  //起始位置的低8位
		LCD_WR_Data((Xpos+Width-1)>>8);	//end 结束位置的高8位
		LCD_WR_Data((Xpos+Width-1)-(((Xpos+Width-1)>>8)<<8));  //结束位置的低8位
		
		LCD_WR_REG(0X2B); 
		LCD_WR_Data(Ypos>>8);   //start
		LCD_WR_Data(Ypos-((Ypos>>8)<<8));
		LCD_WR_Data((Ypos+Height-1)>>8);   //end
		LCD_WR_Data((Ypos+Height-1)-(((Ypos+Height-1)>>8)<<8));
}

//设置刷屏模式
void LCD_Mode(u8 mode)
{
	if(mode)LCD_WriteReg(0x03,0x1018);//横屏刷屏
	else LCD_WriteReg(0x03,0X1030);   //竖屏刷屏
}

void LCD_Clear(u16 Color)
{
	u32 i;
  	for(i=0;i<76800;i++)		 		   
    LCD_WR_Data(Color);			     
}

void GUI_SetPoint(u16 xpos, u16 ypos,u16 color)
{
  	LCD_Window(240-ypos,320-xpos,1,1);   
		LCD_REG=0x2C;//WriteRAM_Prepare 
		LCD_RAM=color;
}

u16 LCD_BGR2RGB(u16 c)
{
	u16 r,g,b,rgb;
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;
	rgb=(b<<11)+(g<<5)+(r<<0);
  	return( rgb );
}

u16 GUI_GetPoint(u16 xpos,u16 ypos)
{
  	LCD_WriteReg(0x20, ypos);
  	LCD_WriteReg(0x21, 319-xpos);
  	if(lcdid==0x4531)return (LCD_ReadRAM());
  	else return (LCD_BGR2RGB(LCD_ReadRAM()));
}


void TFT_DrawPoint( u16 CoordiX, u16 CoordiY, u32 Color )
{
  	LCD_Window(CoordiY,320-CoordiX,1,1);   
		LCD_REG=0x2C;//WriteRAM_Prepare 
		LCD_RAM=Color;
}

void TFT_Draw9Point( u16 CoordiX, u16 CoordiY, u32 Color )
{
	TFT_DrawPoint(CoordiX,CoordiY,Color);
	TFT_DrawPoint(CoordiX,CoordiY-1,Color);
	TFT_DrawPoint(CoordiX,CoordiY+1,Color);
	TFT_DrawPoint(CoordiX-1,CoordiY,Color);
	TFT_DrawPoint(CoordiX+1,CoordiY,Color);
	TFT_DrawPoint(CoordiX-1,CoordiY-1,Color);
	TFT_DrawPoint(CoordiX-1,CoordiY+1,Color);
	TFT_DrawPoint(CoordiX+1,CoordiY-1,Color);
	TFT_DrawPoint(CoordiX+1,CoordiY+1,Color);
}

void TFT_Draw16Point( u16 CoordiX, u16 CoordiY, u32 Color )
{
	TFT_Draw9Point(CoordiX, CoordiY, Color);
	
	TFT_DrawPoint(CoordiX-1,CoordiY+2,Color);
	TFT_DrawPoint(CoordiX+1,CoordiY+2,Color);
	TFT_DrawPoint(CoordiX-1,CoordiY-2,Color);
	TFT_DrawPoint(CoordiX+1,CoordiY-2,Color);
	TFT_DrawPoint(CoordiX-2,CoordiY-1,Color);
	TFT_DrawPoint(CoordiX-2,CoordiY+1,Color);
	TFT_DrawPoint(CoordiX+2,CoordiY-1,Color);
	TFT_DrawPoint(CoordiX+2,CoordiY+1,Color);
	
	TFT_DrawPoint(CoordiX,CoordiY-2,Color);
	TFT_DrawPoint(CoordiX,CoordiY+2,Color);
	TFT_DrawPoint(CoordiX-2,CoordiY,Color);
	TFT_DrawPoint(CoordiX+2,CoordiY,Color);
	TFT_DrawPoint(CoordiX-2,CoordiY-2,Color);
	TFT_DrawPoint(CoordiX-2,CoordiY+2,Color);
	TFT_DrawPoint(CoordiX+2,CoordiY-2,Color);
	TFT_DrawPoint(CoordiX+2,CoordiY+2,Color);	
}

#include <stdio.h>
void TFT_DrawLine( u16 StartX, u16 StartY, u16 EndX, u16 EndY, u32 Color )
{
	u16 i;
	s16 DeltaX, DeltaY;
	double Slope;

	DeltaX = EndX - StartX;
	DeltaY = EndY - StartY;

	// ?? Slope
	if(DeltaX == 0)
		Slope = 0;
	else
		Slope = (double)DeltaY/(double)DeltaX;

if(DeltaX<0)DeltaX=-DeltaX;
if(DeltaY<0)DeltaY=-DeltaY;

	if(EndX<StartX) {
		if(Slope<0) {
			if(DeltaX>DeltaY) {
				for(i=0; i<=DeltaX; i++)
					TFT_DrawPoint(EndX+i, EndY+(s16)(((double)i*Slope)-0.5), Color);
					
			}
			else {
				for(i=0; i<=DeltaY; i++)
					TFT_DrawPoint(EndX-(s16)(((double)i/Slope)-0.5), EndY-i, Color);
			}
		}
		else {
			if(DeltaX>DeltaY) {
				for(i=0; i<=DeltaX; i++)
					TFT_DrawPoint(EndX+i, EndY+(s16)(((double)i*Slope)+0.5), Color);
			}
			else {
				for(i=0; i<=DeltaY; i++)
					TFT_DrawPoint(EndX+(s16)(((double)i/Slope)+0.5), EndY+i, Color);
			}
		}
	}
	else if(EndX==StartX) {
		if(EndY>StartY) {
			for(i=0; i<=DeltaY; i++)
				TFT_DrawPoint(StartX, StartY+i, Color);
		}
		else {
			for(i=0; i<=DeltaY; i++)
				TFT_DrawPoint(EndX, EndY+i, Color);
		}
	}
	else {
		if(Slope<0) {
			if(DeltaX>DeltaY) {
				for(i=0; i<=DeltaX; i++)
					TFT_DrawPoint(StartX+i, StartY+(s16)(((double)i*Slope)-0.5), Color);
			}
			else {
				for(i=0; i<=DeltaY; i++)
					TFT_DrawPoint(StartX-(s16)(((double)i/Slope)-0.5), StartY-i, Color);
			}
		}
		else {
			if(DeltaX>DeltaY) {
				for(i=0; i<=DeltaX; i++)
					TFT_DrawPoint(StartX+i, StartY+(s16)(((double)i*Slope)+0.5), Color);
			}
			else {
				for(i=0; i<=DeltaY; i++)
					TFT_DrawPoint(StartX+(s16)(((double)i/Slope)+0.5), StartY+i, Color);
			}
		}
	}
}

void TFT_DrawLineX( u16 CoordiX, u16 CoordiY, u16 Length, u32 Color )
{
	u16 i;

	for(i=0; i<Length; i++)
		TFT_DrawPoint(CoordiX+i, CoordiY, Color);
}
void TFT_Draw9LineX( u16 CoordiX, u16 CoordiY, u16 Length, u32 Color )
{
	u16 i;

	for(i=0; i<Length; i++)
		TFT_Draw9Point(CoordiX+i, CoordiY, Color);
}
void TFT_DrawLineY( u16 CoordiX, u16 CoordiY, u16 Length, u32 Color )
{
	u16 i;

	for(i=0; i<Length; i++)
		TFT_DrawPoint(CoordiX, CoordiY+i, Color);
}

void TFT_DrawRectangleFull( u16 CoordiX, u16 CoordiY, u16 Length, u16 Width, u32 Color )
{
	u16 i, j;

	for(i=0; i<Width; i++)
		for(j=0; j<Length; j++)
			TFT_DrawPoint(CoordiX+j, CoordiY+i, Color);
}

void TFT_DrawRectangle( u16 CoordiX, u16 CoordiY, u16 Length, u16 Width, u32 Color )
{
	u16 i;

	for(i=0; i<=Length; i++) {
		TFT_DrawPoint(CoordiX+i, CoordiY, Color);
		TFT_DrawPoint(CoordiX+i, CoordiY+Width, Color);
	}
	for(i=1; i<Width; i++) {
		TFT_DrawPoint(CoordiX, CoordiY+i, Color);
		TFT_DrawPoint(CoordiX+Length, CoordiY+i, Color);
	}
}
void TFT_Draw9Rectangle( u16 CoordiX, u16 CoordiY, u16 Length, u16 Width, u32 Color )
{
	u16 i;

	for(i=0; i<=Length; i++) {
		TFT_Draw9Point(CoordiX+i, CoordiY, Color);
		TFT_Draw9Point(CoordiX+i, CoordiY+Width, Color);
	}
	for(i=1; i<Width; i++) {
		TFT_Draw9Point(CoordiX, CoordiY+i, Color);
		TFT_Draw9Point(CoordiX+Length, CoordiY+i, Color);
	}
}


void TFT_DrawCircle( u16 CoordiX, u16 CoordiY, u16 Radius, u32 Color )
{
	int a,b;
	int di;

	a=0;
	b=Radius;
	di=3-(Radius<<1);

	while(a<=b) {
		TFT_DrawPoint(CoordiX-b, CoordiY-a, Color);             //3
		TFT_DrawPoint(CoordiX+b, CoordiY-a, Color);             //0
		TFT_DrawPoint(CoordiX-a, CoordiY+b, Color);             //1
		TFT_DrawPoint(CoordiX-b, CoordiY-a, Color);             //7
		TFT_DrawPoint(CoordiX-a, CoordiY-b, Color);             //2
		TFT_DrawPoint(CoordiX+b, CoordiY+a, Color);             //4
		TFT_DrawPoint(CoordiX+a, CoordiY-b, Color);             //5
		TFT_DrawPoint(CoordiX+a, CoordiY+b, Color);             //6
		TFT_DrawPoint(CoordiX-b, CoordiY+a, Color);
		a++;
		// ??Bresenham????
		if(di<0)
			di += 4*a+6;
		else {
			di+=10+4*(a-b);
			b--;
		}
		TFT_DrawPoint(CoordiX+a, CoordiY+b, Color);
	}
}

#include "module_fontlib.h"

void TFT_PutChar1206( u16 CoordiX, u16 CoordiY, u8* ChWord, u32 FontColor, u32 BackColor )
{
	u8 Tmp_Char = 0;
	u16 i = 0, j = 0;

	for(i=0; i<12; i++) {
		Tmp_Char = ASCII_12x6[*ChWord-32][i];
		for(j=0; j<6; j++) {
			if((Tmp_Char>>j) & 0x01 == 0x01)
				TFT_DrawPoint(CoordiX+j, CoordiY+i, FontColor);	// ????
			else
				TFT_DrawPoint(CoordiX+j, CoordiY+i, BackColor);	// ????
		}
	}
}

void TFT_PutChar1608( u16 CoordiX, u16 CoordiY, u8* ChWord, u32 FontColor, u32 BackColor )
{
	u8 Tmp_Char = 0;
	u16 i = 0, j = 0;

	for(i=0; i<16; i++) {
		Tmp_Char = ASCII_16x8[*ChWord-32][i];
		for(j=0; j<8; j++) {
			if((Tmp_Char>>(7-j)) & 0x01 == 0x01)
				TFT_DrawPoint(CoordiX+j, CoordiY+i, FontColor);	// ????
			else
				TFT_DrawPoint(CoordiX+j, CoordiY+i, BackColor);	// ????
		}
	}
}

void TFT_PutChar1608_( u16 CoordiX, u16 CoordiY, u8* ChWord, u32 FontColor, u32 BackColor )
{
	u8 Tmp_Char = 0;
	u16 i = 0, j = 0;

	for(i=0; i<16; i++) {
		Tmp_Char = ASCII_16x8_[*ChWord-32][i];
		for(j=0; j<8; j++) {
			if((Tmp_Char>>j) & 0x01 == 0x01)
				TFT_DrawPoint(CoordiX+j, CoordiY+i, FontColor);	// ????
			else
				TFT_DrawPoint(CoordiX+j, CoordiY+i, BackColor);	// ????
		}
	}
}

void TFT_PutStr( u16 CoordiX, u16 CoordiY, u8 *ChWord, u8 FontStyle, u32 FontColor, u32 BackColor )
{
	u16 OffsetX = 0;

	switch(FontStyle) {
		case ASCII1206:
			while(*ChWord) {
				TFT_PutChar1206(CoordiX+OffsetX, CoordiY, ChWord, FontColor, BackColor);
				ChWord++;
				OffsetX += 6;
			}
			break;
		case ASCII1608:
			while(*ChWord) {
				TFT_PutChar1608(CoordiX+OffsetX, CoordiY, ChWord, FontColor, BackColor);
				ChWord++;
				OffsetX += 8;
			}
			break;
		case ASCII1608_:
			while(*ChWord) {
				TFT_PutChar1608_(CoordiX+OffsetX, CoordiY, ChWord, FontColor, BackColor);
				ChWord++;
				OffsetX += 8;
			}
			break;
	}
}

void NumToChar( u8 Type, u8 Num, u8 *CharData, s32 NumData )
{
  u8 i = 0;
  u32 Tmp[48] = {0};
  u32 NumTmp = 1;

  switch(Type) {

    case Type_B:  // 2秈
    case Type_O:  // 8秈
    case Type_D:  // 10秈
    case Type_H:  // 16秈
      for(i=0; i<Num; i++) {
        Tmp[i] = ((u32)NumData) / NumTmp;
        NumTmp = NumTmp * Type;
      }
      for(i=0; i<Num; i++) {
        CharData[Num-i-1] = Tmp[i] - Tmp[i+1]*Type;
        if(CharData[Num-i-1]>9)
          CharData[Num-i-1] += 55;  // 65-10
        else
          CharData[Num-i-1] += 48;
      }
      CharData[Num] = '\0';
      break;

    case Type_I:  // 10秈, Τタ璽腹
      if(NumData<0) {
        CharData[0] = '-';
        NumData = (~NumData) + 1;
        for(i=1; i<Num+1; i++) {
        Tmp[i-1] = ((u32)NumData) / NumTmp;
          NumTmp = NumTmp * 10;
        }
        for(i=1; i<Num+1; i++) {
        CharData[Num-i+1] = Tmp[i-1] - Tmp[i]*10;
          CharData[Num-i+1] += 48;
        }
        CharData[Num+1] = '\0';
      }
      else {
        CharData[0] = '+';
        //NumData = (~NumData) + 1;
        for(i=1; i<Num+1; i++) {
          Tmp[i-1] = ((u32)NumData) / NumTmp;
          NumTmp = NumTmp * 10;
        }
        for(i=1; i<Num+1; i++) {
          CharData[Num-i+1] = Tmp[i-1] - Tmp[i]*10;
          CharData[Num-i+1] += 48;
        }
        CharData[Num+1] = '\0';
      }
      break;

//     case Type_F:  // 10秈, 疊翴计
//         
//       break;
  }
}


u8 PrintTr[16] = {0};
void TFT_PutViriable(u16 X,u16 Y,int16_t a,u8 len,u16 fColor, u16 bColor)
{

NumToChar(Type_I, len, PrintTr, a);
TFT_PutStr(X, Y, PrintTr, ASCII1206, fColor, bColor);

}


void Title(u16 CoordiX, u16 CoordiY, u8 *ChWord,u16 Length, u16 Width, u8 FontStyle, u32 FontColor, u32 BackColor)
{
TFT_DrawRectangle( CoordiX,CoordiY,Length,Width, FontColor );
TFT_PutStr(CoordiX+5, CoordiY-5, ChWord, FontStyle, FontColor, BackColor);
}

void Title_Touched(u16 CoordiX, u16 CoordiY, u8 *ChWord,u16 Length, u16 Width, u8 FontStyle, u32 FontColor, u32 BackColor)
{
	TFT_Draw9Rectangle( CoordiX,CoordiY,Length,Width, FontColor );
	TFT_PutStr(CoordiX+5, CoordiY-5, ChWord, FontStyle, FontColor, BackColor);
}

void Button(u16 CoordiX, u16 CoordiY, u8 *ChWord,u16 Length, u16 Width, u8 FontStyle, u32 FontColor, u32 BackColor)
{
	TFT_DrawRectangleFull( CoordiX,CoordiY,Length,Width, BackColor );
	TFT_DrawRectangle( CoordiX,CoordiY,Length,Width, FontColor );
	TFT_PutStr(CoordiX+3, CoordiY+Width/3-3, ChWord, FontStyle, White, BackColor);
}

void Button_Touched(u16 CoordiX, u16 CoordiY, u8 *ChWord,u16 Length, u16 Width, u8 FontStyle, u32 FontColor, u32 BackColor)
{
	
TFT_DrawRectangleFull( CoordiX,CoordiY,Length,Width, FontColor );
TFT_PutStr(CoordiX+3, CoordiY+Width/3-3, ChWord, FontStyle, White, BackColor);
}

///////////////////////////////////////周立功GUI

void  GUI_Pieslice(u16 x, u16 y, u16 r, u16 stangle, u16 endangle, u16 color)
{  int  draw_x, draw_y;					// ??????
   int  op_x, op_y;						// ????
   int  op_2rr;							// 2*r*r???
   
   int  pno_angle;						// ??????
   u8  draw_on;							// ????,?1???,?0???
   
   
   /* ???? */
   if(r==0) return;							// ???0?????
   if(stangle==endangle) return;			// ???????????,??
   if( (stangle>=360) || (endangle>=360) ) return;

   op_2rr = 2*r*r;							// ??r????2
   pno_angle = 0;
   /* ??????????45??????? */       
   op_x = r;
   op_y = 0;
   while(1)
   {  pno_angle++; 							// ????         
      /* ????? */
      op_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ????????????
      {  op_x--;
      }
      if(op_y>=op_x) break;
   }
   
   draw_on = 0;								// ????????
   /* ???????? */
   if(endangle>stangle) draw_on = 1;		// ???????,????????(359)
   stangle = (360-stangle)*pno_angle/45;
   endangle = (360-endangle)*pno_angle/45;
   if(stangle==0) stangle=1;
   if(endangle==0) endangle=1;
   
   /* ???????,?359???(?4??) */
   pno_angle = 0;
   
   draw_x = x+r;
   draw_y = y;         
   op_x = r;
   op_y = 0;
   while(1)
   {  /* ????? */
      op_y++;
      draw_y--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ????????????
      {  op_x--;
         draw_x--;
      }
      if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
         TFT_DrawLine(x, y, draw_x, draw_y, color);
      } 
      if(op_y>=op_x)
      {  if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
         break;
      }
   }
   
   while(1)
   {  /* ????? */
      op_x--;
      draw_x--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) // ????????????
      {  op_y++;
         draw_y--;
      }
      if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
         TFT_DrawLine(x, y, draw_x, draw_y, color);
      } 
      
      if(op_x<=0)
      {  if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);		// ????
         break;
      }
   }
    
    
   /* ???????,?269???(?3??) */
   draw_y = y-r;
   draw_x = x;         
   op_y = r;
   op_x = 0;
   while(1)
   {  /* ????? */
      op_x++;
      draw_x--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_y +1)>0 ) // ????????????
      {  op_y--;
         draw_y++;
      }
      if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
         TFT_DrawLine(x, y, draw_x, draw_y, color);
      } 
      
      if(op_x>=op_y)
      {  if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);		// ????
         break;
      }
   }
   
   while(1)
   {  /* ????? */
      op_y--;
      draw_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_x +1)<=0 ) // ????????????
      {  op_x++;
         draw_x--;
      }
      if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
         TFT_DrawLine(x, y, draw_x, draw_y, color);
      } 
      if(op_y<=0)
      {  if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
         break;
      }
   }
   
   
   /* ???????,?179???(?2??) */
   draw_x = x-r;
   draw_y = y;         
   op_x = r;
   op_y = 0;
   while(1)
   {  /* ????? */
      op_y++;
      draw_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ????????????
      {  op_x--;
         draw_x++;
      }
      if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
         TFT_DrawLine(x, y, draw_x, draw_y, color);
      } 
      if(op_y>=op_x)
      {  if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
         break;
      }
   }
   
   while(1)
   {  /* ????? */
      op_x--;
      draw_x++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) // ????????????
      {  op_y++;
         draw_y++;
      }
      if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
         TFT_DrawLine(x, y, draw_x, draw_y, color);
      } 
      
      if(op_x<=0)
      {  if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);		// ????
         break;
      }
   }
  
  
   /* ???????,?89???(?1??) */
   draw_y = y+r;
   draw_x = x;         
   op_y = r;
   op_x = 0;
   while(1)
   {  /* ????? */
      op_x++;
      draw_x++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_y +1)>0 ) // ????????????
      {  op_y--;
         draw_y--;
      }
      if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
         TFT_DrawLine(x, y, draw_x, draw_y, color);
      } 
      
      if(op_x>=op_y)
      {  if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);		// ????
         break;
      }
   }
   
   while(1)
   {  /* ????? */
      op_y--;
      draw_y--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_x +1)<=0 ) // ????????????
      {  op_x++;
         draw_x++;
      }
      if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
         TFT_DrawLine(x, y, draw_x, draw_y, color);
      } 
      if(op_y<=0)
      {  if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
         break;
      }
   }
   
}


void  GUI_Arc16(u16 x, u16 y, u16 r, u16 stangle, u16 endangle, u16 color)

{  int  draw_x, draw_y;					// ??????
   int  op_x, op_y;						// ????
   int  op_2rr;							// 2*r*r???
   
   int  pno_angle;						// ??????
   u8  draw_on;							// ????,?1???,?0???
   
   stangle=360-stangle;
	 endangle=360-endangle;
   /* ???? */
   if(r==0) return;							// ???0?????
   if(stangle==endangle) return;			// ???????????,??
   if( (stangle>=360) || (endangle>=360) ) return;

   op_2rr = 2*r*r;							// ??r????2
   pno_angle = 0;
   /* ??????????45??????? */       
   op_x = r;
   op_y = 0;
   while(1)
   {  pno_angle++; 							// ????         
      /* ????? */
      op_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ????????????
      {  op_x--;
      }
      if(op_y>=op_x) break;
   }
   
   draw_on = 0;								// ????????
   /* ???????? */
   if(endangle>stangle) draw_on = 1;		// ???????,????????(359)
   stangle = (360-stangle)*pno_angle/45;
   endangle = (360-endangle)*pno_angle/45;
   if(stangle==0) stangle=1;
   if(endangle==0) endangle=1;
   
   /* ???????,?359???(?4??) */
   pno_angle = 0;
   
   draw_x = x+r;
   draw_y = y;         
   op_x = r;
   op_y = 0;
   while(1)
   {  /* ????? */
      op_y++;
      draw_y--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ????????????
      {  op_x--;
         draw_x--;
      }
      if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
      } 
      if(op_y>=op_x)
      {  if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
         break;
      }
   }
   
   while(1)
   {  /* ????? */
      op_x--;
      draw_x--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) // ????????????
      {  op_y++;
         draw_y--;
      }
      if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
      } 
      
      if(op_x<=0)
      {  if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);		// ????
         break;
      }
   }
    
    
   /* ???????,?269???(?3??) */
   draw_y = y-r;
   draw_x = x;         
   op_y = r;
   op_x = 0;
   while(1)
   {  /* ????? */
      op_x++;
      draw_x--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_y +1)>0 ) // ????????????
      {  op_y--;
         draw_y++;
      }
      if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
      } 
      
      if(op_x>=op_y)
      {  if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);		// ????
         break;
      }
   }
   
   while(1)
   {  /* ????? */
      op_y--;
      draw_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_x +1)<=0 ) // ????????????
      {  op_x++;
         draw_x--;
      }
      if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
      } 
      if(op_y<=0)
      {  if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
         break;
      }
   }
   
   
   /* ???????,?179???(?2??) */
   draw_x = x-r;
   draw_y = y;         
   op_x = r;
   op_y = 0;
   while(1)
   {  /* ????? */
      op_y++;
      draw_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ????????????
      {  op_x--;
         draw_x++;
      }
      if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
      } 
      if(op_y>=op_x)
      {  if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
         break;
      }
   }
   
   while(1)
   {  /* ????? */
      op_x--;
      draw_x++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) // ????????????
      {  op_y++;
         draw_y++;
      }
      if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
      } 
      
      if(op_x<=0)
      {  if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);		// ????
         break;
      }
   }
  
  
   /* ???????,?89???(?1??) */
   draw_y = y+r;
   draw_x = x;         
   op_y = r;
   op_x = 0;
   while(1)
   {  /* ????? */
      op_x++;
      draw_x++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_y +1)>0 ) // ????????????
      {  op_y--;
         draw_y--;
      }
      if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
      } 
      
      if(op_x>=op_y)
      {  if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);		// ????
         break;
      }
   }
   
   while(1)
   {  /* ????? */
      op_y--;
      draw_y--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_x +1)<=0 ) // ????????????
      {  op_x++;
         draw_x++;
      }
      if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
      } 
      if(op_y<=0)
      {  if(draw_on==1) TFT_Draw16Point(draw_x, draw_y, color);
         break;
      }
   }
   
}

void  GUI_Arc9(u16 x, u16 y, u16 r, u16 stangle, u16 endangle, u16 color)

{  int  draw_x, draw_y;					// ??????
   int  op_x, op_y;						// ????
   int  op_2rr;							// 2*r*r???
   
   int  pno_angle;						// ??????
   u8  draw_on;							// ????,?1???,?0???
   
   stangle=360-stangle;
	 endangle=360-endangle;
   /* ???? */
   if(r==0) return;							// ???0?????
   if(stangle==endangle) return;			// ???????????,??
   if( (stangle>=360) || (endangle>=360) ) return;

   op_2rr = 2*r*r;							// ??r????2
   pno_angle = 0;
   /* ??????????45??????? */       
   op_x = r;
   op_y = 0;
   while(1)
   {  pno_angle++; 							// ????         
      /* ????? */
      op_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ????????????
      {  op_x--;
      }
      if(op_y>=op_x) break;
   }
   
   draw_on = 0;								// ????????
   /* ???????? */
   if(endangle>stangle) draw_on = 1;		// ???????,????????(359)
   stangle = (360-stangle)*pno_angle/45;
   endangle = (360-endangle)*pno_angle/45;
   if(stangle==0) stangle=1;
   if(endangle==0) endangle=1;
   
   /* ???????,?359???(?4??) */
   pno_angle = 0;
   
   draw_x = x+r;
   draw_y = y;         
   op_x = r;
   op_y = 0;
   while(1)
   {  /* ????? */
      op_y++;
      draw_y--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ????????????
      {  op_x--;
         draw_x--;
      }
      if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);
      } 
      if(op_y>=op_x)
      {  if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);
         break;
      }
   }
   
   while(1)
   {  /* ????? */
      op_x--;
      draw_x--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) // ????????????
      {  op_y++;
         draw_y--;
      }
      if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);
      } 
      
      if(op_x<=0)
      {  if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);		// ????
         break;
      }
   }
    
    
   /* ???????,?269???(?3??) */
   draw_y = y-r;
   draw_x = x;         
   op_y = r;
   op_x = 0;
   while(1)
   {  /* ????? */
      op_x++;
      draw_x--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_y +1)>0 ) // ????????????
      {  op_y--;
         draw_y++;
      }
      if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);
      } 
      
      if(op_x>=op_y)
      {  if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);		// ????
         break;
      }
   }
   
   while(1)
   {  /* ????? */
      op_y--;
      draw_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_x +1)<=0 ) // ????????????
      {  op_x++;
         draw_x--;
      }
      if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);
      } 
      if(op_y<=0)
      {  if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);
         break;
      }
   }
   
   
   /* ???????,?179???(?2??) */
   draw_x = x-r;
   draw_y = y;         
   op_x = r;
   op_y = 0;
   while(1)
   {  /* ????? */
      op_y++;
      draw_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ????????????
      {  op_x--;
         draw_x++;
      }
      if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);
      } 
      if(op_y>=op_x)
      {  if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);
         break;
      }
   }
   
   while(1)
   {  /* ????? */
      op_x--;
      draw_x++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) // ????????????
      {  op_y++;
         draw_y++;
      }
      if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);
      } 
      
      if(op_x<=0)
      {  if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);		// ????
         break;
      }
   }
  
  
   /* ???????,?89???(?1??) */
   draw_y = y+r;
   draw_x = x;         
   op_y = r;
   op_x = 0;
   while(1)
   {  /* ????? */
      op_x++;
      draw_x++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_y +1)>0 ) // ????????????
      {  op_y--;
         draw_y--;
      }
      if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);
      } 
      
      if(op_x>=op_y)
      {  if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);		// ????
         break;
      }
   }
   
   while(1)
   {  /* ????? */
      op_y--;
      draw_y--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_x +1)<=0 ) // ????????????
      {  op_x++;
         draw_x++;
      }
      if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);			// ????
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// ????????,??????
      {  draw_on = 1-draw_on;
         if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);
      } 
      if(op_y<=0)
      {  if(draw_on==1) TFT_Draw9Point(draw_x, draw_y, color);
         break;
      }
   }
   
}
