/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "sysconfig.h"
#include "BSP.H"
#include "usart_dt.h"
#include "usart1.h"
#include "usart2.h"
#include "Contral.h"
#define CLI()      __set_PRIMASK(1)  
#define SEI()      __set_PRIMASK(0)

////////////////////////////////////////////////////////////////////////////////
void SYS_INIT(void)
{
	Tim3_Init(500);				//1000=1MS,500=0.5MS
	Uart1_Init(115200);	
	Nvic_Init();					//中断初始化
	#ifdef RC_USE_PPM
		Tim2_Init();					//用于捕捉PPM
	#endif
	#ifdef DT_USE_USART2
		Uart2_Init(115200);
	#endif
	#ifdef DT_USE_USART3
		Uart3_Init(115200);
	#endif
	#ifdef DT_USE_NRF_SPI1
		Nrf24l01_Init(MODEL_RX2,40);
		if(Nrf24l01_Check())	
			Uart1_Put_String("USB_NRF24L01 IS OK !\r\n");
		else 
			Uart1_Put_String("USB_NRF24L01 IS NOT OK !\r\n");
	#endif
	#ifdef DT_USE_NRF_SPI2
		Nrf24l01_2_Init(MODEL_RX2,40);
		if(Nrf24l01_2_Check())	
			Uart1_Put_String("USB_NRF24L01_2 IS OK !\r\n");
		else 
			Uart1_Put_String("USB_NRF24L01_2 IS NOT OK !\r\n");
	#endif
}
////////////////////////////////////////////////////////////////////////////////
u8 FLAG=0;
extern vu16 AD[4]; 

int main(void)
{
	SYS_INIT_OK=0;
	SYS_INIT();
	SYS_INIT_OK=1;
	DMA_Configuration();
	ADC_Configuration();
	while (1)
	{
		FLAG++;
		if(FLAG==20)
		{
		FLAG=0;
		Uart_CheckEvent();
		}
		#ifdef DT_USE_NRF_SPI1			
		Nrf_Check_Event();	
		#endif
		
		#ifdef DT_USE_NRF_SPI2
			Nrf2_Check_Event();
		#endif
		
	}
}
////////////////////////////////////////////////////////////////////////////////

