#include "usart_dt.h"
#include "lcd.h"
#include "usart.h"

STATUS STATUS1;
SENSOR SENSOR1;
RCDATA RCDATA1;
PWM PWM1;
PID PID_ROL,PID_PIT,PID_YAW;

void Data_Receive_Anl(u8 *data_buf,u8 num)
{
	vs16 rc_value_temp;
	u8 sum = 0;
	u8 i=0;
	for(i=0;i<(num-1);i++)
		sum += *(data_buf+i);
	if(!(sum==*(data_buf+num-1)))		return;		//判断sum
	
	if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAA))		return;		//判断帧头，上位机发给飞控AAAF
/////////////////////////////////////////////////////////////////////////////////////
	if(*(data_buf+2)==0X01)//command
	{
		STATUS1.ROL = (vs16)(*(data_buf+4)<<8)|*(data_buf+5);//int16 thr
		STATUS1.PIT = (vs16)(*(data_buf+6)<<8)|*(data_buf+7);
		STATUS1.YAW = (vs16)(*(data_buf+8)<<8)|*(data_buf+9);
		if(*(data_buf+10)==0XA0) STATUS1.ARMED=0;
		else STATUS1.ARMED=1;
	}
	if(*(data_buf+2)==0X02)//Command
	{
		SENSOR1.ACC_X = (vs16)(*(data_buf+4)<<8)|*(data_buf+5);//int16 thr
		SENSOR1.ACC_Y = (vs16)(*(data_buf+6)<<8)|*(data_buf+7);
		SENSOR1.ACC_Z = (vs16)(*(data_buf+8)<<8)|*(data_buf+9);
		SENSOR1.GYRO_X = (vs16)(*(data_buf+10)<<8)|*(data_buf+11);//int16 thr
		SENSOR1.GYRO_Y = (vs16)(*(data_buf+12)<<8)|*(data_buf+13);
		SENSOR1.GYRO_Z = (vs16)(*(data_buf+14)<<8)|*(data_buf+15);
		SENSOR1.MAG_X = (vs16)(*(data_buf+16)<<8)|*(data_buf+17);
		SENSOR1.MAG_Y = (vs16)(*(data_buf+18)<<8)|*(data_buf+19);
		SENSOR1.MAG_Z = (vs16)(*(data_buf+20)<<8)|*(data_buf+21);		
	}

	if(*(data_buf+2)==0X03)//RCDATA
	{
		RCDATA1.THR = (vs16)(*(data_buf+4)<<8)|*(data_buf+5);//int16 thr
		RCDATA1.YAW = (vs16)(*(data_buf+6)<<8)|*(data_buf+7);
		RCDATA1.ROL = (vs16)(*(data_buf+8)<<8)|*(data_buf+9);
		RCDATA1.PIT = (vs16)(*(data_buf+10)<<8)|*(data_buf+11);
		RCDATA1.AUX1 = (vs16)(*(data_buf+12)<<8)|*(data_buf+13);
		RCDATA1.AUX2 = (vs16)(*(data_buf+14)<<8)|*(data_buf+15);
		RCDATA1.AUX3 = (vs16)(*(data_buf+16)<<8)|*(data_buf+17);
		RCDATA1.AUX4 = (vs16)(*(data_buf+18)<<8)|*(data_buf+19);
		RCDATA1.AUX5 = (vs16)(*(data_buf+20)<<8)|*(data_buf+21);
		RCDATA1.AUX6 = (vs16)(*(data_buf+21)<<8)|*(data_buf+22);		
	}
	
	if(*(data_buf+2)==0X06)//RCDATA
	{
	
	PWM1.Moto_1 = (vs16)(*(data_buf+4)<<8)|*(data_buf+5);//
	PWM1.Moto_2 = (vs16)(*(data_buf+6)<<8)|*(data_buf+7);//
	PWM1.Moto_3 = (vs16)(*(data_buf+8)<<8)|*(data_buf+9);//
	PWM1.Moto_4 = (vs16)(*(data_buf+10)<<8)|*(data_buf+11);//
	}
	
	
	if(*(data_buf+2)==0X10)								//PID1
	{
			PID_ROL.P = (float)((vs16)(*(data_buf+4)<<8)|*(data_buf+5))/100;
			PID_ROL.I = (float)((vs16)(*(data_buf+6)<<8)|*(data_buf+7))/1000;
			PID_ROL.D = (float)((vs16)(*(data_buf+8)<<8)|*(data_buf+9))/100;
			PID_PIT.P = (float)((vs16)(*(data_buf+10)<<8)|*(data_buf+11))/100;
			PID_PIT.I = (float)((vs16)(*(data_buf+12)<<8)|*(data_buf+13))/1000;
			PID_PIT.D = (float)((vs16)(*(data_buf+14)<<8)|*(data_buf+15))/100;
			PID_YAW.P = (float)((vs16)(*(data_buf+16)<<8)|*(data_buf+17))/100;
			PID_YAW.I = (float)((vs16)(*(data_buf+18)<<8)|*(data_buf+19))/100;
			PID_YAW.D = (float)((vs16)(*(data_buf+20)<<8)|*(data_buf+21))/100;
	}
}

void Uart_DTSend_Buf(unsigned char *DataToSend , u8 data_num)
{
	Usart1_Send_Buf(DataToSend,data_num);
}
void NRF_DTSend_Buf(unsigned char *DataToSend , u8 data_num)
{
	#ifdef	DT_USE_NRF_SPI1
		NRF_TxPacket_AP(DataToSend,data_num);
	#endif
	#ifdef	DT_USE_NRF_SPI2
		NRF2_TxPacket_AP(DataToSend,data_num);
	#endif
}
#include "lcd.h"
void Uart_CheckEvent(void)		//负责与上位机通信,检查上位机是否有数据要发送
{
	
	if(Rx_Ok0)
	{
		Rx_Ok0 = 0;
		Data_Receive_Anl(Rx_Buf[0],Rx_Buf[0][3]+5);		
	}
	if(Rx_Ok1)
	{
		Rx_Ok1 = 0;
		Data_Receive_Anl(Rx_Buf[0],Rx_Buf[0][3]+5);	
	}
	
}

