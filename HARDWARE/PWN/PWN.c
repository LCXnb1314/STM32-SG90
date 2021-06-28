#include "stm32f10x.h"                  // Device header



/**
  *@brief		定时器3、PWN输出（输出通道4）初始化
	*@param		PSC:预分频系数
	*@param		ARR:重装载值
	*@retval 无
	*/
void PWN_Init(u16 PSC,u16 ARR)
{
	//初始化时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	//配置GPIO复用
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//定时器初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=ARR;
	TIM_TimeBaseInitStructure.TIM_Prescaler=PSC;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	//定时器输出通道4初始化
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=75;//初始值使舵机在90度位置
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	
	//使能预装载寄存器
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_Cmd(TIM3,ENABLE);//使能定时器3
}
