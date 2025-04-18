#include"stm32f10x.h"

void PWM_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);  //开启TIM1的时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //开启TIM3的时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //开启PB的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);     //开启PA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);   //开启PE的时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1,ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);
	
	
	 GPIO_InitTypeDef GPIO_InitStructure1;
   GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;  //TIM1的通道引脚  CH1,CH2,CH3,CH4 (PWM1-PWM4)
//	 GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_8| GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;  //TIM1的通道引脚  CH1,CH2,CH3,CH4 (PWM1-PWM4)
   GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOE, &GPIO_InitStructure1);
	
	 GPIO_InitTypeDef GPIO_InitStructure2;
   GPIO_InitStructure2.GPIO_Pin =GPIO_Pin_0 | GPIO_Pin_1;  //TIM3的通道引脚  CH3,CH4  (PWM5-PWM6)
   GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB, &GPIO_InitStructure2);
	 
	 GPIO_InitStructure2.GPIO_Pin =GPIO_Pin_6 | GPIO_Pin_7;   //TIM3的通道引脚  CH1,CH2  (PWM5-PWM6)
	 GPIO_Init(GPIOA, &GPIO_InitStructure2);
	 
	
	
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure1;  //TIM1时基单元配置
  TIM_TimeBaseStructure1.TIM_Period = 20000 - 1;       // ARR = 20000
  TIM_TimeBaseStructure1.TIM_Prescaler = 72 - 1;      // 72MHz / 72 = 1MHz
  TIM_TimeBaseStructure1.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure1.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure1.TIM_RepetitionCounter = 0;   // 高级定时器特有
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure1);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure2;    //TIM3时基单元配置
  TIM_TimeBaseStructure2.TIM_Period = 20000 - 1;       // ARR = 999
  TIM_TimeBaseStructure2.TIM_Prescaler = 18 - 1;     
  TIM_TimeBaseStructure2.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure2.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure2.TIM_RepetitionCounter = 0;  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure2);
	

	
	
	 TIM_OCInitTypeDef TIM_OCInitStructure1;  //TIM1的捕获输出配置
   TIM_OCStructInit(&TIM_OCInitStructure1);
   TIM_OCInitStructure1.TIM_OCMode = TIM_OCMode_PWM1;
   TIM_OCInitStructure1.TIM_OutputState = TIM_OutputState_Enable;
   TIM_OCInitStructure1.TIM_Pulse = 0; // 0%占空比（ARR=999）
   TIM_OCInitStructure1.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OCInitTypeDef TIM_OCInitStructure2;   //TIM3的捕获输出配置
  TIM_OCStructInit(&TIM_OCInitStructure2);
  TIM_OCInitStructure2.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure2.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure2.TIM_Pulse = 0; // 0%占空比（ARR=999）
  TIM_OCInitStructure2.TIM_OCPolarity = TIM_OCPolarity_High;
	
	
	
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure1);  // CH1 (PE9) /
	TIM_OC2Init(TIM1, &TIM_OCInitStructure1);  // CH2 (PE11)/
  TIM_OC3Init(TIM1, &TIM_OCInitStructure1);  // CH3 (PE13)/
	TIM_OC4Init(TIM1, &TIM_OCInitStructure1);  // CH4 (PE14)/
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
  TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure2);  // CH1 (PA6)
	TIM_OC2Init(TIM3, &TIM_OCInitStructure2);  // CH2 (PA7)
	TIM_OC3Init(TIM3, &TIM_OCInitStructure2);  // CH3 (PB0)
	TIM_OC4Init(TIM3, &TIM_OCInitStructure2);  // CH4 (PB1)
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);


  
	
	 TIM_CtrlPWMOutputs(TIM1, ENABLE); 
	 TIM_Cmd(TIM1, ENABLE);
   TIM_Cmd(TIM3, ENABLE);
}

void PWM_Init1(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);  //开启TIM8的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   //开启TIM2的时钟
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //开启PC引脚的时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //开启PA引脚的时钟
	
	
	 GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9;  //TIM8的通道引脚  CH1,CH2，CH3,CH4 (PWM5-PWM6)
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 // GPIO_Init(GPIOC, &GPIO_InitStructure);
	 GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	 GPIO_InitTypeDef GPIO_InitStructure4;
	 GPIO_InitStructure4.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_5| GPIO_Pin_11;  //TIM2的通道引脚  CH1,CH2 (PWM5-PWM6)
   GPIO_InitStructure4.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_InitStructure4.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA, &GPIO_InitStructure4);
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;   ///TIM8时基单元配置
  TIM_TimeBaseStructure.TIM_Period = 100 - 1;       // ARR = 999
  TIM_TimeBaseStructure.TIM_Prescaler = 36 - 1;      // 72MHz / 72 = 1MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;   // 高级定时器特有
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure4;   ///TIM2时基单元配置
  TIM_TimeBaseStructure4.TIM_Period = 100 - 1;       // ARR = 999
  TIM_TimeBaseStructure4.TIM_Prescaler = 36 - 1;      // 72MHz / 72 = 1MHz
  TIM_TimeBaseStructure4.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure4.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure4.TIM_RepetitionCounter = 0;   // 高级定时器特有
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure4);
	
	
	
	
	 TIM_OCInitTypeDef TIM_OCInitStructure;   //TIM8捕获输出配置
   TIM_OCStructInit(&TIM_OCInitStructure);
   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
   TIM_OCInitStructure.TIM_Pulse = 0; // 0%占空比（ARR=999）
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 
	 TIM_OCInitTypeDef TIM_OCInitStructure4;   //TIM2捕获输出配置
   TIM_OCStructInit(&TIM_OCInitStructure4);
   TIM_OCInitStructure4.TIM_OCMode = TIM_OCMode_PWM1;
   TIM_OCInitStructure4.TIM_OutputState = TIM_OutputState_Enable;
   TIM_OCInitStructure4.TIM_Pulse = 0; // 0%占空比（ARR=999）
   TIM_OCInitStructure4.TIM_OCPolarity = TIM_OCPolarity_High;
	 
	 
	 
	 	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  // CH1 (PC6 
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  // CH2 (PC7
  TIM_OC3Init(TIM8, &TIM_OCInitStructure);  // CH3 (PC8
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);  // CH4 (PC9)/
  TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
  TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
	
	 	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure4);  // CH1 (PA0 
	TIM_OC2Init(TIM2, &TIM_OCInitStructure4);  // CH2 (PA1
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM8, ENABLE);
  TIM_CtrlPWMOutputs(TIM8, ENABLE); // 高级定时器需启用主输出

}

// 占空比设置函数（保持原样）
void PWM_TIM1_Setcompare1(uint16_t compare) //TIM1的CH1的PWM输出
{ 
	 TIM_SetCompare1(TIM1, compare); 
}

void PWM_TIM1_Setcompare2(uint16_t compare) //TIM1的CH2的PWM输出
{ 
	 TIM_SetCompare2(TIM1, compare); 
}

void PWM_TIM1_Setcompare3(uint16_t compare) //TIM1的CH3的PWM输出
{ 
	 TIM_SetCompare3(TIM1, compare); 
}

void PWM_TIM1_Setcompare4(uint16_t compare) //TIM1的CH4的PWM输出
{ 
	 TIM_SetCompare4(TIM1, compare); 
}


void PWM_TIM3_Setcompare1(uint16_t compare) //TIM3的CH1的PWM输出
{ 
	 TIM_SetCompare1(TIM3, compare); 
}

void PWM_TIM3_Setcompare2(uint16_t compare) //TIM3的CH2的PWM输出
{ 
	 TIM_SetCompare2(TIM3, compare); 
}


void PWM_TIM3_Setcompare3(uint16_t compare) //TIM3的CH3的PWM输出
{ 
	 TIM_SetCompare3(TIM3, compare); 
}

void PWM_TIM3_Setcompare4(uint16_t compare) //TIM3的CH4的PWM输出
{ 
	 TIM_SetCompare4(TIM3, compare); 
}





void PWM_TIM8_Setcompare1(uint16_t compare) //TIM8的CH1的PWM输出
{ 
	 TIM_SetCompare1(TIM8, compare); 
}

void PWM_TIM8_Setcompare2(uint16_t compare) //TIM8的CH2的PWM输出
{ 
	 TIM_SetCompare2(TIM8, compare); 
}

void PWM_TIM8_Setcompare3(uint16_t compare) //TIM8的CH3的PWM输出
{ 
	 TIM_SetCompare3(TIM8, compare); 
}

void PWM_TIM8_Setcompare4(uint16_t compare) //TIM8的CH4的PWM输出
{ 
	 TIM_SetCompare4(TIM8, compare); 
}



void PWM_TIM2_Setcompare1(uint16_t compare) //TIM2的CH1的PWM输出
{ 
	 TIM_SetCompare1(TIM2, compare); 
}

void PWM_TIM2_Setcompare2(uint16_t compare) //TIM2的CH2的PWM输出
{ 
	 TIM_SetCompare2(TIM2, compare); 
}

