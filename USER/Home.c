#include "Application.h"

WINDOWS_INIT_TYPE Home_Win={YELLOW,BROWN,53,"���ڿƼ���˱�","�˳�","�˵�"};

void Home_Func(void)
{
	/*���ڳ�ʼ��*/
	Windows_Init(Home_Win);
	LCD_DrawRecFill(50, 40, 170, 96,BROWN);
	
	do{
		/*��ȡ���ܼ�ֵ*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Login_flag,&Home_flag,&Menu_flag);
		/*����ʱ����ʾ*/
		RTC_Func();				
	}while(Home_flag);
	
}

