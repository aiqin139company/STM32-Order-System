#include "Application.h"

/**********************************************************
	�������ܣ�������
***********************************************************/
void Home_Func(void)
{
	WINDOWS_INIT_TYPE Home_Win={53,"���ڿƼ���˱�","�˳�","�˵�"};
	/*���ڳ�ʼ��*/
	Windows_Init(Home_Win);
	LCD_DrawRecFill(50, 40, 170, 96,Theme_BACK);

	do{
		/*��ȡ���ܼ�ֵ*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Login_flag,&Home_flag,&Menu_flag);
		/*����ʱ����ʾ*/
		RTC_Func();			
		
	}while(Home_flag);
	
}

