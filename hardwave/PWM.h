#ifndef __PWM_H
#define __PWM_H
#include"stm32f10x.h"

void PWM_Init(void);
void PWM_Init1(void);


// 占空比设置函数（保持原样）
void PWM_TIM1_Setcompare1(uint16_t compare); //TIM1的CH1的PWM输出

void PWM_TIM1_Setcompare2(uint16_t compare); //TIM1的CH2的PWM输出

void PWM_TIM1_Setcompare3(uint16_t compare); //TIM1的CH3的PWM输出

void PWM_TIM1_Setcompare4(uint16_t compare); //TIM1的CH4的PWM输出


void PWM_TIM3_Setcompare1(uint16_t compare); //TIM3的CH1的PWM输出

void PWM_TIM3_Setcompare2(uint16_t compare); //TIM3的CH2的PWM输出

void PWM_TIM3_Setcompare3(uint16_t compare); //TIM3的CH3的PWM输出

void PWM_TIM3_Setcompare4(uint16_t compare); //TIM3的CH4的PWM输出






void PWM_TIM8_Setcompare1(uint16_t compare); //TIM8的CH1的PWM输出

void PWM_TIM8_Setcompare2(uint16_t compare); //TIM8的CH2的PWM输出

void PWM_TIM8_Setcompare3(uint16_t compare); //TIM8的CH3的PWM输出

void PWM_TIM8_Setcompare4(uint16_t compare); //TIM8的CH4的PWM输出



void PWM_TIM2_Setcompare1(uint16_t compare); //TIM2的CH1的PWM输出

void PWM_TIM2_Setcompare2(uint16_t compare); //TIM2的CH2的PWM输出



#endif