#include "Application.h"

WINDOWS_INIT_TYPE Settings_User_Win={YELLOW,BROWN,78,"�û�����","����","ѡ��"};

void Settings_User_Func(void)
{
	/*���ڳ�ʼ��*/
	Windows_Init(Settings_User_Win);	
	
	do{
		/*��ȡ���ܼ�ֵ*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Settings_flag,&Settings_User_flag,&Settings_flag);
		
	}while(Settings_User_flag);
}
