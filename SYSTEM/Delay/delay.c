#include "delay.h"

/*
	�������ܣ���ʱ�������뼶
	������timer (ms)
*/
void delay_72M_ms(u32 timer)
{
	u32 i;
	u8 j,k;
	for(i=0;i<timer;i++)
		for(j=0;j<100;j++)
			for(k=0;k<100;k++);
}

/*
	�������ܣ���ʱ����΢�뼶
	������timer (us)
*/
void delay_72M_us(u32 timer)
{
	u8 j = 12;
	while(timer--){
		j = 6;
		while(j--);
	}
}

/*
	�������ܣ���ʱ��6��ʱ������ʼ��
*/
void Delay_Init(void)
{
	/*��ʼ��ʱ��6ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	/*��λ��ʱ��6״̬*/
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, DISABLE);
	
	/*�رն�ʱ��6*/
	TIM_Cmd(TIM6, DISABLE);
}

/*
	�������ܣ���ʱ��6��ʱ������x��ms����
*/
void Delay_ms(u32 timer)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/*������ؼĴ���*/
	TIM_TimeBaseStructure.TIM_Period = timer*10;
	TIM_TimeBaseStructure.TIM_Prescaler = 7200-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM6, & TIM_TimeBaseStructure);
	/*ʹ�ܶ�ʱ��*/
	TIM_Cmd(TIM6, ENABLE);
	while(TIM_GetCounter(TIM6)!= (timer * 10));/*�ȴ�*/
	TIM_Cmd(TIM6, DISABLE);		//�رն�ʱ��6
}

/*
	�������ܣ���ʱ��6��ʱ������x��us����
*/
void Delay_us(u32 timer)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/*������ؼĴ���*/
	TIM_TimeBaseStructure.TIM_Period = timer;
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM6, & TIM_TimeBaseStructure);
	/*ʹ�ܶ�ʱ��*/
	TIM_Cmd(TIM6, ENABLE);
	while(TIM_GetCounter(TIM6)!= timer);/*�ȴ�*/
	TIM_Cmd(TIM6, DISABLE);		//�رն�ʱ��6
}
