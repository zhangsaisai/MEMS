#include <stm32f4xx.h>
#include "usart_dt.h"

#define Campus_X 160
#define Campus_Y 115
#define Sp3D_X 133
#define Sp3D_Y 105
#define Sp3D_R 18

#define invSqrtf( iSq ) (1.0f/sqrtf((float)iSq))
#define squa( Sq )      (((float)Sq)*((float)Sq))
#define toRad( Math_D )	((float)(Math_D)*0.0174532925f)
#define toDeg( Math_R )	((float)(Math_R)*57.2957795f)
#include "math.h"
#include "system_engine3D.h"

void _3dstatus_Window(u16 Pr3D_X,u16 Pr3D_Y,u16 Pr3D_R);
void _3dstatus_Data(u16 Pr3D_X,u16 Pr3D_Y,u16 Pr3D_R);

void Campus_Window(u16 x,u16 y);
void Campus_Data(u16 x,u16 y);

void WaveForm_Window(u16 Pr3D_X,u16 Pr3D_Y);
void WaveForm_Data(u16 Pr3D_X,u16 Pr3D_Y);

void Angle_Window(u16 x,u16 y);
void Angle_Data(u16 x,u16 y);

void ACCGRYO_Window(u16 x,u16 y);
void ACCGRYO_Data(u16 x,u16 y);

void RC_Window(u16 x,u16 y);
void RC_Data(u16 x,u16 y);

void Moto_Window(u16 x,u16 y);
void Moto_Data(u16 x,u16 y);

void BAT_Window(u16 x,u16 y);
void BAT_Data(u16 x,u16 y);


