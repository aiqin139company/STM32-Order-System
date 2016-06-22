#include "Application.h"


/********************************************************************************
	�������ܣ���ͬ��ȡ���ӺŹ��ܽ���
	������u8 *Old_flag���ϵĽ����־��
				u8 *Self_flag����������־��
				u8 *New_flag���µĽ����־��
				u8 *name���������ƣ�
				u8 *show����ʾ�������ݣ�
				u8 *warming����ʾ����
*********************************************************************************/
u16 Get_Table_Func(u8 *Old_flag, u8 *Self_flag, u8 *New_flag,u8 *name,u8 *show,u8 *warming)
{
	u8 key;
	u16 table_num;
	u8 *Table;
	/*������Ϣ*/
	WINDOWS_INIT_TYPE Win={94,"    ","ȡ��","ȷ��"};
	Win.Name = name;
	/*�����ʼ��*/
	Windows_Init(Win);
	LCD_DrawRecFill(40,40,180,60,Theme_BACK);
	Display_String(43,43,150,16,show,16);
	LCD_DrawRecFill(40,80,180,120,Theme_BACK);
	
	do{
		/*��ȡ���ܼ�ֵ*/
		key = Common_Key((short*)&Null,(short*)&Null,Null,Null, Old_flag,Self_flag,Self_flag);
		if((key==KEY_WKUP)&&Clear_flag){
			*Self_flag = 0;
			Message_Warming_flag = 1;
			sscanf((char *)Table,"%d",(int *)&table_num);
			#ifdef Debug_Get_Table
			printf("���Ӻţ�%d\r\n",table_num);
			#endif
		}
		/*��ȡ���Ӻ�*/
		Table = Key_Input(key,3,&Clear_All);
		Display_String(98,90,80,16,Table,16);
	}while(*Self_flag);
	if(*Old_flag==0)
		Message_Warming_Func(Old_flag,New_flag, warming);
	
	return table_num;
}


/********************************************************************************
	�������ܣ�������
********************************************************************************/
void Newtable_Func(void)
{
	/*�Ͻ����־����������־���½����־���������ƣ���ȡ���Ӻ���ʾ��ȷ����ʾ*/
	u16 Newtable_num = Get_Table_Func(&Menu_flag, &Newtable_flag,&Order_flag,"����","�������¿����ţ�","�Ƿ��ˣ�");
	COUSTOMER.Table = Newtable_num;
}

/********************************************************************************
	�������ܣ��߲˹���
********************************************************************************/
void Reminder_Func(void)
{
	u8 str[40];
	/*�Ͻ����־����������־���½����־���������ƣ���ȡ���Ӻ���ʾ��ȷ����ʾ*/
	u16 Remider_num = Get_Table_Func(&Menu_flag, &Reminder_flag,&Menu_flag,"�߲�","������߲����ţ�","�Ƿ�߲ˣ�");
	COUSTOMER.Table = Remider_num;
	sprintf((char *)str,"%d�������ڴ߲ˣ���㣡",COUSTOMER.Table);
	Send_msg(0x08,str);
}

/********************************************************************************
	�������ܣ���ѯ����
********************************************************************************/
void Query_Func(void)
{		
	/*�Ͻ����־����������־���½����־���������ƣ���ȡ���Ӻ���ʾ��ȷ����ʾ*/
	u16 Query_num = Get_Table_Func(&Menu_flag, &Query_flag,&AddFood_flag,"��ѯ","�������ѯ���ţ�","�Ƿ��ѯ��");
	COUSTOMER.Table = Query_num;
}


/********************************************************************************/

