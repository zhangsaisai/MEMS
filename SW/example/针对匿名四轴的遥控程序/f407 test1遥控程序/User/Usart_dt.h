#ifndef _USART_DT_H_
#define _USART_DT_H_
#include <stm32f4xx.h>
#include "usart.h"


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

typedef struct{
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
				int16_t Moto_1;
				int16_t Moto_2;
				int16_t Moto_3;
				int16_t Moto_4;}PWM;

typedef struct PID{
				float P;
				float pout;
				float I;
				float iout;
				float D;
				float dout;
				float IMAX;
				float OUT;}PID;


void wave2(u16 CoordiX, u16 CoordiY, u16 Color);

extern STATUS STATUS1;
extern SENSOR SENSOR1;
extern RCDATA RCDATA1;
extern PWM PWM1;
extern PID PID_ROL,PID_PIT,PID_YAW;

void Uart_CheckEvent(void);
void Status_Data();

#endif
