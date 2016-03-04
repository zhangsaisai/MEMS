#include "touch.h" 
#include "lcd.h"
#include "delay.h"	 
#include "spi.h"
#include "touchevent.h"
// A/D ͨ��ѡ�������ֺ͹����Ĵ���
#define	CHX 	0x90//0x90 	//ͨ��Y+��ѡ�������	//0x94
#define	CHY 	0xD0//0xd0	//ͨ��X+��ѡ�������	//0xD4

/*=====================================================================*/

void SPI_Config(void);
unsigned char SPI_WriteByte(unsigned char data);
u16 distence(u16 data1,u16 data2);
static void ADS7843_Rd_Addata(u16 *X_Addata,u16 *Y_Addata);
u16 TPReadX(void);
u16 TPReadY(void);

void ADS7843_InterruptConfig(void);

/*=====================================================================*/

void ADS7843_Init(void)
{
    SPI_Config();
    //ADS7843_InterruptConfig();
}
/*=====================================================================*/
/*=====================================================================*/


void SPI_Config(void) 
{ 
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Enable SPI2 and GPIO clocks */
  RCC_AHB1PeriphClockCmd(RCC_SPI2_PORT|RCC_AHB1Periph_GPIOA, ENABLE);

  /*!< SPI Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_SPI2_CLK, ENABLE);

  GPIO_PinAFConfig(SPI2_GPIO_PORT, SPI2_SCK_SOURCE, GPIO_AF_SPI2);
  GPIO_PinAFConfig(SPI2_GPIO_PORT, SPI2_MISO_SOURCE, GPIO_AF_SPI2);
  GPIO_PinAFConfig(SPI2_GPIO_PORT, SPI2_MOSI_SOURCE, GPIO_AF_SPI2);
      
  /*!< Configure  pins: SCK */
  GPIO_InitStructure.GPIO_Pin = SPI2_SCK;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;
  GPIO_Init(SPI2_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure  pins: MISO */
  GPIO_InitStructure.GPIO_Pin = SPI2_MISO;
  GPIO_Init(SPI2_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure  pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = SPI2_MOSI;
  GPIO_Init(SPI2_GPIO_PORT, &GPIO_InitStructure);

  //Configure PF10 pin: TP_CS pin 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  	//�������
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;     //GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB,&GPIO_InitStructure); 
  ADS7843_CS_HIGH() ;     // TPCSƬѡĬ��Ϊ��
    
  /* Configure PG.07 as input For TP_IRQ*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;            //��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA,&GPIO_InitStructure);

  /* SPI configuration *///��ʼ��SPI�ṹ��
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI1����Ϊ����ȫ˫��
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //����SPI1Ϊ��ģʽ
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //SPI���ͽ���8λ֡�ṹ
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; //����ʱ���ڲ�����ʱ��ʱ��Ϊ�͵�ƽ
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; //��һ��ʱ���ؿ�ʼ��������
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS�ź��������ʹ��SSIλ������
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //SPI������Ԥ��ƵֵΪ8
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //���ݴ����MSBλ��ʼ
  SPI_InitStructure.SPI_CRCPolynomial = 7; //CRCֵ����Ķ���ʽ
  SPI_Init(SPI2, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPI2�Ĵ���
  
  /* Enable SPI2  *///ʹ��SPI2����
  SPI_Cmd(SPI2, ENABLE);

  //�ر�ͬһ��SPI�ܽŵ�����SPI�豸
//  RCC_AHB1PeriphClockCmd(RCC_NRF24L01_CSN, ENABLE);          //ʹ��GPIO��ʱ��
//  GPIO_InitStructure.GPIO_Pin = NRF24L01_CSN;      
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;           //�������
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
//  GPIO_Init(GPIO_NRF24L01_CSN, &GPIO_InitStructure);
}

/*=====================================================================*/
unsigned char SPI_WriteByte(unsigned char data) 
{ 
 unsigned char Data = 0; 

   //Wait until the transmit buffer is empty 
  while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET); 
  // Send the byte  
  SPI_I2S_SendData(SPI2,data); 

   //Wait until a data is received 
  while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET); 
  // Get the received data 
  Data = SPI_I2S_ReceiveData(SPI2); 

  // Return the shifted data 
  return Data; 
}  


/*=====================================================================*/
/*
#define ShortDelayTime 1
#define LongDelayTime (ShortDelayTime*2)
SPI1_Delay_Short()
{
    __IO uint32_t nCount;
    
    for( nCount= 0; nCount < ShortDelayTime; nCount++ );
}
*/
/*=====================================================================*/
/*=====================================================================*/
u16 _AD2Y(u16 adx) //240
{
  u16 sx=0;
  int r = adx - 360;
  r *= 240;
  sx=r / (4096 - 800);
  if (sx<=0 || sx>240)
    return 0;
  return sx;
}

/*=====================================================================*/
u16 _AD2X(u16 ady) //320
{
  u16 sy=0;
  int r = ady - 360;
  r *= 320;
  sy=r/(4096 - 680);
  if (sy<=0 || sy>320)
    return 0;
  return sy;
}
/*=====================================================================*/
u16 TPReadX(void)
{ 
   u16 x=0;
   ADS7843_CS_LOW();
   SPI_WriteByte(CHX);
   x=SPI_WriteByte(0x00);
   x<<=8;
   x+=SPI_WriteByte(0x00);
   ADS7843_CS_HIGH(); 
   x = x>>3;
   return (x);
}

/*=====================================================================*/
u16 TPReadY(void)
{
  u16 y=0;
  ADS7843_CS_LOW();

  SPI_WriteByte(CHY);
  y=SPI_WriteByte(0x00);
  y<<=8;
  y+=SPI_WriteByte(0x00);
  ADS7843_CS_HIGH();
  y = y>>3; 
  return (y);
}

/*=====================================================================*/
#define  times  4
static void ADS7843_Rd_Addata(u16 *X_Addata,u16 *Y_Addata)
{

	u16		i,j,k,x_addata[times],y_addata[times];
    
	for(i=0;i<times;i++)					//����4��.
	{
		x_addata[i] = TPReadX();   //����X���������
		y_addata[i] = TPReadY();   //����X���������
	}
    //����������ĳ����������򵥣�ÿ���õ�ǰ��Ԫ��ͬ����Ԫ�رȽϲ�����
	for(i=0;i<times-1;i++)
	{
    	for(j=i+1;j<times;j++)
    	{
           if(x_addata[j] > x_addata[i])
            {
                k = x_addata[j];
                x_addata[j] = x_addata[i];
                x_addata[i] = k;
            }
         }
    }
    //����������ĳ����������򵥣�ÿ���õ�ǰ��Ԫ��ͬ����Ԫ�رȽϲ�����
	for(i=0;i<times-1;i++)
	{
    	for(j=i+1;j<times;j++)
    	{
           if(y_addata[j] > y_addata[i])
            {
                k = y_addata[j];
                y_addata[j] = y_addata[i];
                y_addata[i] = k;
            }
         }
    }
	
	
	*X_Addata=(x_addata[1] + x_addata[2]) >> 1;
	*Y_Addata=(y_addata[1] + y_addata[2]) >> 1;

}


/*=====================================================================*/
/*=====================================================================*/
u16 distence(u16 data1,u16 data2)
{
    if((data2 > data1 + 2) || (data1 > data2 + 2))
    {
        return 0;
    }

    return 1;    
}

/*=====================================================================*/
void ARMJISHU_TouchScreen_ADS7843(void)
{
  u16 xdata, ydata;
  u32 xScreen, yScreen;
  static u16 sDataX,sDataY;
  static u16 Counter = 0;
    
  ADS7843_Rd_Addata(&xdata, &ydata);

  xScreen = _AD2X(xdata);
  yScreen = _AD2Y(ydata);

  if((xScreen>1)&&(yScreen>1)&&(xScreen<320-1)&&(yScreen<240-1))
  {
      if((Counter % 1024) == 8)
      {
       
      
	  }
//      if((GPIO_ADS7843_INT_VALID) && distence(sDataX,xScreen) && distence(sDataY,yScreen))
//        {
//					TFT_Draw9Point(1+xScreen, 240-yScreen,White);
//        }
      sDataX = xScreen;
      sDataY = yScreen;
	  Counter++;
  }
     Touch_Event(320-xScreen,yScreen);
}
