/*
 * calculate.h
 *
 *  Created on: Mar 24, 2015
 *      Author: lab
 */

#ifndef CALCULATE_H_
#define CALCULATE_H_

//定义不同测量范围的刻度因子
#define Gyro_250_Scale_Factor   131.0f
#define Gyro_500_Scale_Factor   65.5f
#define Gyro_1000_Scale_Factor  32.8f
#define Gyro_2000_Scale_Factor  16.4f
#define Accel_2_Scale_Factor    16384.0f
#define Accel_4_Scale_Factor    8192.0f
#define Accel_8_Scale_Factor    4096.0f
#define Accel_16_Scale_Factor   2048.0f

#define Kp 2.0f     //proportional gain governs rate of convergence to accelerometer/magnetometer
#define Ki 0.005f   //integral gain governs rate of convergence of gyroscope biases


void Calibration_mag(void);
void Calibration_gyro(void);
void calculate_azimuth_acc(void);

float invSqrt(float x) ;
void init_quaternion(void);
void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);

#endif /* CALCULATE_H_ */
