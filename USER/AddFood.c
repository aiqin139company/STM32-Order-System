#include "Application.h"

WINDOWS_INIT_TYPE AddFood_Win={YELLOW,BROWN,94,"�Ӳ�","����","ѡ��"};

void AddFood_Func(void)
{
	/*���ڳ�ʼ��*/
	Windows_Init(AddFood_Win);
	
	do{
		/*��ȡ���ܼ�ֵ*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Menu_flag,&AddFood_flag,&Null);	
		
	}while(AddFood_flag);
	
}
