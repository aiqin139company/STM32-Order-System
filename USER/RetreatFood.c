#include "Application.h"

WINDOWS_INIT_TYPE RetreatFood_Win={YELLOW,BROWN,94,"�˲�","����","ѡ��"};

/*
	�������ܣ��˲˽���
*/
void RetreatFood_Func(void)
{
	/*���ڳ�ʼ��*/
	Windows_Init(RetreatFood_Win);
	
	do{
		/*��ȡ���ܼ�ֵ*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Menu_flag,&RetreatFood_flag,&Null);
		
	}while(RetreatFood_flag);
	
}

