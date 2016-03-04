#ifndef _USART3_H_
#define _USART3_H_
#include "stm32f10x.h"
#include "usart1.h"

void Uart3_Init(u32 br_num);
void Uart3_IRQ(void);

uint8_t Uart3_Put_Char(unsigned char DataToSend);
void Usart3_Send_Buf(unsigned char *DataToSend , u8 data_num);

#endif
