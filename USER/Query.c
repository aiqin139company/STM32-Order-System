#include "Application.h"

WINDOWS_INIT_TYPE Query_Win={YELLOW,BROWN,94,"��ѯ","����","ѡ��"};

/*************************************************************
	�������ܣ���ѯ����
**************************************************************/
void Query_Func(void)
{	
	/*���ڳ�ʼ��*/
	Windows_Init(Query_Win);	
	
	do{
		/*��ȡ���ܼ�ֵ*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Menu_flag,&Query_flag,&Null);	
		
	}while(Query_flag);
}
