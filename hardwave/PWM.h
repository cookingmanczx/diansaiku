#ifndef __PWM_H
#define __PWM_H
#include"stm32f10x.h"

void PWM_Init(void);
void PWM_Init1(void);


// ռ�ձ����ú���������ԭ����
void PWM_TIM1_Setcompare1(uint16_t compare); //TIM1��CH1��PWM���

void PWM_TIM1_Setcompare2(uint16_t compare); //TIM1��CH2��PWM���

void PWM_TIM1_Setcompare3(uint16_t compare); //TIM1��CH3��PWM���

void PWM_TIM1_Setcompare4(uint16_t compare); //TIM1��CH4��PWM���


void PWM_TIM3_Setcompare1(uint16_t compare); //TIM3��CH1��PWM���

void PWM_TIM3_Setcompare2(uint16_t compare); //TIM3��CH2��PWM���

void PWM_TIM3_Setcompare3(uint16_t compare); //TIM3��CH3��PWM���

void PWM_TIM3_Setcompare4(uint16_t compare); //TIM3��CH4��PWM���






void PWM_TIM8_Setcompare1(uint16_t compare); //TIM8��CH1��PWM���

void PWM_TIM8_Setcompare2(uint16_t compare); //TIM8��CH2��PWM���

void PWM_TIM8_Setcompare3(uint16_t compare); //TIM8��CH3��PWM���

void PWM_TIM8_Setcompare4(uint16_t compare); //TIM8��CH4��PWM���



void PWM_TIM2_Setcompare1(uint16_t compare); //TIM2��CH1��PWM���

void PWM_TIM2_Setcompare2(uint16_t compare); //TIM2��CH2��PWM���



#endif