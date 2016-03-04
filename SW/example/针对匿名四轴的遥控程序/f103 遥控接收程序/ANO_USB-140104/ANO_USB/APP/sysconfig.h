#ifndef _SYSCONFIG_H_
#define _SYSCONFIG_H_
#include "stm32f10x.h"
#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

#define DT_USE_NRF_SPI1
//#define DT_USE_NRF_SPI2
//#define DT_USE_USART2
#define DT_USE_USART3
//#define RC_USE_PPM


#endif
