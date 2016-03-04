#include "stm32f10x.h"
#include "Contral.h"
#include "usart1.h"
#define ADC1_DR_Address    ((u32)0x4001244C)

int16_t AD[4]={0};            //���4·ADC��ת��ֵ��12λ��
unsigned char RX[1]={0};           //��Ž��յ���һ���ֽ�
unsigned char TX[9]={0};//��ŷ���ľŸ��ֽڣ��������£�
						  //��һ�ֽڴ��AD[0]�ĸ���λ���ڶ��ֽڴ��AD[0]�ĵͰ�λ
              //�����ֽڴ��AD[1]�ĸ���λ�������ֽڴ��AD[1]�ĵͰ�λ
              //�����ֽڴ��AD[2]�ĸ���λ�������ֽڴ��AD[2]�ĵͰ�λ
						  //�����ֽڴ��AD[3]�ĸ���λ���ڰ��ֽڴ��AD[3]�ĵͰ�λ
						  //�ھ��ֽڸ���λ��Ų��뿪��ֵ������λ��3λS2��2λS3��1λAS1��0λAS2

void ADC_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;		
	ADC_InitTypeDef ADC_InitStructure;	 
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_ADC1 , ENABLE);
	
	// ����ADģ������˿ڣ�PC0��1��2��3��Ϊģ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  //ģ������
	GPIO_Init(GPIOA, &GPIO_InitStructure);		

  // ADC1 configuration
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	       //ADC1�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;		           //ģ��ת��������ɨ��ģʽ����ͨ����ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	       //ģ��ת��������ѭ��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//ѡ���������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;             //ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 4;                            //�涨��˳����й���ת����ADCͨ������ĿΪ4��
	ADC_Init(ADC1, &ADC_InitStructure);
	
	// ADC1 regular channels configuration [����ָ�� ADC �Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ�� ]
   ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );	  //ͨ��10��PC0�����Ȳɼ�������ʱ��239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );	  //ͨ��11��PC1����֮�ɼ�������ʱ��239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5 );	  //ͨ��12��PC2����֮�ɼ�������ʱ��239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5 );	  //ͨ��13��PC3����֮�ɼ�������ʱ��239.5����
	
	ADC_DMACmd(ADC1, ENABLE);		 // Enable ADC1 DMA transfer
	// Enable ADC1  
	ADC_Cmd(ADC1, ENABLE);					 //ע�⣺���� ADC_Cmd ֻ�������� ADC ���ú���֮�󱻵��á�
	// Reset the ADC1 Calibration registers */
	ADC_ResetCalibration(ADC1);
	//���ADC1У׼�Ĵ�����ʼ���Ƿ����
	while(ADC_GetResetCalibrationStatus(ADC1));	
	// Start the ADC2 Calibration */ 
	ADC_StartCalibration(ADC1);
	//����Ƿ����У׼
	while(ADC_GetCalibrationStatus(ADC1));	
	/* �������ת�������������ȥ*/ 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void DMA_Configuration(void)
{
	DMA_InitTypeDef DMA_InitStructure;	 
	      
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  /* DMA channel1 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel1);		                                  //��DMA Channel1�Ĵ�����ֵ����Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;			//�����ַ 
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)AD;	                //��������ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;					    //���ͷ���������Ϊ���ݴ������Դ
	DMA_InitStructure.DMA_BufferSize = 4;								            //�����ڴ��С��4��16λ����һ��DMAֻ��4����
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ�Ĵ����ĵ�ַ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;				  //�����ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//ADC1ת����������16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//���͵�Ŀ�ĵ�ַ��16λ���
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	//������ѭ������ģʽ������������Ҫ��ĸ�����ѭ��
																					        //ADCΪ�����������ֻ����һ�Σ���ѭ��ɨ��ת������������ҲҪѭ�� 	
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//DMA Channel1���и����ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;				//DMA Channel1û������Ϊ�ڴ浽�ڴ�Ĵ���
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	DMA_Cmd(DMA1_Channel1, ENABLE);   
}


void Send(void)
{		
	
	TX[1] = AD[0];    //�Ͱ�λ	
	TX[0] = AD[0]>>8; //����λ
	TX[3] = AD[1];    //�Ͱ�λ	
	TX[2] = AD[1]>>8; //����λ
	TX[5] = AD[2];    //�Ͱ�λ	
	TX[4] = AD[2]>>8; //����λ	
	TX[7] = AD[3];    //�Ͱ�λ	
	TX[6] = AD[3]>>8; //����λ	
	
}	