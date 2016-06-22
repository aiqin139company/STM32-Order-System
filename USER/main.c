#include <stm32f10x.h>
#include "Application.h"

/*
	�������ܣ�������
*/
int main(void)
{
	
	LED_Init();			//LED�Ƴ�ʼ��
	Beep_Init();		//��������ʼ��
	KEY_Init();			//������ʼ��
	Delay_Init();		//��ʱ������ʼ��
	USART1_Init(115200);	//���ڳ�ʼ��
	W25Q64_Init();	//�洢оƬ��ʼ��
	Font_Init();		//�ֿ��ʼ��	
	LCD_Init();			//Һ������ʼ��
	RTC_Init();			//ʵʱʱ�ӳ�ʼ��
	
	while(1){
		if(Login_flag)				Login_Func();						//��½����
		if(Home_flag)					Home_Func();						//������
		if(Menu_flag)					Menu_Func();						//�˵�����
		if(Newtable_flag) 		Newtable_Func();				//��������
		if(Order_flag)				Order_Func();						//��˽���
		if(Reminder_flag)			Reminder_Func();				//�߲˽���
		if(AddFood_flag)			AddFood_Func();					//�Ӳ˽���
		if(RetreatFood_flag)	RetreatFood_Func();			//�˲˽���
		if(Query_flag)				Query_Func();						//��ѯ����
		if(MMS_flag)					MMS_Func();							//��Ϣ����
		if(Settings_flag)			Settings_Func();				//���ý���
	}
}

