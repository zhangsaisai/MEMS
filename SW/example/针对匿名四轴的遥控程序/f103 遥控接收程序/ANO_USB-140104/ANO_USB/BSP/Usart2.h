#ifndef _USART2_H_
#define _USART2_H_
#include "stm32f10x.h"
#include "usart1.h"

void Uart2_Init(u32 br_num);
void Uart2_IRQ(void);

uint8_t Uart2_Put_Char(unsigned char DataToSend);
void Usart2_Send_Buf(unsigned char *DataToSend , u8 data_num);

#endif
