#include "stm32f10x.h"
volatile int16_t Encoder_Count;
volatile int16_t Encoder_Count1;


void Encoder_Init()
{
/*����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);		//����GPIOE��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		//����AFIO��ʱ�ӣ��ⲿ�жϱ��뿪��AFIO��ʱ��
	
	
	
	/*GPIO��ʼ��*/
	GPIO_InitTypeDef GPIO_InitStructure5;
	GPIO_InitStructure5.GPIO_Mode =GPIO_Mode_IPU;
	GPIO_InitStructure5.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3 ;//| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7 ;
	GPIO_InitStructure5.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure5);						//��PE0��PE1���ų�ʼ��Ϊ��������
	
	
	
	/*AFIOѡ���ж�����*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource0);//���ⲿ�жϵ�0����ӳ�䵽GPIOE����ѡ��PE0Ϊ�ⲿ�ж�����
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource1);//���ⲿ�жϵ�1����ӳ�䵽GPIOE����ѡ��PE1Ϊ�ⲿ�ж�����
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);//���ⲿ�жϵ�0����ӳ�䵽GPIOE����ѡ��PE2Ϊ�ⲿ�ж�����
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);//���ⲿ�жϵ�1����ӳ�䵽GPIOE����ѡ��PE3Ϊ�ⲿ�ж�����
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);//���ⲿ�жϵ�0����ӳ�䵽GPIOE����ѡ��PE0Ϊ�ⲿ�ж�����
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource5);//���ⲿ�жϵ�1����ӳ�䵽GPIOE����ѡ��PE1Ϊ�ⲿ�ж�����
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource6);//���ⲿ�жϵ�0����ӳ�䵽GPIOE����ѡ��PE2Ϊ�ⲿ�ж�����
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource7);//���ⲿ�жϵ�1����ӳ�䵽GPIOE����ѡ��PE3Ϊ�ⲿ�ж�����
	
	/*EXTI��ʼ��*/
	EXTI_InitTypeDef EXTI_InitStructure1;						//����ṹ�����
	EXTI_InitStructure1.EXTI_Line = EXTI_Line0 | EXTI_Line1| EXTI_Line2| EXTI_Line3 ;		//ѡ�������ⲿ�жϵ�0���ߺ�1����,2����,3����
	EXTI_InitStructure1.EXTI_LineCmd = ENABLE;					//ָ���ⲿ�ж���ʹ��
	EXTI_InitStructure1.EXTI_Mode = EXTI_Mode_Interrupt;			//ָ���ⲿ�ж���Ϊ�ж�ģʽ
	EXTI_InitStructure1.EXTI_Trigger =  EXTI_Trigger_Rising_Falling;		//ָ���ⲿ�ж���Ϊ�����½���
	EXTI_Init(&EXTI_InitStructure1);								//���ṹ���������EXTI_Init������EXTI����
	
	
	
	/*NVIC�жϷ���*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//����NVICΪ����1
																//����ռ���ȼ���Χ��0~3����Ӧ���ȼ���Χ��0~3
																//�˷������������������н������һ��
																//���ж���жϣ����԰Ѵ˴������main�����ڣ�whileѭ��֮ǰ
																//�����ö�����÷���Ĵ��룬���ִ�е����ûḲ����ִ�е�����
	
	/*NVIC����*/
	NVIC_InitTypeDef NVIC_InitStructure;						//����ṹ�����
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ѡ������NVIC��EXTI0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//ָ��NVIC��·ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//ָ��NVIC��·����ռ���ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//ָ��NVIC��·����Ӧ���ȼ�Ϊ1
	NVIC_Init(&NVIC_InitStructure);								//���ṹ���������NVIC_Init������NVIC����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;	//ѡ������NVIC��EXTI1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);								
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;	//ѡ������NVIC��EXTI2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);								//
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;	//ѡ������NVIC��EXTI3��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStructure);					

//	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;	//ѡ������NVIC��EXTI3��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
//	NVIC_Init(&NVIC_InitStructure);		

//	NVIC_InitStructure.NVIC_IRQChannel = EXTI5_IRQn;	//ѡ������NVIC��EXTI3��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
//	NVIC_Init(&NVIC_InitStructure);				

//	NVIC_InitStructure.NVIC_IRQChannel = EXTI6_IRQn;	//ѡ������NVIC��EXTI3��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;
//	NVIC_Init(&NVIC_InitStructure);							
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI7_IRQn;	//ѡ������NVIC��EXTI3��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
//	NVIC_Init(&NVIC_InitStructure);							
//	
//	

	
}




/********
PE0ΪA��㣬PE1ΪB���
��������EXTI0_IRQHandler(void)   
���ܣ�A�㴥���ж��жϷ��򣬿��Ƽ�������

��������EXTI1_IRQHandler(void)   
���ܣ�B�㴥���ж��жϷ��򣬿��Ƽ�������
***/
void EXTI0_IRQHandler(void)     
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)		//�ж��Ƿ����ⲿ�ж�0���ߴ������ж�
	{
		if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == 1)    //PE0�������ش����жϣ���ʱ�����һ��PE1�ĵ�ƽ��Ŀ�����ж���ת��
		{
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1) == 1)		  //��һ��PE1�ĵ�ƽΪ�ߵ�ƽ
			{
				Encoder_Count --;					//�˷�����Ϊ��ת�����������Լ�
			}
			else
			{
				Encoder_Count ++;        //�˷�����Ϊ��ת��������������
			}
		}
		else           ////PE0���½��ش����жϣ���ʱ�����һ��PE1�ĵ�ƽ��Ŀ�����ж���ת��
		{
			if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1) == 1)    //��һ��PE1�ĵ�ƽΪ�ߵ�ƽ
			{
				Encoder_Count ++;     //�˷�����Ϊ��ת��������������
			}
			else
			{
				Encoder_Count --;    //�˷�����Ϊ��ת�����������Լ�
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line0);			//����ⲿ�ж�0���ߵ��жϱ�־λ
													//�жϱ�־λ�������
													//�����жϽ��������ϵش�����������������
	}
}



void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) == SET)		//�ж��Ƿ����ⲿ�ж�0���ߴ������ж�
	{
		if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1) == 1)  	//PE1�������ش����жϣ���ʱ�����һ��PB1�ĵ�ƽ��Ŀ�����ж���ת��
		{
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == 1)		//��һ��PE0�ĵ�ƽΪ�ߵ�ƽ
			{
				Encoder_Count ++;					 //�˷�����Ϊ��ת��������������
			}
			else
			{
				Encoder_Count --;          //�˷�����Ϊ��ת�����������Լ�
			}
		}
		else   	//PE1���½��ش����жϣ���ʱ�����һ��PB1�ĵ�ƽ��Ŀ�����ж���ת��
		{
			if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == 1)  //��һ��PE0�ĵ�ƽΪ�ߵ�ƽ
			{
				Encoder_Count --;     //�˷�����Ϊ��ת�����������Լ�
			}
			else
			{
				Encoder_Count ++;    //�˷�����Ϊ��ת��������������
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line1);			//����ⲿ�ж�1���ߵ��жϱ�־λ
													//�жϱ�־λ�������
													//�����жϽ��������ϵش�����������������
	}
}

/********
��������Get_Encoder_Count(void)
���ܣ���ȡEncoder_Count;
***/
int16_t Get_Encoder_Count(void)
{
	int16_t temp;
	__disable_irq(); 
	temp = Encoder_Count;
	Encoder_Count=0;
	__enable_irq();  
	return temp;
}



/********
PE2ΪA��㣬PE3ΪB���
��������EXTI2_IRQHandler(void)   
���ܣ�A�㴥���ж��жϷ��򣬿��Ƽ�������

��������EXTI3_IRQHandler(void)   
���ܣ�B�㴥���ж��жϷ��򣬿��Ƽ�������
***/

void EXTI2_IRQHandler(void)     
{
	if (EXTI_GetITStatus(EXTI_Line2) == SET)		//�ж��Ƿ����ⲿ�ж�2���ߴ������ж�
	{
		if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 1)    //PE2�������ش����жϣ���ʱ�����һ��PE3�ĵ�ƽ��Ŀ�����ж���ת��
		{
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 1)		  //��һ��PE3�ĵ�ƽΪ�ߵ�ƽ
			{
				Encoder_Count1 --;					//�˷�����Ϊ��ת�����������Լ�
			}
			else
			{
				Encoder_Count1 ++;        //�˷�����Ϊ��ת��������������
			}
		}
		else           ////PE0���½��ش����жϣ���ʱ�����һ��PB1�ĵ�ƽ��Ŀ�����ж���ת��
		{
			if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 1)    //��һ��PE3�ĵ�ƽΪ�ߵ�ƽ
			{
				Encoder_Count1 ++;     //�˷�����Ϊ��ת��������������
			}
			else
			{
				Encoder_Count1 --;    //�˷�����Ϊ��ת�����������Լ�
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line2);			//����ⲿ�ж�2���ߵ��жϱ�־λ
													//�жϱ�־λ�������
													//�����жϽ��������ϵش�����������������
	}
}




void EXTI3_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line3) == SET)		//�ж��Ƿ����ⲿ�ж�3���ߴ������ж�
	{
		if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 1)  	//PE3�������ش����жϣ���ʱ�����һ��PE2�ĵ�ƽ��Ŀ�����ж���ת��
		{
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 1)		//��һ��PE2�ĵ�ƽΪ�ߵ�ƽ
			{
				Encoder_Count1 ++;					 //�˷�����Ϊ��ת��������������
			}
			else
			{
				Encoder_Count1 --;          //�˷�����Ϊ��ת�����������Լ�
			}
		}
		else   	//PE1���½��ش����жϣ���ʱ�����һ��PB1�ĵ�ƽ��Ŀ�����ж���ת��
		{
			if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 1)  //��һ��PE2�ĵ�ƽΪ�ߵ�ƽ
			{
				Encoder_Count1 --;     //�˷�����Ϊ��ת�����������Լ�
			}
			else
			{
				Encoder_Count1 ++;    //�˷�����Ϊ��ת��������������
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line3);			//����ⲿ�ж�3���ߵ��жϱ�־λ
													//�жϱ�־λ�������
													//�����жϽ��������ϵش�����������������
	}
}



/********
��������Get_Encoder_Count1(void)
���ܣ���ȡEncoder_Count1;
***/
int16_t Get_Encoder_Count1(void)
{
	int16_t temp;
	__disable_irq(); 
	temp = Encoder_Count1;
	Encoder_Count1=0;
	__enable_irq();  
	return temp;
}

