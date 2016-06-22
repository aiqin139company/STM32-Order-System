#include "Beep.h"

u8 BEEP_EN = 0;
/***********************************************************
	�������ܣ���������ʼ��
	Ӳ�����ӣ�Beep ��PA12
************************************************************/
void Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*����PAʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	/*�������GPIO��*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*����Ĭ��ֵ*/
	GPIO_ResetBits(GPIOA, GPIO_Pin_12);
	
}

/************************************************************
	�������ܣ���������һ��
*************************************************************/
void Beep_Alarm(void)
{
	if(BEEP_EN){
		Beep = 1;
		Delay_ms(10);
		Beep = 0;
	}
}

/************************************************************/
