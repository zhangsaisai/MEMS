#include "usart1.h"

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

typedef union {unsigned char byte[4];float num;}t_floattobyte;
t_floattobyte floattobyte;

void Uart1_Init(u32 br_num)
{
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //����USART1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
	
	//����PA9��ΪUSART1��Tx
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	//����PA10��ΪUSART1��Rx
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
	//����USART1
	//�жϱ�������
	USART_InitStructure.USART_BaudRate = br_num;       //�����ʿ���ͨ������վ����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //8λ����
	USART_InitStructure.USART_StopBits = USART_StopBits_1;   //��֡��β����1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;    //������żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ��������ʧ��
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;  //���͡�����ʹ��
	//����USART1ʱ��
	USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;  //ʱ�ӵ͵�ƽ�
	USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;  //SLCK������ʱ������ļ���->�͵�ƽ
	USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;  //ʱ�ӵڶ������ؽ������ݲ���
	USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable; //���һλ���ݵ�ʱ�����岻��SCLK���
	
	USART_Init(USART1, &USART_InitStructure);
	USART_ClockInit(USART1, &USART_ClockInitStruct);

	//ʹ��USART1�����ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//ʹ��USART1
	USART_Cmd(USART1, ENABLE); 
}
static u8 TxBuffer[256];
static u8 TxCounter=0;
static u8 count=0; 
u8 Rx_Buf[2][32];	//����32�ֽڵĴ��ڽ��ջ���
static u8 Rx_Act=0;		//����ʹ�õ�buf��
static u8 Rx_Adr=0;		//���ڽ��յڼ��ֽ�
u8 Rx_Ok0 = 0;
u8 Rx_Ok1 = 0;
void Uart1_IRQ(void)
{
	if(USART1->SR & USART_SR_ORE)//ORE�ж�
	{
		u8 com_data = USART1->DR;
	}
	//�����ж�
	if((USART1->SR & (1<<7))&&(USART1->CR1 & USART_CR1_TXEIE))
	{
		USART1->DR = TxBuffer[TxCounter++]; //дDR����жϱ�־          
		if(TxCounter == count)
		{
			USART1->CR1 &= ~USART_CR1_TXEIE;		//�ر�TXE�ж�
		}
	}
	//�����ж� (���ռĴ����ǿ�) 
	if(USART1->SR & (1<<5))  
	{
		u8 com_data = USART1->DR;
		
		#ifdef DT_USE_NRF_SPI1
			#define USE_NRF
		#endif
		#ifdef DT_USE_NRF_SPI2
			#define USE_NRF
		#endif
		#ifdef USE_NRF
			if(Rx_Adr==0)		//Ѱ��֡ͷ0XAAAF
			{
				if(com_data==0xAA)	
				{
					Rx_Buf[Rx_Act][0] = com_data;
					Rx_Adr = 1;
				}
			}
			else if(Rx_Adr==1)
			{
				if(com_data==0xAF)	
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
			if(Rx_Adr==Rx_Buf[Rx_Act][3]+5)		//���ݽ������
			{
				Rx_Adr = 0;
				if(Rx_Act)	
				{ 
					Rx_Act = 0; 			//�л�����
					Rx_Ok1 = 1;
				}
				else 				
				{
					Rx_Act = 1;
					Rx_Ok0 = 1;
				}
			}
			
		#endif
//		#ifdef	DT_USE_USART2
//			Uart2_Put_Char(com_data);
//		#endif
//		#ifdef	DT_USE_USART3
//			Uart3_Put_Char(com_data);
//		#endif
	}
}
/**************************ʵ�ֺ���********************************************
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
uint8_t Uart1_Put_Float(float DataToSend)
{
	uint8_t sum = 0;
	floattobyte.num=DataToSend;
	TxBuffer[count++] = floattobyte.byte[3];  
	TxBuffer[count++] = floattobyte.byte[2];  
	TxBuffer[count++] = floattobyte.byte[1];  
	TxBuffer[count++] = floattobyte.byte[0];  
	if(!(USART1->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	sum += BYTE3(DataToSend);
	sum += BYTE2(DataToSend);
	sum += BYTE1(DataToSend);
	sum += BYTE0(DataToSend);
	return sum;	
}
void Uart1_Put_String(unsigned char *Str)
{
	//�ж�Strָ��������Ƿ���Ч.
	while(*Str)
	{
	//�Ƿ��ǻس��ַ� �����,������Ӧ�Ļس� 0x0d 0x0a
	if(*Str=='\r')Uart1_Put_Char(0x0d);
		else if(*Str=='\n')Uart1_Put_Char(0x0a);
			else Uart1_Put_Char(*Str);
	//ָ��++ ָ����һ���ֽ�.
	Str++;
	}
}
void Usart1_Send_Buf(unsigned char *DataToSend , u8 data_num)
{
	for(u8 i=0;i<data_num;i++)
		TxBuffer[count++] = *(DataToSend+i);
	if(!(USART1->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE); 
}

void NumToChar( u8 Type, u8 Num, u8 *CharData, s32 NumData )
{
  u8 i = 0;
  u32 Tmp[48] = {0};
  u32 NumTmp = 1;

  switch(Type) {

    case Type_B:  // 2�i��
    case Type_O:  // 8�i��
    case Type_D:  // 10�i��
    case Type_H:  // 16�i��
      for(i=0; i<Num; i++) {
        Tmp[i] = ((u32)NumData) / NumTmp;
        NumTmp = NumTmp * Type;
      }
      for(i=0; i<Num; i++) {
        CharData[Num-i-1] = Tmp[i] - Tmp[i+1]*Type;
        if(CharData[Num-i-1]>9)
          CharData[Num-i-1] += 55;  // 65-10
        else
          CharData[Num-i-1] += 48;
      }
      CharData[Num] = '\0';
      break;

    case Type_I:  // 10�i��, �����t��
      if(NumData<0) {
        CharData[0] = '-';
        NumData = (~NumData) + 1;
        for(i=1; i<Num+1; i++) {
        Tmp[i-1] = ((u32)NumData) / NumTmp;
          NumTmp = NumTmp * 10;
        }
        for(i=1; i<Num+1; i++) {
        CharData[Num-i+1] = Tmp[i-1] - Tmp[i]*10;
          CharData[Num-i+1] += 48;
        }
        CharData[Num+1] = '\0';
      }
      else {
        CharData[0] = '+';
        //NumData = (~NumData) + 1;
        for(i=1; i<Num+1; i++) {
          Tmp[i-1] = ((u32)NumData) / NumTmp;
          NumTmp = NumTmp * 10;
        }
        for(i=1; i<Num+1; i++) {
          CharData[Num-i+1] = Tmp[i-1] - Tmp[i]*10;
          CharData[Num-i+1] += 48;
        }
        CharData[Num+1] = '\0';
      }
      break;

//     case Type_F:  // 10�i��, �B�I��
//         
//       break;
  }
}
