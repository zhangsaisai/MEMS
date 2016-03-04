#ifndef _USART1_H_
#define _USART1_H_
#include "stm32f10x.h"
#include "sysconfig.h"
#include "usart2.h"

#define Type_B 2    // �L���ƤG�i��
#define Type_O 8    // �L���ƤK�i��
#define Type_D 10   // �L���ƤQ�i��
#define Type_H 16   // �L���ƤQ���i��
#define Type_I 0    // ������

extern u8 Rx_Buf[2][32];	//����32�ֽڵĴ��ڽ��ջ���
extern u8 Rx_Ok0;		//������ϱ�־
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
