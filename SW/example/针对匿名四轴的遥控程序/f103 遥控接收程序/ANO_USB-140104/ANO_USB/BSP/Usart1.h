#ifndef _USART1_H_
#define _USART1_H_
#include "stm32f10x.h"
#include "sysconfig.h"
#include "usart2.h"

#define Type_B 2    // 礚腹计秈
#define Type_O 8    // 礚腹计秈
#define Type_D 10   // 礚腹计秈
#define Type_H 16   // 礚腹计せ秈
#define Type_I 0    // Τ腹计

extern u8 Rx_Buf[2][32];	//两个32字节的串口接收缓存
extern u8 Rx_Ok0;		//接收完毕标志
extern u8 Rx_Ok1;

void Uart1_Init(u32 br_num);
void Uart1_IRQ(void);

void Uart1_Put_String(unsigned char *Str);
uint8_t Uart1_Put_Char(unsigned char DataToSend);
uint8_t Uart1_Put_Int16(uint16_t DataToSend);
uint8_t Uart1_Put_Float(float DataToSend);
void Usart1_Send_Buf(unsigned char *DataToSend , u8 data_num);
void NumToChar( u8 Type, u8 Num, u8 *CharData, s32 NumData );
#endif
