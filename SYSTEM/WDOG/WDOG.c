#include "WDOG.h"

u16 W_WDG_ARR; 				//ι���ڿ��Ź�

/*
	���ڿ��Ź���ʼ������
	pscԤ��Ƶ���ӵķ�Χ��0--3
	arr����ֵ��Χ��0x7f -- 0x40
*/
void W_WDG_Init(u16 w_arr, u16 arr, u16 psc)
{
	RCC->APB1ENR |= 1<<11;			//�������ڿ��Ź�ʱ��
	WWDG->CFR = w_arr;					//���ô���ֵ
	WWDG->CFR |= psc<<7;				//����ʱ��(Ԥ��Ƶϵ��) ��Χ0��3
	WWDG->CFR |= 1<<9;					//ʹ����ǰ�����ж� ���������ڿ��Ź��ж�
	Set_NVIC(WWDG_IRQn,1,1);		//�����жϷ�������ȼ�
	WWDG->CR = W_WDG_ARR = arr;	//����T����ֵ��ι���ڿ��Ź�
	WWDG->CR |= 1<<7;						//ʹ�ܴ��ڿ��Ź�
	
}

/*
	���ڿ��Ź��жϷ�����
*/
void WWDG_IRQHandler(void)
{
	
	WWDG->CR |= W_WDG_ARR;		//ι��
	
	WWDG->SR &= 0; 
}

