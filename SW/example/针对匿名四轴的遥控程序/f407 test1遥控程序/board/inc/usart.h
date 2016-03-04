#ifndef __USART_H
#define __USART_H

#include "stm32f4xx_conf.h"

extern u8 Rx_Buf[2][32];	//����32�ֽڵĴ��ڽ��ջ���
extern u8 Rx_Ok0;		//������ϱ�־
extern u8 Rx_Ok1;

void Uart1_Init(u32 BaudRate);
uint8_t Uart1_Put_Char(unsigned char DataToSend);
void Uart1_IRQ(void);
void Usart1_Send_Buf(unsigned char *DataToSend , u8 data_num);
void Nvic_Init(void);
#endif

