#include <stm32f10x.h>
#include "Application.h"

/*
	�������ܣ�������
*/
int main(void)
{
	u8 key;
	
	LED_Init();			//LED�Ƴ�ʼ��
	Beep_Init();		//��������ʼ��
	KEY_Init();			//������ʼ��
	Delay_Init();		//��ʱ������ʼ��
	USART1_Init(115200);	//���ڳ�ʼ��
	W25Q64_Init();	//�洢оƬ��ʼ��
	Font_Init();		//�ֿ��ʼ��	
	LCD_Init();			//Һ������ʼ��
	RTC_Init();			//ʵʱʱ�ӳ�ʼ��
	
	Login_Func();
	
	while(1){
		key = Key_Scan();
		if(key) LCD_ShowNum(10,10,key,3,16);

	}
}

