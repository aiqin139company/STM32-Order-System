#include "Application.h"

#define Input_Cnt		3

/*
	�������ܣ��߲˹���
*/
void Reminder_Func(void)
{
	u8 key;
	u8 *Reminder_Table;
	
	WINDOWS_INIT_TYPE Reminder_Win={YELLOW,BROWN,94,"�߲�","ȡ��","ȷ��"};
	/*�����ʼ��*/
	Windows_Init(Reminder_Win);
	
	LCD_DrawRecFill(40,40,180,60,BROWN);
	Display_String(43,43,150,16,"������߲����ţ�",16);
	
	LCD_DrawRecFill(40,80,180,120,BROWN);
	
	do{
	
		/*��ȡ���ܼ�ֵ*/
		key = Common_Key((short *)&Null,(short *)&Null,Null,Null, &Menu_flag,&Reminder_flag,&Menu_flag);	
		
		/*��ȡ�߲����Ӻ�*/
		Reminder_Table = Key_Input(key,Input_Cnt,&Clear_All);
		Display_String(98,90,80,16,Reminder_Table,16);
		
	}while(Reminder_flag);
	Clear_All = 1;
	Clear_flag = 1;
}

