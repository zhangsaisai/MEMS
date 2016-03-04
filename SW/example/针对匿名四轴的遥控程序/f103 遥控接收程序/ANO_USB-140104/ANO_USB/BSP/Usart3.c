#include "usart3.h"
#include "Usart_dt.h"
void Uart3_Init(u32 br_num)
{
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //����USART1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	
	
	//Tx
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB , &GPIO_InitStructure);
	//Rx
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB , &GPIO_InitStructure);
	
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
	
	USART_Init(USART3, &USART_InitStructure);
	USART_ClockInit(USART3, &USART_ClockInitStruct);

	//ʹ��USART1�����ж�
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	//ʹ��USART1
	USART_Cmd(USART3, ENABLE); 
}
static u8 TxBuffer[256];
static u8 TxCounter=0;
static u8 count=0; 
void Uart3_IRQ(void)
{
	if(USART3->SR & USART_SR_ORE)//ORE�ж�
	{
		u8 com_data = USART3->DR;
		//USART_ClearFlag(USART1,USART_IT_ORE);
	}
	if((USART3->SR & (1<<7))&&(USART3->CR1 & USART_CR1_TXEIE))
	{
		USART3->DR = TxBuffer[TxCounter++]; //дDR����жϱ�־ 
		if(TxCounter == count)
		{
			USART3->CR1 &= ~USART_CR1_TXEIE;		//�ر�TXE�ж�
		}
	}
	if(USART3->SR & (1<<5))
	{
		u8 com_data = USART3->DR;
		if(com_data==0x12||com_data==0x34||com_data==0x56)
		{
			if (com_data==0x12) {
	ACC_CalOff=1;GYR_CalOff=0;}
			if (com_data==0x34) {
	GYR_CalOff=1;ACC_CalOff=0;}
			if (com_data==0x56) {
	ACC_CalOff=1;GYR_CalOff=1;}
		}
		else {ACC_CalOff=0;GYR_CalOff=0;}
//		Uart1_Put_Char(com_data);
	}
}
uint8_t Uart3_Put_Char(unsigned char DataToSend)
{
	TxBuffer[count++] = DataToSend;
  if(!(USART3->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART3, USART_IT_TXE, ENABLE); 
	return DataToSend;
}
void Usart3_Send_Buf(unsigned char *DataToSend , u8 data_num)
{
	for(u8 i=0;i<data_num;i++)
		TxBuffer[count++] = *(DataToSend+i);
	if(!(USART3->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART3, USART_IT_TXE, ENABLE); 
}
