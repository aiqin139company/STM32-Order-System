#include "Application.h"


/*
	�������ܣ���Ϣ��ʾ��
*/
void Message_Warming_Func(u8 *Old_flag,u8 *New_flag, u8 *Str)
{
	WINDOWS_INIT_TYPE Msg_Win={LIGHTBLUE,LBBLUE,94,"��ʾ"," ��"," ��"};
	/*���ڳ�ʼ��*/
	Windows_Init(Msg_Win);	
	LCD_DrawRecFill(50, 50, 170, 96,WHITE);
	Display_String(70,60,170,96,Str,16);

	do{
		/*��ȡ���ܼ�ֵ*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null,Old_flag,&Message_Warming_flag,New_flag);
		
	}while(Message_Warming_flag);
	
}



