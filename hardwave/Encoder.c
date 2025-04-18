#include "stm32f10x.h"
volatile int16_t Encoder_Count;
volatile int16_t Encoder_Count1;


void Encoder_Init()
{
/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);		//开启GPIOE的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		//开启AFIO的时钟，外部中断必须开启AFIO的时钟
	
	
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure5;
	GPIO_InitStructure5.GPIO_Mode =GPIO_Mode_IPU;
	GPIO_InitStructure5.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3 ;//| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7 ;
	GPIO_InitStructure5.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure5);						//将PE0和PE1引脚初始化为上拉输入
	
	
	
	/*AFIO选择中断引脚*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource0);//将外部中断的0号线映射到GPIOE，即选择PE0为外部中断引脚
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource1);//将外部中断的1号线映射到GPIOE，即选择PE1为外部中断引脚
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);//将外部中断的0号线映射到GPIOE，即选择PE2为外部中断引脚
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);//将外部中断的1号线映射到GPIOE，即选择PE3为外部中断引脚
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);//将外部中断的0号线映射到GPIOE，即选择PE0为外部中断引脚
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource5);//将外部中断的1号线映射到GPIOE，即选择PE1为外部中断引脚
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource6);//将外部中断的0号线映射到GPIOE，即选择PE2为外部中断引脚
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource7);//将外部中断的1号线映射到GPIOE，即选择PE3为外部中断引脚
	
	/*EXTI初始化*/
	EXTI_InitTypeDef EXTI_InitStructure1;						//定义结构体变量
	EXTI_InitStructure1.EXTI_Line = EXTI_Line0 | EXTI_Line1| EXTI_Line2| EXTI_Line3 ;		//选择配置外部中断的0号线和1号线,2号线,3号线
	EXTI_InitStructure1.EXTI_LineCmd = ENABLE;					//指定外部中断线使能
	EXTI_InitStructure1.EXTI_Mode = EXTI_Mode_Interrupt;			//指定外部中断线为中断模式
	EXTI_InitStructure1.EXTI_Trigger =  EXTI_Trigger_Rising_Falling;		//指定外部中断线为上升下降沿
	EXTI_Init(&EXTI_InitStructure1);								//将结构体变量交给EXTI_Init，配置EXTI外设
	
	
	
	/*NVIC中断分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//配置NVIC为分组1
																//即抢占优先级范围：0~3，响应优先级范围：0~3
																//此分组配置在整个工程中仅需调用一次
																//若有多个中断，可以把此代码放在main函数内，while循环之前
																//若调用多次配置分组的代码，则后执行的配置会覆盖先执行的配置
	
	/*NVIC配置*/
	NVIC_InitTypeDef NVIC_InitStructure;						//定义结构体变量
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//选择配置NVIC的EXTI0线
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//指定NVIC线路使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//指定NVIC线路的抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//指定NVIC线路的响应优先级为1
	NVIC_Init(&NVIC_InitStructure);								//将结构体变量交给NVIC_Init，配置NVIC外设
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;	//选择配置NVIC的EXTI1线
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);								
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;	//选择配置NVIC的EXTI2线
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);								//
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;	//选择配置NVIC的EXTI3线
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStructure);					

//	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;	//选择配置NVIC的EXTI3线
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
//	NVIC_Init(&NVIC_InitStructure);		

//	NVIC_InitStructure.NVIC_IRQChannel = EXTI5_IRQn;	//选择配置NVIC的EXTI3线
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
//	NVIC_Init(&NVIC_InitStructure);				

//	NVIC_InitStructure.NVIC_IRQChannel = EXTI6_IRQn;	//选择配置NVIC的EXTI3线
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;
//	NVIC_Init(&NVIC_InitStructure);							
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI7_IRQn;	//选择配置NVIC的EXTI3线
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
//	NVIC_Init(&NVIC_InitStructure);							
//	
//	

	
}




/********
PE0为A相点，PE1为B相点
函数名：EXTI0_IRQHandler(void)   
功能：A点触发中断判断方向，控制计数变量

函数名：EXTI1_IRQHandler(void)   
功能：B点触发中断判断方向，控制计数变量
***/
void EXTI0_IRQHandler(void)     
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)		//判断是否是外部中断0号线触发的中断
	{
		if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == 1)    //PE0的上升沿触发中断，此时检测另一相PE1的电平，目的是判断旋转方
		{
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1) == 1)		  //另一相PE1的电平为高电平
			{
				Encoder_Count --;					//此方向定义为反转，计数变量自减
			}
			else
			{
				Encoder_Count ++;        //此方向定义为正转，计数变量自增
			}
		}
		else           ////PE0的下降沿触发中断，此时检测另一相PE1的电平，目的是判断旋转方
		{
			if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1) == 1)    //另一相PE1的电平为高电平
			{
				Encoder_Count ++;     //此方向定义为正转，计数变量自增
			}
			else
			{
				Encoder_Count --;    //此方向定义为反转，计数变量自减
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line0);			//清除外部中断0号线的中断标志位
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	}
}



void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) == SET)		//判断是否是外部中断0号线触发的中断
	{
		if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1) == 1)  	//PE1的上升沿触发中断，此时检测另一相PB1的电平，目的是判断旋转方
		{
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == 1)		//另一相PE0的电平为高电平
			{
				Encoder_Count ++;					 //此方向定义为正转，计数变量自增
			}
			else
			{
				Encoder_Count --;          //此方向定义为反转，计数变量自减
			}
		}
		else   	//PE1的下降沿触发中断，此时检测另一相PB1的电平，目的是判断旋转方
		{
			if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == 1)  //另一相PE0的电平为高电平
			{
				Encoder_Count --;     //此方向定义为反转，计数变量自减
			}
			else
			{
				Encoder_Count ++;    //此方向定义为正转，计数变量自增
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line1);			//清除外部中断1号线的中断标志位
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	}
}

/********
函数名：Get_Encoder_Count(void)
功能：获取Encoder_Count;
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
PE2为A相点，PE3为B相点
函数名：EXTI2_IRQHandler(void)   
功能：A点触发中断判断方向，控制计数变量

函数名：EXTI3_IRQHandler(void)   
功能：B点触发中断判断方向，控制计数变量
***/

void EXTI2_IRQHandler(void)     
{
	if (EXTI_GetITStatus(EXTI_Line2) == SET)		//判断是否是外部中断2号线触发的中断
	{
		if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 1)    //PE2的上升沿触发中断，此时检测另一相PE3的电平，目的是判断旋转方
		{
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 1)		  //另一相PE3的电平为高电平
			{
				Encoder_Count1 --;					//此方向定义为反转，计数变量自减
			}
			else
			{
				Encoder_Count1 ++;        //此方向定义为正转，计数变量自增
			}
		}
		else           ////PE0的下降沿触发中断，此时检测另一相PB1的电平，目的是判断旋转方
		{
			if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 1)    //另一相PE3的电平为高电平
			{
				Encoder_Count1 ++;     //此方向定义为正转，计数变量自增
			}
			else
			{
				Encoder_Count1 --;    //此方向定义为反转，计数变量自减
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line2);			//清除外部中断2号线的中断标志位
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	}
}




void EXTI3_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line3) == SET)		//判断是否是外部中断3号线触发的中断
	{
		if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 1)  	//PE3的上升沿触发中断，此时检测另一相PE2的电平，目的是判断旋转方
		{
			if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 1)		//另一相PE2的电平为高电平
			{
				Encoder_Count1 ++;					 //此方向定义为正转，计数变量自增
			}
			else
			{
				Encoder_Count1 --;          //此方向定义为反转，计数变量自减
			}
		}
		else   	//PE1的下降沿触发中断，此时检测另一相PB1的电平，目的是判断旋转方
		{
			if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 1)  //另一相PE2的电平为高电平
			{
				Encoder_Count1 --;     //此方向定义为反转，计数变量自减
			}
			else
			{
				Encoder_Count1 ++;    //此方向定义为正转，计数变量自增
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line3);			//清除外部中断3号线的中断标志位
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	}
}



/********
函数名：Get_Encoder_Count1(void)
功能：获取Encoder_Count1;
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

