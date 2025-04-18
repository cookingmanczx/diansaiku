#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Instructure;
	GPIO_Instructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Instructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Instructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Instructure);
}

uint8_t Key_GetNum(void)
{
	uint8_t num = 0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0)
		Delay_ms(20);
		num = 1;
	}
	return num;
}


