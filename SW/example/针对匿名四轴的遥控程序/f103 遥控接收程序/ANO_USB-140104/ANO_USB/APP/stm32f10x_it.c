/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp.h"
#include "usart_dt.h"
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
/*=====================================================================================================*/
/*=====================================================================================================*/
void USART1_IRQHandler(void)  //�����жϺ���
{
	Uart1_IRQ();
}
#ifdef DT_USE_USART2
void USART2_IRQHandler(void)  //�����жϺ���
{
	Uart2_IRQ();
}
#endif
#ifdef DT_USE_USART3
void USART3_IRQHandler(void)  //�����жϺ���
{
	Uart3_IRQ();
}
#endif
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
#ifdef RC_USE_PPM
void TIM2_IRQHandler(void)
{
	static u8 	RC_Ch = 0;
	static u16 	RC_Value[10];
	
	if(TIM2->SR & TIM_IT_CC1)//if(TIM_GetITStatus(TIM2, TIM_IT_CC1) == SET)
	{
		u16 CC1_Value_Now = TIM2->CCR1;//��ccr,��cc1if��־
		TIM2->CNT = 0;				//��cnt
			if(CC1_Value_Now>3000)	//�ж�ͬ���ź�
				RC_Ch = 0;
			RC_Value[RC_Ch] = CC1_Value_Now;
			RC_Ch++;
			if(RC_Ch==1)
			{

			}
	}	
}
#endif
/*=====================================================================================================*/
/*=====================================================================================================*/

void TIM3_IRQHandler(void)		//0.5ms�ж�һ��
{	
	static u8 ms1 = 0,ms2 = 0,ms5 = 0,ms10 = 0;				//�жϴ���������
	if(TIM3->SR & TIM_IT_Update)		//if ( TIM_GetITStatus(TIM3 , TIM_IT_Update) != RESET ) 
	{     
		TIM3->SR = ~TIM_FLAG_Update;//TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);   //����жϱ�־
		if(!SYS_INIT_OK)		
			return;
		//ÿ���ж϶�ִ��,0.5ms
		ms1++;
		ms2++;
		ms5++;
		ms10++;
		//Nrf_Check_Event();
		if(ms1==2)				//ÿ�����ж�ִ��һ��,1ms
		{
			ms1=0;
		}
		if(ms2==4)				//ÿ�Ĵ��ж�ִ��һ��,2ms
		{
			ms2=0;
		}
		if(ms5==10)
		{
			ms5=0;					//ÿʮ���ж�ִ��һ��,5ms
		}
		if(ms10==20)
		{
			ms10=0;					//û��ʮ���ж�ִ��һ��,10ms
		}
		
	}
}

/*=====================================================================================================*/
/*=====================================================================================================*/
// void EXTI1_IRQHandler(void)
// {
// 	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
// 	{
// 		EXTI_ClearITPendingBit(EXTI_Line1);
// 	}
// }
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
/*=====================================================================================================*/
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{

}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
