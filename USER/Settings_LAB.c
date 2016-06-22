#include "Application.h"

const u8 *Settings_LAB[3] = {"���⿪��","��������","��������"};
/***********************************************************************
	�������ܣ���������
	������u8 i���ڼ���
				u8 num����ʾ�������ȵļ���
				u8 flag����һ���־
				u16 color����ɫ
************************************************************************/
void Display_Info(u8 i,u8 num,u8 flag,u16 color)
{
	LCD_DrawRecFill(130, (25+i*(30)), 210, (25+i*(30))+25,color);
	if(i==0||i==2){	
		Display_String(160,(25+i*30+4),70,16,(u8 *)(flag?"��":"��"),16);
	}
	if(i==1){
		BACK_COLOR = color;
		LCD_ShowNum(160,(25+i*30+4),num,2,16);	
	}
}

/***********************************************************************
	�������ܣ����ñ��⼰����
************************************************************************/
void Settings_LAB_Func(void)
{
	u8 key,tmp;
	short i=0,j=LCD_BL_LIGHT,tmp1=1,tmp2=10;
	/*��ʼ�����꣬��ʼ�����꣬ͼ���ȣ�ͼ��߶ȣ����϶���ݼ�϶��������Ƭ��������������Ƭ������*/
	WINDOWS_TYPE Settings_LAB_Info = {10,25,200,25,5,5,1,3};
	/*������ɫ��������ɫ��������ʼ�����꣬����1������2*/
	WINDOWS_INIT_TYPE Settings_LAB_Win={70,"���⼰����","����","ѡ��"};
	/*���ڳ�ʼ��*/
	Windows_Init(Settings_LAB_Win);	
	/*��ʾ�˵�*/
	Windows_Titles(Settings_LAB_Info,(u8 **)Settings_LAB,Theme_BACK);
	for(tmp=0;tmp<3;tmp++)
		Display_Info(tmp,j,(tmp?BEEP_EN:KEY_LED),Theme_BACK);
	
	do{
		
		key = Common_Key(&i,&j,21, Settings_LAB_Info.tls_y,&Settings_flag,&Settings_LAB_flag,(u8 *)&Null);
		/*ѡ�񿪹�*/
		if(key==KEY_WKUP){
			Settings_LAB_flag = 1;
			if(i==0)	KEY_LED = !KEY_LED;
			if(i==2)	BEEP_EN = !BEEP_EN;
			Display_Info(i,j,(i?BEEP_EN:KEY_LED),Theme_SLE);
		}
		
		/*��������*/
		if((tmp2!=j)&&i==1){
			LCD_BL_PWM = j * 5;
			tmp2 = j;
			BACK_COLOR = Theme_SLE;
			Display_Info(i,j,(i?BEEP_EN:KEY_LED),Theme_SLE);
		}
		
		/*������ʾ*/
		if(tmp1!=i){
			/*��ʾ�ɵ���Ϣ��ȡ������*/
			Windows_Title(Settings_LAB_Info,(u8 **)Settings_LAB,tmp1,0,Theme_BACK);
			Display_Info(tmp1,j,(tmp1?BEEP_EN:KEY_LED),Theme_BACK);
			tmp1 = i;
			/*��ʾ�µ���Ϣ�����ø���*/
			Windows_Title(Settings_LAB_Info,(u8 **)Settings_LAB,i,0,Theme_SLE);
			Display_Info(i,j,(i?BEEP_EN:KEY_LED),Theme_SLE);
		}
	
	}while(Settings_LAB_flag);
	
	/*��������*/
	LCD_BL_LIGHT = j;
	SAVE_Data();
}

/*********************************END**************************************/


