#include "LED.h"

/*********************************************************
	�������ܣ�LED��ʼ��
	Ӳ�����ӣ�KEY_LED ��PA2
						LCD_BL ��PA3
**********************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*����PAʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	/*�������GPIO��*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*����Ĭ��ֵ*/
	GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3);
	
}

/**********************************************************/

