#include "Application.h"

/*�˵��б�*/
const u8 *Settings_title[12] = {"ʱ������","��������","���⼰����","����"};

/*
	�������ܣ�ϵͳ����
*/
void Settings_Func(void)
{
	static short i=0,tmp=1;
	/*��ʼ�����꣬��ʼ�����꣬ͼ���ȣ�ͼ��߶ȣ����϶���ݼ�϶��������Ƭ��������������Ƭ������*/
	WINDOWS_TYPE Settings_Info = {10,25,200,25,5,5,1,4};	
	/*������ɫ��������ɫ��������ʼ�����꣬����1������2*/
	WINDOWS_INIT_TYPE Settings_Win={94,"����","����","ѡ��"};
	/*�����ʼ��*/
	Windows_Init(Settings_Win);	
	/*��ʼ���˵�*/
	Windows_Titles(Settings_Info,(u8 **)Settings_title,Theme_BACK);
	/*���ø���*/
	Windows_Title(Settings_Info,(u8 **)Settings_title,i,0,Theme_SLE);
	do{
		/*��ȡ���ܼ�ֵ*/
		Common_Key(&i,(short *)&Null,Settings_Info.tls_x,Settings_Info.tls_y, &Menu_flag,&Settings_flag,(u8*)&Null);
		
		/*������ʾ*/
		if(tmp!=i){
			/*�ָ�����*/
			Windows_Title(Settings_Info,(u8 **)Settings_title,tmp,0,Theme_BACK);
			tmp = i;
			/*���ø���*/
			Windows_Title(Settings_Info,(u8 **)Settings_title,i,0,Theme_SLE);
		}
		
	}while(Settings_flag);
	
	/*�����ý��治������ʱ������i��ֵ������Ӧ����*/
	if(Menu_flag==0)
		switch(i){
			case 0 : Settings_Time_flag  = 1;break;
			case 1 : Settings_Theme_flag = 1;break;
			case 2 : Settings_LAB_flag   = 1;break;
			case 3 : Settings_About_flag = 1;break;
		}
	
}
