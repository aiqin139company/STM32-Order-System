#include "Application.h"

const u8 About[] = "    �����ϵͳΪ�����д��ڿƼ����޹�˾�־�ΰ��ƣ���Ȩ���У�������Ҫ����ϵ����ߣ�                      �绰:15017931073          QQ:277579066";

/*
	�������ܣ����ý������
*/
void Settings_About_Func(void)
{	
	WINDOWS_INIT_TYPE Settings_About_Win={YELLOW,BROWN,94,"����","����","ȷ��"};
	/*���ڳ�ʼ��*/
	Windows_Init(Settings_About_Win);	
	
	BACK_COLOR = YELLOW;
	Display_String(10,25,210,120,(u8 *)About,16);
	
	do{
		/*��ȡ���ܼ�ֵ*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Settings_flag,&Settings_About_flag,&Settings_flag);
		
	}while(Settings_About_flag);
}
