#include "Application.h"

/*������ɫ��������ɫ��������ʼ�����꣬����1������2*/
WINDOWS_INIT_TYPE Settings_LAB_Win={YELLOW,BROWN,70,"���⼰����","����","ѡ��"};

/*��ʼ�����꣬��ʼ�����꣬ͼ���ȣ�ͼ��߶ȣ����϶���ݼ�϶��������Ƭ��������������Ƭ������*/
WINDOWS_TYPE Settings_LAB_Info = {10,25,200,25,5,5,1,3};

const u8 *Settings_LAB[12] = {"���⿪��","��������","��������"};

/*
	�������ܣ����ñ��⼰����
*/
void Settings_LAB_Func(void)
{
	u8 key;
	short i=0,tmp=1;
	
	/*���ڳ�ʼ��*/
	Windows_Init(Settings_LAB_Win);	
	
	/*��ʾ�˵�*/
	Windows_Titles(Settings_LAB_Info,(u8 **)Settings_LAB,BROWN);
	
	do{
		
		key = Common_Key(&i,(short*)&Null,Settings_LAB_Info.tls_x, Settings_LAB_Info.tls_y,&Settings_flag,&Settings_LAB_flag,&Null);
		/*ѡ��*/
		if(key==KEY_WKUP){
			Settings_LAB_flag = 1;
			if(i==0){
				KEY_LED = !KEY_LED;
				LCD_DrawRecFill(130, (25+i*(30)), 210, (25+i*(30))+25,CYAN);
				Display_String(160,(25+i*30+4),70,16,(u8 *)(KEY_LED?"��":"��"),16);	
			}
		}
		
		/*������ʾ*/
		if(tmp!=i){
			Windows_Title(Settings_LAB_Info,(u8 **)Settings_LAB,tmp,0,BROWN);
			tmp = i;
			Windows_Title(Settings_LAB_Info,(u8 **)Settings_LAB,i,0,CYAN);
		}
	
	}while(Settings_LAB_flag);
}
