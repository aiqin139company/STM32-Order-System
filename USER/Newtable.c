#include "Application.h"

/*
	�������ܣ�������
*/
void Newtable_Func(void)
{
	/*�Ͻ����־����������־���½����־���������ƣ���ȡ���Ӻ���ʾ��ȷ����ʾ*/
	Get_Table_Func(&Menu_flag, &Newtable_flag,&Order_flag,"����","�������¿����ţ�","�Ƿ��ˣ�");
}

/*
	�������ܣ��߲˹���
*/
void Reminder_Func(void)
{
	/*�Ͻ����־����������־���½����־���������ƣ���ȡ���Ӻ���ʾ��ȷ����ʾ*/
	Get_Table_Func(&Menu_flag, &Reminder_flag,&RetreatFood_flag,"�߲�","������߲����ţ�","�Ƿ�߲ˣ�");
}


void Query_Func(void)
{		
	/*�Ͻ����־����������־���½����־���������ƣ���ȡ���Ӻ���ʾ��ȷ����ʾ*/
	Get_Table_Func(&Menu_flag, &Query_flag,&AddFood_flag,"��ѯ","�������ѯ���ţ�","�Ƿ��ѯ��");
}
