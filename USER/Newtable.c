#include "Application.h"


/*
	�������ܣ�������
*/
void Newtable_Func(void)
{
	u8 key;
	u8 *Table;
	
	LCD_Clear(YELLOW);
	BACK_COLOR = BROWN;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(94,3,80,16,"����",16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,(u8 *)(Clear_flag?"���":"ȡ��"),16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,"ȷ��",16);	
	
	LCD_DrawRecFill(40,40,180,60,BROWN);
	Display_String(43,43,150,16,"�������¿����ţ�",16);
	
	LCD_DrawRecFill(40,80,180,120,BROWN);
	
	do{
		key = Key_Scan();
		
		/*�˳�*/
		if((key==KEY_ESC)&&Clear_flag==0){
			Newtable_flag = 0;
			Menu_flag = 1;
		}
		/*ѡ��*/
		if((key==KEY_WKUP)&&Clear_flag){
			Newtable_flag = 0;
			Menu_flag = 1;
			/*���ڼ��Ϸ������Ӻ�*/
		}
		
		/*��ȡ�¿����Ӻ�*/
		Table = Key_Input(key);
		Display_String(70,90,120,16,Table,16);
		
	}while(Newtable_flag);
	
}


