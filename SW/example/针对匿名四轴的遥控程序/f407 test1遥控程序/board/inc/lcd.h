#ifndef __TFT_H
#define __TFT_H

#include "stm32f4xx_conf.h"

 
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //趹伎
#define BRRED 			 0XFC07 //趹綻伎
#define GRAY  			 0X8430 //閡伎
#define DARKBLUE      	 0X01CF	//旮懦伎
#define LIGHTBLUE      	 0X7D7C	//Ё懦伎  
#define GRAYBLUE       	 0X5458 //閡懦伎

#define White         	 0xFFFF
#define Black         	 0x0000	  
#define Blue         	 0x001F
#define Blue2          0x051F
#define Bred             0XF81F
#define Gred 			 0XFFE0
#define Gblue			 0X07FF
#define Red           	 0xF800
#define Magenta       	 0xF81F
#define Green         	 0x07E0
#define Cyan          	 0x7FFF
#define Yellow        	 0xFFE0
#define Brown 			 0XBC40 //趹伎
#define Breed 			 0XFC07 //趹綻伎
#define Gray  			 0X8430 //閡伎
#define Darkblue      	 0X01CF	//旮懦伎
#define Lightblue      	 0X7D7C	//Ё懦伎  
#define Grayblue       	 0X5458 //閡懦伎

#define LCD_RAM   *(vu16*)((u32)0x60020000)  //disp Data ADDR
#define LCD_REG   *(vu16*)((u32)0x60000000)	 //disp Reg  ADDR

#define LCD_WIDTH	  320
#define LCD_HEIGHT	  240

#define ASCII1206		((u8)0x00)
#define ASCII1608		((u8)0x04)
#define ASCII1608_	((u8)0x05)

#define Type_B 2    // 無號數二進制
#define Type_O 8    // 無號數八進制
#define Type_D 10   // 無號數十進制
#define Type_H 16   // 無號數十六進制
#define Type_I 0    // 有號數

void MyLCD_Init(void);
void LCD_Cursor(u16 Xpos, u16 Ypos);
void LCD_Window(u16 Xpos, u16 Ypos, u16 Height, u16 Width);
void LCD_Mode(u8 mode);

void LCD_Clear(u16 Color);
void LCD_Point(u16 xpos, u16 ypos,u16 color);
void GUI_SetPoint(u16 xpos, u16 ypos,u16 color);
u16  GUI_GetPoint(u16 xpos,u16 ypos);

void LCD_LineConf(void);
void LCD_FSMCConf(void);
void LCD_WriteReg(u8 Reg, u16 Value);
u16  LCD_ReadReg(u8 Reg);
void LCD_WriteRAM(u16 RGB_Code);

void TFT_DrawPoint( u16 CoordiX, u16 CoordiY, u32 Color );
void TFT_Clear( u16 Color );
void TFT_PutStr( u16 CoordiX, u16 CoordiY, u8 *ChWord, u8 FontStyle, u32 FontColor, u32 BackColor );
void TFT_DrawLine( u16 StartX, u16 StartY, u16 EndX, u16 EndY, u32 Color );
void TFT_DrawLineY( u16 CoordiX, u16 CoordiY, u16 Length, u32 Color );
void TFT_DrawLineX( u16 CoordiX, u16 CoordiY, u16 Length, u32 Color );
void TFT_Draw9LineX( u16 CoordiX, u16 CoordiY, u16 Length, u32 Color );
void TFT_DrawRectangle( u16 CoordiX, u16 CoordiY, u16 Length, u16 Width, u32 Color ); 
void TFT_Draw9Rectangle( u16 CoordiX, u16 CoordiY, u16 Length, u16 Width, u32 Color ); 
void TFT_DrawRectangleFull( u16 CoordiX, u16 CoordiY, u16 Length, u16 Width, u32 Color );
void TFT_DrawCircle( u16 CoordiX, u16 CoordiY, u16 Radius, u32 Color );

void  GUI_Pieslice(u16 x, u16 y, u16 r, u16 stangle, u16 endangle, u16 color);
void  GUI_Arc9(u16 x, u16 y, u16 r, u16 stangle, u16 endangle, u16 color);
void  GUI_Arc16(u16 x, u16 y, u16 r, u16 stangle, u16 endangle, u16 color);
void  GUI_LineWith(u16 x0, u16 y0, u16 x1, u16 y1, u8 with, u16 color);
void TFT_Draw9Point( u16 CoordiX, u16 CoordiY, u32 Color );
void TFT_Draw16Point( u16 CoordiX, u16 CoordiY, u32 Color );


void NumToChar( u8 Type, u8 Num, u8 *CharData, s32 NumData );
void TFT_PutViriable(u16 X,u16 Y,int16_t a,u8 len,u16 fColor, u16 bColor);
void Title(u16 CoordiX, u16 CoordiY, u8 *ChWord,u16 Length, u16 Width, u8 FontStyle, u32 FontColor, u32 BackColor);
void Button_Touched(u16 CoordiX, u16 CoordiY, u8 *ChWord,u16 Length, u16 Width, u8 FontStyle, u32 FontColor, u32 BackColor);
void Button(u16 CoordiX, u16 CoordiY, u8 *ChWord,u16 Length, u16 Width, u8 FontStyle, u32 FontColor, u32 BackColor);

#endif
