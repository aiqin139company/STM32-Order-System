#include <stm32f10x.h>
#include "LED.h"
#include "Beep.h"
#include "delay.h"
#include "KEY.h"
#include "USART.h"
#include "W25Q64.h"
#include "Font.h"
#include "ILI9341.h"

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
	
	LCD_Init();			
	
	LCD_Clear(BLUE);
	for(key=0;key<110;key++)
	{
		Draw_Circle(110,88,key,BLACK);								//��Բ
	}
	
	LCD_ShowString(110,88,80,16,16,"hello");
	Display_String(10,26,220,16,"��Ļ��ʼ��ɣ�",16);
	
	
	while(1){
		key = Key_Scan();
		if(key) LCD_ShowNum(10,10,key,3,16);
	}
}

