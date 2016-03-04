#include "stm32f10x.h"
#include "Contral.h"
#include "usart1.h"
#define ADC1_DR_Address    ((u32)0x4001244C)

int16_t AD[4]={0};            //存放4路ADC的转换值（12位）
unsigned char RX[1]={0};           //存放接收到的一个字节
unsigned char TX[9]={0};//存放发射的九个字节，安排如下：
						  //第一字节存放AD[0]的高四位，第二字节存放AD[0]的低八位
              //第三字节存放AD[1]的高四位，第四字节存放AD[1]的低八位
              //第五字节存放AD[2]的高四位，第六字节存放AD[2]的低八位
						  //第七字节存放AD[3]的高四位，第八字节存放AD[3]的低八位
						  //第九字节高四位存放拨码开关值，低四位：3位S2，2位S3，1位AS1，0位AS2

void ADC_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;		
	ADC_InitTypeDef ADC_InitStructure;	 
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_ADC1 , ENABLE);
	
	// 设置AD模拟输入端口（PC0、1、2、3）为模拟输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  //模拟输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);		

  // ADC1 configuration
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	       //ADC1工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;		           //模数转换工作在扫描模式（多通道）模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	       //模数转换工作在循环模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//选择软件触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;             //ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 4;                            //规定了顺序进行规则转换的ADC通道的数目为4。
	ADC_Init(ADC1, &ADC_InitStructure);
	
	// ADC1 regular channels configuration [设置指定 ADC 的规则组通道，设置它们的转化顺序和采样时间 ]
   ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );	  //通道10，PC0，最先采集，采样时间239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );	  //通道11，PC1，次之采集，采样时间239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5 );	  //通道12，PC2，次之采集，采样时间239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5 );	  //通道13，PC3，次之采集，采样时间239.5周期
	
	ADC_DMACmd(ADC1, ENABLE);		 // Enable ADC1 DMA transfer
	// Enable ADC1  
	ADC_Cmd(ADC1, ENABLE);					 //注意：函数 ADC_Cmd 只能在其他 ADC 设置函数之后被调用。
	// Reset the ADC1 Calibration registers */
	ADC_ResetCalibration(ADC1);
	//检测ADC1校准寄存器初始化是否完成
	while(ADC_GetResetCalibrationStatus(ADC1));	
	// Start the ADC2 Calibration */ 
	ADC_StartCalibration(ADC1);
	//检测是否完成校准
	while(ADC_GetCalibrationStatus(ADC1));	
	/* 启动软件转换，这句必须加上去*/ 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void DMA_Configuration(void)
{
	DMA_InitTypeDef DMA_InitStructure;	 
	      
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  /* DMA channel1 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel1);		                                  //将DMA Channel1寄存器的值重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;			//外设地址 
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)AD;	                //储存器地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;					    //传送方向，外设作为数据传输的来源
	DMA_InitStructure.DMA_BufferSize = 4;								            //传送内存大小，4个16位，即一次DMA只传4个数
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址寄存器的地址不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;				  //传送内存地址递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//ADC1转换的数据是16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//传送的目的地址是16位宽度
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	//工作在循环缓存模式，即，传输完要求的个数后循环
																					        //ADC为软件启动（且只启动一次），循环扫描转换，所以这里也要循环 	
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//DMA Channel1具有高优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;				//DMA Channel1没有设置为内存到内存的传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	DMA_Cmd(DMA1_Channel1, ENABLE);   
}


void Send(void)
{		
	
	TX[1] = AD[0];    //低八位	
	TX[0] = AD[0]>>8; //高四位
	TX[3] = AD[1];    //低八位	
	TX[2] = AD[1]>>8; //高四位
	TX[5] = AD[2];    //低八位	
	TX[4] = AD[2]>>8; //高四位	
	TX[7] = AD[3];    //低八位	
	TX[6] = AD[3]>>8; //高四位	
	
}	