#include "Application.h"

WINDOWS_INIT_TYPE MMS_Win={YELLOW,BROWN,94,"��Ϣ","����","ѡ��"};

void MMS_Func(void)
{
	/*���ڳ�ʼ��*/
	Windows_Init(MMS_Win);	
	
	do{
		/*��ȡ���ܼ�ֵ*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Menu_flag,&MMS_flag,&Null);
		
	}while(MMS_flag);
	
}
