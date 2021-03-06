#include "LED.h"

/*********************************************************
	函数功能：LED初始化
	硬件连接：KEY_LED ：PA2
						LCD_BL ：PA3
**********************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*开启PA时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	/*配置相关GPIO口*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*配置默认值*/
	GPIO_ResetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3);
	
}

/**********************************************************/

