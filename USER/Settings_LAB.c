#include "Application.h"

const u8 *Settings_LAB[12] = {"���⿪��","��������","��������"};

/*
	�������ܣ����ñ��⼰����
*/
void Settings_LAB_Func(void)
{
	u8 key;
	short i=0,j=10,tmp1=1,tmp2=10;
	
	/*��ʼ�����꣬��ʼ�����꣬ͼ���ȣ�ͼ��߶ȣ����϶���ݼ�϶��������Ƭ��������������Ƭ������*/
	WINDOWS_TYPE Settings_LAB_Info = {10,25,200,25,5,5,1,3};
	/*������ɫ��������ɫ��������ʼ�����꣬����1������2*/
	WINDOWS_INIT_TYPE Settings_LAB_Win={YELLOW,BROWN,70,"���⼰����","����","ѡ��"};
	/*���ڳ�ʼ��*/
	Windows_Init(Settings_LAB_Win);	
	
	/*��ʾ�˵�*/
	Windows_Titles(Settings_LAB_Info,(u8 **)Settings_LAB,BROWN);
	
	do{
		
		key = Common_Key(&i,&j,20, Settings_LAB_Info.tls_y,&Settings_flag,&Settings_LAB_flag,&Null);
		/*ѡ��*/
		if(key==KEY_WKUP){
			Settings_LAB_flag = 1;
			if(i==0){
				KEY_LED = !KEY_LED;
				LCD_DrawRecFill(130, (25+i*(30)), 210, (25+i*(30))+25,CYAN);
				Display_String(160,(25+i*30+4),70,16,(u8 *)(KEY_LED?"��":"��"),16);	
			}
		}
		
		/*��������*/
		if((tmp2!=j)&&i==1){
			LCD_BL_PWM = j * 5;
			tmp2 = j;
			LCD_DrawRecFill(130, (25+i*(30)), 210, (25+i*(30))+25,CYAN);
			BACK_COLOR = CYAN;
			LCD_ShowNum(160,(25+i*30+4),j,2,16);	
		}
		
		/*������ʾ*/
		if(tmp1!=i){
			Windows_Title(Settings_LAB_Info,(u8 **)Settings_LAB,tmp1,0,BROWN);
//			if(tmp1==0||tmp1==2){
//				LCD_DrawRecFill(130, (25+tmp1*(30)), 210, (25+tmp1*(30))+25,BROWN);
//				Display_String(160,(25+tmp1*30+4),70,16,(u8 *)(KEY_LED?"��":"��"),16);
//			}
//			if(tmp1==1){
//				LCD_DrawRecFill(130, (25+tmp1*(30)), 210, (25+tmp1*(30))+25,BROWN);
//				BACK_COLOR = BROWN;
//				LCD_ShowNum(160,(25+tmp1*30+4),j,2,16);	
//			}
			tmp1 = i;
			Windows_Title(Settings_LAB_Info,(u8 **)Settings_LAB,i,0,CYAN);
//			if(i==0||i==2){
//				LCD_DrawRecFill(130, (25+i*(30)), 210, (25+i*(30))+25,CYAN);
//				Display_String(160,(25+i*30+4),70,16,(u8 *)(KEY_LED?"��":"��"),16);
//			}
//			if(i==1){
//				LCD_DrawRecFill(130, (25+i*(30)), 210, (25+i*(30))+25,CYAN);
//				BACK_COLOR = CYAN;
//				LCD_ShowNum(160,(25+i*30+4),j,2,16);	
//			}
		}
	
	}while(Settings_LAB_flag);
}
