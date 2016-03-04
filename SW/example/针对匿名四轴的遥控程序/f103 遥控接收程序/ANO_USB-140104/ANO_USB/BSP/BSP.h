#ifndef _BSP_BSP_H_
#define _BSP_BSP_H_
#include "stm32f10x.h"
#include "sysconfig.h"
#include "tim.h"
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "nrf24l01.h"

extern u8 SYS_INIT_OK;

void Nvic_Init(void);

#endif
