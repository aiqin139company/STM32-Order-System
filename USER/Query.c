#include "Application.h"

/*************************************************************
	�������ܣ���ѯ����
**************************************************************/
void Query_Func(void)
{		
	u8 key;
	u8 *Query_Table;
	
	/*������Ϣ*/
	WINDOWS_INIT_TYPE Query_Win={YELLOW,BROWN,94,"��ѯ","ȡ��","ȷ��"};
	/*�����ʼ��*/
	Windows_Init(Query_Win);
	LCD_DrawRecFill(40,40,180,60,BROWN);
	Display_String(43,43,150,16,"�������ѯ���ţ�",16);
	LCD_DrawRecFill(40,80,180,120,BROWN);
	
	do{
		
		/*��ȡ���ܼ�ֵ*/
		key = Common_Key((short*)&Null,(short*)&Null,Null,Null, &Menu_flag,&Query_flag,&AddFood_flag);
		if((key==KEY_WKUP)&&Clear_flag){
			
		}
			
		/*��ȡ��ѯ���Ӻ�*/
		Query_Table = Key_Input(key,3,&Clear_All);
		Display_String(98,90,80,16,Query_Table,16);
		
	}while(Query_flag);
}
