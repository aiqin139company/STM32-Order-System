#include "Application.h"

const u8 About[] = "    �����ϵͳΪ�����д��ڿƼ����޹�˾�־�ΰ��ƣ���Ȩ���У�������Ҫ����ϵ����ߣ�                      �绰:15017931073          QQ:277579066";

/*
	�������ܣ����ý������
*/
void Settings_About_Func(void)
{
	u8 key;
	
	LCD_Clear(YELLOW);
	BACK_COLOR = YELLOW;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(94,3,80,16,"����",16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,"����",16);
	
	Display_String(10,25,210,120,(u8 *)About,16);
	
	do{
		key = Key_Scan();
		
		/*�˳�*/
		if(key==KEY_ESC){
			Settings_About_flag = 0;
			Settings_flag = 1;
		}
		
	}while(Settings_About_flag);
}
