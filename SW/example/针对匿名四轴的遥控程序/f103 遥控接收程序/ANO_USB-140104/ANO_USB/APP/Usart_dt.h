#ifndef _USART_DT_H_
#define _USART_DT_H_
#include "stm32f10x.h"
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "nrf24l01.h"
#include "nrf24l01_2.h"

typedef struct{
				int16_t ROL;
				int16_t PIT;
				int16_t YAW;
				int32_t ALT;
				int8_t ARMED;}STATUS;
typedef struct{
				int16_t ACC_X;
				int16_t ACC_Y;
				int16_t ACC_Z;
				int16_t GYRO_X;
				int16_t GYRO_Y;
				int16_t GYRO_Z;
				int16_t MAG_X;
				int16_t MAG_Y;
				int16_t MAG_Z;}SENSOR;

typedef struct {
				int16_t THR;
				int16_t YAW;
				int16_t ROL;
				int16_t PIT;
				int16_t AUX1;
				int16_t AUX2;
				int16_t AUX3;
				int16_t AUX4;
				int16_t AUX5;
				int16_t AUX6;}RCDATA;

typedef struct{
				int16_t PWM;}PWM;

extern u8 ACC_CalOff;
extern u8 GYR_CalOff;

void Uart_CheckEvent(void);

void Nrf_Check_Event(void);
void Nrf2_Check_Event(void);
#endif
