#include "Application.h"

#define Input_Cnt		3 

/*
	�������ܣ�������
*/
void Newtable_Func(void)
{
	u8 key;
	u8 *Table;
	
	/*������Ϣ*/
	WINDOWS_INIT_TYPE Newtable_Win={YELLOW,BROWN,94,"����","ȡ��","ȷ��"};
	/*�����ʼ��*/
	Windows_Init(Newtable_Win);
	
	LCD_DrawRecFill(40,40,180,60,BROWN);
	Display_String(43,43,150,16,"�������¿����ţ�",16);
	
	LCD_DrawRecFill(40,80,180,120,BROWN);
	
	do{
		
		/*��ȡ���ܼ�ֵ*/
		key = Common_Key((short*)&Null,(short*)&Null,Null,Null, &Menu_flag,&Newtable_flag,&Menu_flag);
		
		/*��ȡ�¿����Ӻ�*/
		Table = Key_Input(key,Input_Cnt,&Clear_All);
		Display_String(98,90,80,16,Table,16);
		
	}while(Newtable_flag);
	
}


