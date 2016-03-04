#include <stm32f4xx.h>
#include "lcd.h"
#include "usart_dt.h"
#include "touch.h"
#include "status.h"
#include "stdio.h"
#include "stdlib.h"
#include "delay.h"
s16 Cube0[8][3] = {0};
s16 Cube1[8][3] = {0};
s16 Cube2[8][3] = {0};
s16 Copter3D[12][3] = {0};

u8 i=0;
u8 flag=0;
s16 _3d_Rol,_3d_Pit,_3d_Yaw = 0;

void _3dstatus_Window(u16 Pr3D_X,u16 Pr3D_Y,u16 Pr3D_R)
{
			Button_Touched(Sp3D_X-60,Sp3D_Y-70, "3D Status", 60,15,ASCII1206,Blue, Blue);
			Button(Sp3D_X,Sp3D_Y-70, " Campus ", 50,15,ASCII1206,Blue, Black);
			Button(Sp3D_X+50,Sp3D_Y-70, " WaveForm", 60,15,ASCII1206,Blue, Black);
			
			Title(Pr3D_X-62,Pr3D_Y-72, "", 173,140,ASCII1206,White, Black);			
			TFT_DrawLine(Pr3D_X-50,Pr3D_Y-45,Pr3D_X-50,Pr3D_Y+60,BLUE);
			TFT_DrawLine(Pr3D_X-50,Pr3D_Y+60,Pr3D_X+95,Pr3D_Y+60,BLUE);
			TFT_PutStr(Pr3D_X-45,Pr3D_Y-40, "Z", ASCII1206,WHITE, BLACK);
			TFT_PutStr(Pr3D_X+80,Pr3D_Y+43, "Y", ASCII1206,WHITE, BLACK);				
}
vs16 Sita=0;
void _3dstatus_Data(u16 Pr3D_X,u16 Pr3D_Y,u16 Pr3D_R)
{
								
			TFT_DrawLine(Pr3D_X-50,Pr3D_Y+60,Pr3D_X-30,Pr3D_Y+25,BLUE);
			TFT_PutStr(Pr3D_X-35,Pr3D_Y+25, "X", ASCII1206,WHITE, BLACK);
			
			Pr3D_X+=65;	
			TFT_DrawLine(Pr3D_X+Copter3D[0][0], Pr3D_Y+Copter3D[0][1], Pr3D_X+Copter3D[2][0], Pr3D_Y+Copter3D[2][1], BLACK);
			TFT_DrawLine(Pr3D_X+Copter3D[1][0], Pr3D_Y+Copter3D[1][1], Pr3D_X+Copter3D[3][0], Pr3D_Y+Copter3D[3][1], BLACK);
			TFT_DrawCircle(Pr3D_X+Copter3D[0][0], Pr3D_Y+Copter3D[0][1],5,BLACK);
			TFT_DrawCircle(Pr3D_X+Copter3D[2][0], Pr3D_Y+Copter3D[2][1],5,BLACK);
			TFT_DrawCircle(Pr3D_X+Copter3D[1][0], Pr3D_Y+Copter3D[1][1],5,BLACK);
			TFT_DrawCircle(Pr3D_X+Copter3D[3][0], Pr3D_Y+Copter3D[3][1],5,BLACK);
			Copter3D[0][0] = Pr3D_R*2;
			Copter3D[0][1] = 0;
			Copter3D[0][2] = 0;
			Copter3D[1][0] = 0;
			Copter3D[1][1] = Pr3D_R*2;
			Copter3D[1][2] = 0;
			Copter3D[2][0] = -Pr3D_R*2;
			Copter3D[2][1] = 0;
			Copter3D[2][2] = 0;
			Copter3D[3][0] = 0;
			Copter3D[3][1] = -Pr3D_R*2;
			Copter3D[3][2] = 0;
			for(i=0; i<4; i++) {

				Engine3D_RotateZ(45-(float)(STATUS1.YAW*0.015f), Copter3D[i]);
				Engine3D_RotateX(70+(float)STATUS1.ROL*0.01f, Copter3D[i]);
				Engine3D_RotateY((float)STATUS1.PIT*0.012f, Copter3D[i]);
				
			}
			TFT_DrawLine(Pr3D_X+Copter3D[0][0], Pr3D_Y+Copter3D[0][1], Pr3D_X+Copter3D[2][0], Pr3D_Y+Copter3D[2][1], Green);
			TFT_DrawLine(Pr3D_X+Copter3D[1][0], Pr3D_Y+Copter3D[1][1], Pr3D_X+Copter3D[3][0], Pr3D_Y+Copter3D[3][1], Green);
			TFT_DrawCircle(Pr3D_X+Copter3D[0][0], Pr3D_Y+Copter3D[0][1],5,Yellow);
			TFT_DrawCircle(Pr3D_X+Copter3D[2][0], Pr3D_Y+Copter3D[2][1],5,Red);
			TFT_DrawCircle(Pr3D_X+Copter3D[1][0], Pr3D_Y+Copter3D[1][1],5,Yellow);
			TFT_DrawCircle(Pr3D_X+Copter3D[3][0], Pr3D_Y+Copter3D[3][1],5,Red);
		
			Pr3D_X-=125;	
			TFT_DrawLine(Sp3D_X+Cube0[0][0], Sp3D_Y+Cube0[0][1], Sp3D_X+Cube0[1][0], Sp3D_Y+Cube0[1][1], BLACK);
			TFT_DrawLine(Sp3D_X+Cube0[0][0], Sp3D_Y+Cube0[0][1], Sp3D_X+Cube0[2][0], Sp3D_Y+Cube0[2][1], BLACK);
			TFT_DrawLine(Sp3D_X+Cube0[0][0], Sp3D_Y+Cube0[0][1], Sp3D_X+Cube0[3][0], Sp3D_Y+Cube0[3][1], BLACK);
			TFT_DrawLine(Sp3D_X+Cube0[7][0], Sp3D_Y+Cube0[7][1], Sp3D_X+Cube0[4][0], Sp3D_Y+Cube0[4][1], BLACK);
			TFT_DrawLine(Sp3D_X+Cube0[7][0], Sp3D_Y+Cube0[7][1], Sp3D_X+Cube0[5][0], Sp3D_Y+Cube0[5][1], BLACK);
			TFT_DrawLine(Sp3D_X+Cube0[7][0], Sp3D_Y+Cube0[7][1], Sp3D_X+Cube0[6][0], Sp3D_Y+Cube0[6][1], BLACK);
			TFT_DrawLine(Sp3D_X+Cube0[1][0], Sp3D_Y+Cube0[1][1], Sp3D_X+Cube0[5][0], Sp3D_Y+Cube0[5][1], BLACK);
			TFT_DrawLine(Sp3D_X+Cube0[1][0], Sp3D_Y+Cube0[1][1], Sp3D_X+Cube0[6][0], Sp3D_Y+Cube0[6][1], BLACK);
			TFT_DrawLine(Sp3D_X+Cube0[2][0], Sp3D_Y+Cube0[2][1], Sp3D_X+Cube0[4][0], Sp3D_Y+Cube0[4][1], BLACK);
			TFT_DrawLine(Sp3D_X+Cube0[2][0], Sp3D_Y+Cube0[2][1], Sp3D_X+Cube0[6][0], Sp3D_Y+Cube0[6][1], BLACK);
			TFT_DrawLine(Sp3D_X+Cube0[3][0], Sp3D_Y+Cube0[3][1], Sp3D_X+Cube0[5][0], Sp3D_Y+Cube0[5][1], BLACK);
			TFT_DrawLine(Sp3D_X+Cube0[3][0], Sp3D_Y+Cube0[3][1], Sp3D_X+Cube0[4][0], Sp3D_Y+Cube0[4][1], BLACK);
			Cube0[0][0] = -Sp3D_R;
			Cube0[0][1] = -Sp3D_R;
			Cube0[0][2] = -Sp3D_R;
			Cube0[1][0] = Sp3D_R;
			Cube0[1][1] = -Sp3D_R;
			Cube0[1][2] = -Sp3D_R;
			Cube0[2][0] = -Sp3D_R;
			Cube0[2][1] = Sp3D_R;
			Cube0[2][2] = -Sp3D_R;
			Cube0[3][0] = -Sp3D_R;
			Cube0[3][1] = -Sp3D_R;
			Cube0[3][2] = Sp3D_R;
			Cube0[4][0] = -Sp3D_R;
			Cube0[4][1] = Sp3D_R;
			Cube0[4][2] = Sp3D_R;
			Cube0[5][0] = Sp3D_R;
			Cube0[5][1] = -Sp3D_R;
			Cube0[5][2] = Sp3D_R;
			Cube0[6][0] = Sp3D_R;
			Cube0[6][1] = Sp3D_R;
			Cube0[6][2] = -Sp3D_R;
			Cube0[7][0] = Sp3D_R;
			Cube0[7][1] = Sp3D_R;
			Cube0[7][2] = Sp3D_R;
			for(i=0; i<8; i++) {
					Engine3D_RotateZ((float)(STATUS1.YAW*0.015f), Cube0[i]);			
					Engine3D_RotateX(70+(float)STATUS1.ROL*0.01f, Cube0[i]);
					Engine3D_RotateY((float)STATUS1.PIT*0.007f, Cube0[i]);
			}
			TFT_DrawLine(Sp3D_X+Cube0[0][0], Sp3D_Y+Cube0[0][1], Sp3D_X+Cube0[1][0], Sp3D_Y+Cube0[1][1], GREEN);
			TFT_DrawLine(Sp3D_X+Cube0[0][0], Sp3D_Y+Cube0[0][1], Sp3D_X+Cube0[2][0], Sp3D_Y+Cube0[2][1], RED);
			TFT_DrawLine(Sp3D_X+Cube0[0][0], Sp3D_Y+Cube0[0][1], Sp3D_X+Cube0[3][0], Sp3D_Y+Cube0[3][1], RED);
			TFT_DrawLine(Sp3D_X+Cube0[7][0], Sp3D_Y+Cube0[7][1], Sp3D_X+Cube0[4][0], Sp3D_Y+Cube0[4][1], GREEN);
			TFT_DrawLine(Sp3D_X+Cube0[7][0], Sp3D_Y+Cube0[7][1], Sp3D_X+Cube0[5][0], Sp3D_Y+Cube0[5][1], YELLOW);
			TFT_DrawLine(Sp3D_X+Cube0[7][0], Sp3D_Y+Cube0[7][1], Sp3D_X+Cube0[6][0], Sp3D_Y+Cube0[6][1], YELLOW);
			TFT_DrawLine(Sp3D_X+Cube0[1][0], Sp3D_Y+Cube0[1][1], Sp3D_X+Cube0[5][0], Sp3D_Y+Cube0[5][1], RED);
			TFT_DrawLine(Sp3D_X+Cube0[1][0], Sp3D_Y+Cube0[1][1], Sp3D_X+Cube0[6][0], Sp3D_Y+Cube0[6][1], RED);
			TFT_DrawLine(Sp3D_X+Cube0[2][0], Sp3D_Y+Cube0[2][1], Sp3D_X+Cube0[4][0], Sp3D_Y+Cube0[4][1], YELLOW);
			TFT_DrawLine(Sp3D_X+Cube0[2][0], Sp3D_Y+Cube0[2][1], Sp3D_X+Cube0[6][0], Sp3D_Y+Cube0[6][1], GREEN);
			TFT_DrawLine(Sp3D_X+Cube0[3][0], Sp3D_Y+Cube0[3][1], Sp3D_X+Cube0[5][0], Sp3D_Y+Cube0[5][1], GREEN);
			TFT_DrawLine(Sp3D_X+Cube0[3][0], Sp3D_Y+Cube0[3][1], Sp3D_X+Cube0[4][0], Sp3D_Y+Cube0[4][1], YELLOW);
}




void Campus_Window(u16 x,u16 y)
{
	  Title(Sp3D_X-62,Sp3D_Y-72, "", 173,140,ASCII1206,White, Black);			
		GUI_Arc16(x, y,45, 350,10, Blue);
		GUI_Arc16(x, y,45, 80,100, Blue);
		GUI_Arc16(x, y,45, 170,190, Blue);
		GUI_Arc16(x, y,45, 260,280, Blue);
		
		GUI_Arc16(x, y,45, 35,55, Blue);
		GUI_Arc16(x, y,45, 125,145, Blue);
		GUI_Arc16(x, y,45, 215,235, Blue);
		GUI_Arc16(x, y,45, 305,325, Blue);
		
		
		
		GUI_Pieslice(x, y,30, 1,181, Blue2);
		GUI_Pieslice(x, y,25, 1,181, Blue2);
		GUI_Pieslice(x, y,20, 1,181, Blue2);
		GUI_Pieslice(x, y,15, 1,181, Blue2);
		GUI_Pieslice(x, y,10, 1,181, Blue2);
		GUI_Pieslice(x, y,5, 1,181, Blue2);
		
		GUI_Pieslice(x, y,30, 181,1, Green);
		GUI_Pieslice(x, y,25, 181,1, Green);
		GUI_Pieslice(x, y,20, 181,1, Green);
		GUI_Pieslice(x, y,15, 181,1, Green);
		GUI_Pieslice(x, y,10, 181,1, Green);
		GUI_Pieslice(x, y,5, 181,1, Green);	
		
		TFT_PutStr(x+40, y-45,"NE", ASCII1206, White, Black);
		TFT_PutStr(x+40, y+37,"SE", ASCII1206, White, Black);
		TFT_PutStr(x-50, y-43,"NW", ASCII1206, White, Black);
		TFT_PutStr(x-50, y+33,"SW", ASCII1206, White, Black);
		
}

u8 Angle2=0;
uint32_t Angle1=0;
u16 Campus_Horizon=60;
void Campus_Data(u16 x,u16 y)
{
		u16 Horizon;
		uint32_t Angle;
		u8 i;
		
		TFT_DrawLineY(x,y-30,60,Black);
		for(i=0;i<5;i++)TFT_DrawLineX(x-10,y+20-10*i,20,Black);
				Horizon=y+STATUS1.ROL/200;		
		if(Campus_Horizon>=y)
		{
		TFT_Draw9LineX(x-5,Campus_Horizon,10,Green);
		}
		else
		{
				TFT_Draw9LineX(x-5,Campus_Horizon,10,Blue2);				
		}
		
		TFT_Draw9LineX(x-5,Horizon,10,Black);
		Campus_Horizon=Horizon;
		if(STATUS1.YAW>=0)
		Angle=(float)STATUS1.YAW*0.01125f;
		if(STATUS1.YAW<=0)
		Angle=360+(float)STATUS1.YAW*0.01125f;	
				
		GUI_Arc9(x, y,50, Angle1,Angle1+20, Black);
		GUI_Arc9(x, y,40, Angle1,Angle1+20, Black);
		GUI_Arc9(x, y,50, Angle,Angle+20, Yellow);
		GUI_Arc9(x, y,40, Angle,Angle+20, Yellow);
		Angle1=Angle;
		Delay(5000);
				
}

u8 Wave_cnt=0;
u16 Wave_ROL[160],Wave_PIT[160],Wave_YAW[160];
u16 bb=80,cc=0,dd=0;
void WaveForm_Data(u16 Pr3D_X,u16 Pr3D_Y)
{
				
				Wave_cnt+=1;
				if(Wave_cnt==2)
				{
					Wave_cnt=0;
					if(!(cc==160))
					{	
						
					Wave_ROL[cc]=STATUS1.ROL/250+110;
					if(Wave_ROL[cc]>=Sp3D_Y-45&&Wave_ROL[cc]<=Sp3D_Y+50)
					{			
						if(cc==0)TFT_DrawPoint(bb+cc,Wave_ROL[cc],Green);
						if(cc>0)TFT_DrawLine(bb+cc-1,Wave_ROL[cc-1],bb+cc,Wave_ROL[cc],Green);
					}
					
					Wave_PIT[cc]=STATUS1.PIT/250+110;
					if(Wave_PIT[cc]>=Sp3D_Y-45&&Wave_PIT[cc]<=Sp3D_Y+50)
					{
						if(cc==0)TFT_DrawPoint(bb+cc,Wave_PIT[cc],Green);
						if(cc>0)TFT_DrawLine(bb+cc-1,Wave_PIT[cc-1],bb+cc,Wave_PIT[cc],Yellow);
					}
					
					Wave_YAW[cc]=STATUS1.YAW/250+110;
					if(Wave_YAW[cc]>=Sp3D_Y-45&&Wave_YAW[cc]<=Sp3D_Y+50)
					{						
						if(cc==0)TFT_DrawPoint(bb+cc,Wave_YAW[cc],Green);
						if(cc>0)TFT_DrawLine(bb+cc-1,Wave_YAW[cc-1],bb+cc,Wave_YAW[cc],White);
					}					
					cc+=1;
					}
					
					if(cc==160)
					{
					
					for(dd=0;dd<159;dd++)
					if(Wave_ROL[dd]>=Sp3D_Y-45&&Wave_ROL[dd]<=Sp3D_Y+50)
					TFT_DrawLine(bb+dd,Wave_ROL[dd],bb+dd+1,Wave_ROL[dd+1],Black);
					
					for(dd=0;dd<159;dd++)
					Wave_ROL[dd]=Wave_ROL[dd+1];
					Wave_ROL[159]=STATUS1.ROL/250+110;
					
					for(dd=0;dd<159;dd++)
					if(Wave_ROL[dd]>=Sp3D_Y-45&&Wave_ROL[dd]<=Sp3D_Y+50)
					TFT_DrawLine(bb+dd,Wave_ROL[dd],bb+dd+1,Wave_ROL[dd+1],Green);
					
					for(dd=0;dd<159;dd++)
					if(Wave_PIT[dd]>=Sp3D_Y-45&&Wave_PIT[dd]<=Sp3D_Y+50)
					TFT_DrawLine(bb+dd,Wave_PIT[dd],bb+dd+1,Wave_PIT[dd+1],Black);
					
					for(dd=0;dd<159;dd++)
					Wave_PIT[dd]=Wave_PIT[dd+1];
					Wave_PIT[159]=STATUS1.PIT/250+110;
					
					for(dd=0;dd<159;dd++)
					if(Wave_PIT[dd]>=Sp3D_Y-45&&Wave_PIT[dd]<=Sp3D_Y+50)
					TFT_DrawLine(bb+dd,Wave_PIT[dd],bb+dd+1,Wave_PIT[dd+1],Yellow);
										
					for(dd=0;dd<159;dd++)
					if(Wave_YAW[dd]>=Sp3D_Y-45&&Wave_YAW[dd]<=Sp3D_Y+50)
					TFT_DrawLine(bb+dd,Wave_YAW[dd],bb+dd+1,Wave_YAW[dd+1],Black);
					
					for(dd=0;dd<159;dd++)
					Wave_YAW[dd]=Wave_YAW[dd+1];
					Wave_YAW[159]=STATUS1.YAW/250+110;
					
					for(dd=0;dd<159;dd++)
					if(Wave_YAW[dd]>=Sp3D_Y-45&&Wave_YAW[dd]<=Sp3D_Y+50)
					TFT_DrawLine(bb+dd,Wave_YAW[dd],bb+dd+1,Wave_YAW[dd+1],White);
					
					}				
				}
				TFT_PutStr(Sp3D_X-47,Sp3D_Y-50,"10000",ASCII1206,White, Black);
				TFT_PutStr(Sp3D_X-47,Sp3D_Y-5,"0",ASCII1206,White, Black);
				TFT_PutStr(Sp3D_X-50,Sp3D_Y+40,"-10000",ASCII1206,White, Black);			
}

void WaveForm_Window(u16 Pr3D_X,u16 Pr3D_Y)
{
		
		u8 i,j;
		bb=80;
		for(i=1;i<16;i++)
			for(j=1;j<11;j++)
//		TFT_DrawPoint(80+10*i,60+10*j,White);
		
		TFT_DrawLineY(Sp3D_X-55,Sp3D_Y-48,100,White);
		TFT_DrawLineX(Sp3D_X-55,Sp3D_Y+52,150,White);
		TFT_PutStr(Sp3D_X-47,Sp3D_Y-50,"10000",ASCII1206,White, Black);
		TFT_PutStr(Sp3D_X-47,Sp3D_Y-5,"0",ASCII1206,White, Black);
		TFT_PutStr(Sp3D_X-50,Sp3D_Y+40,"-10000",ASCII1206,White, Black);
}

void Angle_Window(u16 x,u16 y)
{	
		Title(110,185, " Angle ", 100,50,ASCII1206,White, Black);
		TFT_PutStr(110,190," rol ",ASCII1206,White, Black);
		TFT_PutStr(110,205," pit ",ASCII1206,White, Black);
		TFT_PutStr(110,220," yaw ",ASCII1206,White, Black);
}
void Angle_Data(u16 x,u16 y)
{
	TFT_PutViriable(145,193,STATUS1.ROL,4,White, Black);
	TFT_PutViriable(145,208,STATUS1.PIT,4,White, Black);
	TFT_PutViriable(145,223,STATUS1.YAW,5,White, Black);

}


void ACCGRYO_Window(u16 x,u16 y)
{
		Title(10,185, " Acc ", 100,50,ASCII1206,White, Black);
		Title(210,185, " Gyr ", 100,50,ASCII1206,White, Black);
		Title(110,185, " Angle ", 100,50,ASCII1206,White, Black);
		Button(63,193,"Reset",35,35,ASCII1206,Yellow, Black);
		Button(263,193,"Reset",35,35,ASCII1206,Yellow, Black);
}
void ACCGRYO_Data(u16 x,u16 y)
{
	TFT_PutViriable(20,193,SENSOR1.ACC_X,4,White, Black);
	TFT_PutViriable(20,208,SENSOR1.ACC_Y,4,White, Black);
	TFT_PutViriable(20,223,SENSOR1.ACC_Z,4,White, Black);

	TFT_PutViriable(220,193,SENSOR1.GYRO_X,4,White, Black);
	TFT_PutViriable(220,208,SENSOR1.GYRO_Y,4,White, Black);
	TFT_PutViriable(220,223,SENSOR1.GYRO_Z,5,White, Black);
}
void RC_Window(u16 x,u16 y)
{
	Title(10,35, " RC ", 55,140,ASCII1206,White, Black);
	
}
void RC_Data(u16 x,u16 y)
{
	TFT_PutStr(18,50, "  thr  ", ASCII1206,White, Red);
	TFT_PutStr(18,80, "  yaw  ", ASCII1206,White, Red);
	TFT_PutStr(18,110, "  rol  ", ASCII1206,White, Red);
	TFT_PutStr(18,140, "  pit  ", ASCII1206,White, Red);
	
	TFT_PutViriable(22,65, RCDATA1.THR, 4,White, Black);
	TFT_PutViriable(22,125, RCDATA1.ROL, 4,White, Black);
	TFT_PutViriable(22,95, RCDATA1.YAW, 4,White, Black);
	TFT_PutViriable(22,155, RCDATA1.PIT, 4,White, Black);
}
void Moto_Window(u16 x,u16 y)
{
	Title(252,35, " MOTO ", 60,140,ASCII1206,White, Black);
	
}
void Moto_Data(u16 x,u16 y)
{
	TFT_PutStr(263,50, "  M1  ", ASCII1206,White, Red);
	TFT_PutStr(263,80, "  M2  ", ASCII1206,White, Red);
	TFT_PutStr(263,110, "  M3  ", ASCII1206,White, Red);
	TFT_PutStr(263,140, "  M4  ", ASCII1206,White, Red);
	
	TFT_PutViriable(267,65, PWM1.Moto_1, 4,White, Black);
	TFT_PutViriable(267,125, PWM1.Moto_2, 4,White, Black);
	TFT_PutViriable(267,95, PWM1.Moto_3, 4,White, Black);
	TFT_PutViriable(267,155, PWM1.Moto_4, 4,White, Black);
}

void BAT_Window(u16 x,u16 y)
{
//		TFT_PutStr(20,15, " FLY-BAT ", ASCII1206,White, Black);
//		TFT_PutStr(95,15, " 50% ", ASCII1206,White, Black);
//		TFT_DrawRectangle( 69,14,25,13, White );
		TFT_PutStr(215,15, " BAT ", ASCII1206,White, Black);
		TFT_PutStr(275,15, " 100% ", ASCII1206,White, Black);
		TFT_DrawRectangle( 249,14,25,13, White );
}

void BAT_Data(u16 x,u16 y)
{
//		TFT_PutStr(70,15, "  ", ASCII1206,White, Red);
		TFT_PutStr(250,15,"    ", ASCII1206,White, Green);
}


