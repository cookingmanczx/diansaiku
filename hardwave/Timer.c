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
	
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure7;				//����ṹ�����
	TIM_TimeBaseInitStructure7.TIM_ClockDivision = TIM_CKD_DIV1;		//ʱ�ӷ�Ƶ��ѡ�񲻷�Ƶ���˲������������˲���ʱ�ӣ���Ӱ��ʱ����Ԫ����
	TIM_TimeBaseInitStructure7.TIM_CounterMode = TIM_CounterMode_Up;	//������ģʽ��ѡ�����ϼ���
	TIM_TimeBaseInitStructure7.TIM_Period = 100 - 1;				//�������ڣ���ARR��ֵ
	TIM_TimeBaseInitStructure7.TIM_Prescaler =7200 - 1;				//Ԥ��Ƶ������PSC��ֵ
	TIM_TimeBaseInitStructure7.TIM_RepetitionCounter = 0;			//�ظ����������߼���ʱ���Ż��õ�
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure7);				//���ṹ���������TIM_TimeBaseInit������TIM4��ʱ����Ԫ	
	
	
	
	/*�ж��������*/
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);						//�����ʱ�����±�־λ
																
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);					//����TIM4�ĸ����ж�
	
	
	
	
	/*NVIC�жϷ���*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//����NVICΪ����2															
																
	/*NVIC����*/
	NVIC_InitTypeDef NVIC_InitStructure1;						//����ṹ�����
	NVIC_InitStructure1.NVIC_IRQChannel = TIM4_IRQn;				//ѡ������NVIC��TIM2��
	NVIC_InitStructure1.NVIC_IRQChannelCmd = ENABLE;				//ָ��NVIC��·ʹ��
	NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority = 2;	//ָ��NVIC��·����ռ���ȼ�Ϊ2
	NVIC_InitStructure1.NVIC_IRQChannelSubPriority = 1;			//ָ��NVIC��·����Ӧ���ȼ�Ϊ1
	NVIC_Init(&NVIC_InitStructure1);								//���ṹ���������NVIC_Init������NVIC����
	
	
	
	TIM_Cmd(TIM4, ENABLE);			//ʹ��TIM4����ʱ����ʼ����
}

