#include "KEY.h"

/****************************************************************
	�������ܣ�������ʼ��
	Ӳ�����ӣ�PB_All PA0 PC10
*****************************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*����PA,PB,PC,AFIOʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO , ENABLE);
	/*�ر�jtag*/
	AFIO->MAPR &= ~(0x7<<24);
	AFIO->MAPR |=  0x04<<24;
	/*�������GPIO��*/
	/*����PA0*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*����PB_All*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/*����PC10*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/*����Ĭ��ֵ*/
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	GPIO_ResetBits(GPIOB,GPIO_Pin_All);
	GPIO_ResetBits(GPIOC,GPIO_Pin_10);
}

/*****************************************************************
	�������ܣ�����ɨ��
	����ֵ������ֵ
******************************************************************/
u8 Key_Scan(void)
{
	static u8 key_flag = 1;

	if((GPIOB->IDR!=0x0000||S16||S17)&&key_flag){
		key_flag = 0;
		Delay_ms(20);
		if(GPIOB->IDR!=0x0000||S16||S17)	Beep_Alarm();	
		if(S1)	return 1;
		if(S2) 	return 2;
		if(S3) 	return 3;
		if(S4) 	return 4;
		if(S5) 	return 5;
		if(S6) 	return 6;
		if(S7) 	return 7;
		if(S8) 	return 8;
		if(S9) 	return 9;
		if(S10) return 10;
		if(S0)	return 11;
		if(S11) return 12;
		if(S12) return 13;
		if(S13) return 14;
		if(S14) return 15;
		if(S15) return 16;
		if(S16) return 17;
		if(S17) return 18;
	}else if(GPIOB->IDR==0x0000&&S16==0&&S17==0)
		key_flag = 1;	 
	
	return 0;
}

/******************************************************************/
