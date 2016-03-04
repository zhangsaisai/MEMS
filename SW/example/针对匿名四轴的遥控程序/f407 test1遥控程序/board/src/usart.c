#include "usart.h"
#include <stdio.h>

static u8 TxBuffer[256];
static u8 TxCounter=0;
static u8 count=0; 
u8 Rx_Buf[2][32];	//两个32字节的串口接收缓存
static u8 Rx_Act=0;		//正在使用的buf号
static u8 Rx_Adr=0;		//正在接收第几字节
u8 Rx_Ok0 = 0;
u8 Rx_Ok1 = 0;

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

void Nvic_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* NVIC_PriorityGroup 1 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//串口
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//初始化串口1
void Uart1_Init(u32 BaudRate)
{
  	 GPIO_InitTypeDef GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;
        USART_ClockInitTypeDef USART_ClockInitStruct;
    
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE); 
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);            //PA9?PA10??????,???? |
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

        /*??PA9?Tx??*/
        GPIO_StructInit(&GPIO_InitStructure);                                                    //?????
        GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
        GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;                                     //?????,???AF,OUT??
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_Init(GPIOA,&GPIO_InitStructure);
            
        /*??PA10?Rx??*/
        GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;                                     //?????
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA,&GPIO_InitStructure);

        /*??USART1,?????Cotex M3??*/
        USART_StructInit(&USART_InitStructure);
        USART_InitStructure.USART_BaudRate =115200;                             //?????
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
        USART_Init(USART1, &USART_InitStructure);
        USART_ClockStructInit(&USART_ClockInitStruct);  
        USART_ClockInit(USART1, &USART_ClockInitStruct);

        USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                            //????
        USART_Cmd(USART1, ENABLE);    
        USART_ClearFlag(USART1, USART_FLAG_TC);
}

void Uart1_IRQ(void)
{

	if(USART1->SR & USART_SR_ORE)//ORE中断
	{
		u8 com_data = USART1->DR;
	}
	//发送中断
	if((USART1->SR & (1<<7))&&(USART1->CR1 & USART_CR1_TXEIE))
	{
		USART1->DR = TxBuffer[TxCounter++]; //写DR清除中断标志          
		if(TxCounter == count)
		{
			USART1->CR1 &= ~USART_CR1_TXEIE;		//关闭TXE中断
		}
	}
	//接收中断 (接收寄存器非空) 
	if(USART1->SR & (1<<5))
	{
		

		u8 com_data = USART1->DR;
		
			if(Rx_Adr==0)		//寻找帧头0XAAAF
			{
				if(com_data==0xAA)	
				{
					Rx_Buf[Rx_Act][0] = com_data;
					Rx_Adr = 1;
				}
			}
			else if(Rx_Adr==1)
			{
				if(com_data==0xAA)	
				{
					Rx_Buf[Rx_Act][1] = com_data;
					Rx_Adr = 2;
				}
				else
					Rx_Adr = 0;
			}
			else if(Rx_Adr==2)		//FUN
			{
				Rx_Buf[Rx_Act][2] = com_data;
				Rx_Adr = 3;
			}
			else if(Rx_Adr==3)		//LEN
			{
				Rx_Buf[Rx_Act][3] = com_data;
				Rx_Adr = 4;
			}
			else
			{
				Rx_Buf[Rx_Act][Rx_Adr] = com_data;
				Rx_Adr ++;
			}
			if(Rx_Adr==Rx_Buf[Rx_Act][3]+5)		//数据接收完毕 数据+非数据
			{
				Rx_Adr = 0;
				if(Rx_Act)	
				{ 
					Rx_Act = 0; 			//切换缓存
					Rx_Ok1 = 1;
				}
				else 				
				{
					Rx_Act = 1;
					Rx_Ok0 = 1;
				}
			}

//		Uart1_Put_Char(com_data);
	}
}
/**************************实现函数********************************************
*******************************************************************************/
uint8_t Uart1_Put_Char(unsigned char DataToSend)
{
	TxBuffer[count++] = DataToSend;
  if(!(USART1->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE); 
	return DataToSend;
}
uint8_t Uart1_Put_Int16(uint16_t DataToSend)
{
	uint8_t sum = 0;
	TxBuffer[count++] = BYTE1(DataToSend);
	TxBuffer[count++] = BYTE0(DataToSend);
	if(!(USART1->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	sum += BYTE1(DataToSend);
	sum += BYTE0(DataToSend);
	return sum;
}

void Uart1_Put_String(unsigned char *Str)
{
	//判断Str指向的数据是否有效.
	while(*Str)
	{
	//是否是回车字符 如果是,则发送相应的回车 0x0d 0x0a
	if(*Str=='\r')Uart1_Put_Char(0x0d);
		else if(*Str=='\n')Uart1_Put_Char(0x0a);
			else Uart1_Put_Char(*Str);
	//指针++ 指向下一个字节.
	Str++;
	}
}
void Usart1_Send_Buf(unsigned char *DataToSend , u8 data_num)
{
	u8 i;
	for(i=0;i<data_num;i++)
		TxBuffer[count++] = *(DataToSend+i);
	if(!(USART1->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE); 
}

