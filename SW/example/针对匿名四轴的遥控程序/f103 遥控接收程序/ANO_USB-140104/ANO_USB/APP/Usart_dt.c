#include "usart_dt.h"

RCDATA Rc_D;
u8 data_to_send[32];
u8 _cnt=0;
u8 sum = 0;

extern int16_t AD[4]; 

void Data_Send_RCData(void)
{
//	Rc_DValue(&Rc_D);
	u8 i;
	
//	Rc_D.THR= AD[3];//*1000/3500)+1000;//1000~2000
//	Rc_D.YAW= (AD[2]*1000/3500)+1000-80;
//	Rc_D.ROL= (AD[1]*1000/3500)+1000-90;
//	Rc_D.PIT= (AD[0]*1000/3500)+1000-100;
	Rc_D.THR= AD[3];
	Rc_D.YAW= AD[2];
	Rc_D.ROL= AD[1];
	Rc_D.PIT= AD[0];
//	Rc_D.YAW= 1500;
//	Rc_D.ROL=1500;
//	Rc_D.PIT=1500;
	_cnt=0;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAF;
	data_to_send[_cnt++]=0x03;
	data_to_send[_cnt++]=0;
	data_to_send[_cnt++]=BYTE1(Rc_D.THR);
	data_to_send[_cnt++]=BYTE1(Rc_D.THR);
	data_to_send[_cnt++]=BYTE1(Rc_D.YAW);
	data_to_send[_cnt++]=BYTE0(Rc_D.YAW);
	data_to_send[_cnt++]=BYTE1(Rc_D.ROL);
	data_to_send[_cnt++]=BYTE0(Rc_D.ROL);
	data_to_send[_cnt++]=BYTE1(Rc_D.PIT);
	data_to_send[_cnt++]=BYTE0(Rc_D.PIT);
	data_to_send[_cnt++]=BYTE1(Rc_D.AUX1);
	data_to_send[_cnt++]=BYTE0(Rc_D.AUX1);
	data_to_send[_cnt++]=BYTE1(Rc_D.AUX2);
	data_to_send[_cnt++]=BYTE0(Rc_D.AUX2);
	data_to_send[_cnt++]=BYTE1(Rc_D.AUX3);
	data_to_send[_cnt++]=BYTE0(Rc_D.AUX3);
	data_to_send[_cnt++]=BYTE1(Rc_D.AUX4);
	data_to_send[_cnt++]=BYTE0(Rc_D.AUX4);
	data_to_send[_cnt++]=BYTE1(Rc_D.AUX5);
	data_to_send[_cnt++]=BYTE0(Rc_D.AUX5);
	data_to_send[_cnt++]=BYTE1(Rc_D.AUX6);
	data_to_send[_cnt++]=BYTE0(Rc_D.AUX6);
	
	data_to_send[3] = _cnt-4;
	
	sum = 0;
	for(u8 i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
}

u8 ACC_CalOff=0;
u8 GYR_CalOff=0;
void Data_Send_Offset(void)
{
	_cnt=0;
	data_to_send[_cnt++]=0xAA; //0
	data_to_send[_cnt++]=0xAF;//1
	data_to_send[_cnt++]=0x01;//2
	data_to_send[_cnt++]=0;//3
	
	if(ACC_CalOff==1&&GYR_CalOff==0) 
		data_to_send[_cnt++]=0x01;//4 ACC
	else if(GYR_CalOff==1&&ACC_CalOff==0)
		data_to_send[_cnt++]=0x02;//5	GYR
//	else if(GYR_CalOff==1&&ACC_CalOff==1)data_to_send[_cnt++]=0x03;//6 BOTH
//	data_to_send[_cnt++]=0x03;//6 BOTH
	
	data_to_send[3] = _cnt-4;	
	sum = 0;
	for(u8 i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;
}

void Uart_DTSend_Buf(unsigned char *DataToSend , u8 data_num)
{
	Usart3_Send_Buf(DataToSend,data_num);
//	Usart1_Send_Buf(DataToSend,data_num);
	
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

void Uart_CheckEvent(void)		//负责与上位机通信,检查上位机是否有数据要发送
{

//	if(Rx_Ok0)
//	{
//		Rx_Ok0 = 0;
//		NRF_DTSend_Buf(Rx_Buf[0],Rx_Buf[0][3]+5);
//		
//		
//	}
//	if(Rx_Ok1)
//	{
//		Rx_Ok1 = 0;
//		NRF_DTSend_Buf(Rx_Buf[1],Rx_Buf[1][3]+5);	
//		
//	}

		
		if(GYR_CalOff==1||ACC_CalOff==1)
		{		
		Data_Send_Offset();
		GYR_CalOff=0;
		ACC_CalOff=0;
		NRF_DTSend_Buf(data_to_send,_cnt);
		}
		else{
		Data_Send_RCData();
		NRF_DTSend_Buf(data_to_send,_cnt);
		}
}

#define RX_DR			6		//中断标志
#define TX_DS			5
#define MAX_RT			4
void Nrf_Check_Event(void)
{
	u8 sta = NRF_Read_Reg(NRF_READ_REG + NRFRegSTATUS);
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	
	if(sta & (1<<RX_DR))//接收中断
	{
		u8 rx_len = NRF_Read_Reg(R_RX_PL_WID);
		NRF_Read_Buf(RD_RX_PLOAD,NRF24L01_RXDATA,rx_len);
		Uart_DTSend_Buf(NRF24L01_RXDATA,rx_len);
		
	}
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	if(sta & (1<<TX_DS))
	{
		
	}
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	if(sta & (1<<MAX_RT))
	{
		if(sta & 0x01)	//TX FIFO FULL
		{
			NRF_Write_Reg(FLUSH_TX,0xff);
		}
	}
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	NRF_Write_Reg(NRF_WRITE_REG + NRFRegSTATUS, sta);//??nrf??????
	sta = NRF_Read_Reg(NRF_READ_REG + NRFRegSTATUS);
}
void Nrf2_Check_Event(void)
{
	u8 sta = NRF2_Read_Reg(NRF_READ_REG + NRFRegSTATUS);
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	if(sta & (1<<RX_DR))//接收中断
	{
		u8 rx_len = NRF2_Read_Reg(R_RX_PL_WID);
		NRF2_Read_Buf(RD_RX_PLOAD,NRF24L01_2_RXDATA,rx_len);
		Uart_DTSend_Buf(NRF24L01_2_RXDATA,rx_len);
	}
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	if(sta & (1<<TX_DS))
	{
		
	}
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	if(sta & (1<<MAX_RT))
	{
		if(sta & 0x01)	//TX FIFO FULL
		{
			NRF2_Write_Reg(FLUSH_TX,0xff);
		}
	}
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	NRF2_Write_Reg(NRF_WRITE_REG + NRFRegSTATUS, sta);//??nrf??????
	sta = NRF2_Read_Reg(NRF_READ_REG + NRFRegSTATUS);
}
