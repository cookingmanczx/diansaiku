#include "stm32f10x.h"
#include "PWM.h"
#include "stdio.h"

void duoji_Init(void)                        //≥ı ºPWM1
{
	PWM_Init();
}


void duoji1_SetAngle(float Angle)            //PWM1 PE9
{
	 PWM_TIM1_Setcompare1(Angle /180*2000+500);
}

void duoji2_SetAngle(float Angle)           //PWM1 PE11
{
	 PWM_TIM1_Setcompare2(Angle /180*2000+500);
}
void duoji3_SetAngle(float Angle)           //PWM1 PE13
{
	 PWM_TIM1_Setcompare3(Angle /180*2000+500);
}

void duoji4_SetAngle(float Angle)           //PWM1 PE14
{
	 PWM_TIM1_Setcompare4(Angle /180*2000+500);
}
void duoji5_SetAngle(float Angle)           //PWM1 PB0
{
	 PWM_TIM3_Setcompare1(Angle /180*2000+500);
}
void duoji6_SetAngle(float Angle)           //PWM1 PB1
{
	 PWM_TIM3_Setcompare2(Angle /180*2000+500);
}
void duoji7_SetAngle(float Angle)           //PWM4 PD13
{
	 PWM_TIM3_Setcompare3(Angle /180*2000+500);
}
void duoji8_SetAngle(float Angle)           //PWM4 PD14
{
	 PWM_TIM3_Setcompare4(Angle /180*2000+500);
}