#include "stm32f10x.h"
#include "PWM.h"

void Motor_Init(void)
{
	 PWM_Init1();
	 GPIO_InitTypeDef GPIO_InitStructure6;
   GPIO_InitStructure6.GPIO_Pin = GPIO_Pin_8| GPIO_Pin_11;  //TIM8的通道引脚  CH1,CH2，CH3,CH4 (PWM5-PWM6)
   GPIO_InitStructure6.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_InitStructure6.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA, &GPIO_InitStructure6);
}

void Motor1(uint16_t compare)
{
	PWM_TIM8_Setcompare1(compare);  //CH1_PC6
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);
}
