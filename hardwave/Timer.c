#include "stm32f10x.h"
#include "Encoder.h"
#include "stdio.h"

//volatile int16_t Encoder_Speed;
volatile float Encoder_Speed;
//volatile int16_t Encoder_Speed1;
volatile float Encoder_Speed1;

volatile float Car_Speed;

void Timer_Init()
{
	Encoder_Init();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure7;				//定义结构体变量
	TIM_TimeBaseInitStructure7.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure7.TIM_CounterMode = TIM_CounterMode_Up;	//计数器模式，选择向上计数
	TIM_TimeBaseInitStructure7.TIM_Period = 100 - 1;				//计数周期，即ARR的值
	TIM_TimeBaseInitStructure7.TIM_Prescaler =7200 - 1;				//预分频器，即PSC的值
	TIM_TimeBaseInitStructure7.TIM_RepetitionCounter = 0;			//重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure7);				//将结构体变量交给TIM_TimeBaseInit，配置TIM4的时基单元	
	
	
	
	/*中断输出配置*/
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);						//清除定时器更新标志位
																
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);					//开启TIM4的更新中断
	
	
	
	
	/*NVIC中断分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//配置NVIC为分组2															
																
	/*NVIC配置*/
	NVIC_InitTypeDef NVIC_InitStructure1;						//定义结构体变量
	NVIC_InitStructure1.NVIC_IRQChannel = TIM4_IRQn;				//选择配置NVIC的TIM2线
	NVIC_InitStructure1.NVIC_IRQChannelCmd = ENABLE;				//指定NVIC线路使能
	NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority = 2;	//指定NVIC线路的抢占优先级为2
	NVIC_InitStructure1.NVIC_IRQChannelSubPriority = 1;			//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure1);								//将结构体变量交给NVIC_Init，配置NVIC外设
	
	
	
	TIM_Cmd(TIM4, ENABLE);			//使能TIM4，定时器开始运行
}

