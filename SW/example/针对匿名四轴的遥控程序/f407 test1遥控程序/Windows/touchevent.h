#include <stm32f4xx.h>

extern u8 _3dstatus_Flag;
extern u8 Campus_Flag;
extern u8 WaveForm_Flag;

unsigned char Button_Event(u16 CoordiX, u16 CoordiY, u8 *ChWord,u16 Length, u16 Width,u16 Touch_X,u16 Touch_Y, u8 FontStyle, u32 FontColor, u32 BackColor);
void Touch_Event( u16 Touch_X ,u16 Touch_Y);

