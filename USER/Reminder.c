#include "Application.h"

/*
	�������ܣ��߲˹���
*/
void Reminder_Func(void)
{
	u8 key;
	u8 *Reminder_Table;
	
	LCD_Clear(YELLOW);
	BACK_COLOR = BROWN;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(94,3,80,16,"�߲�",16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,(u8 *)(Clear_flag?"���":"ȡ��"),16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,"ȷ��",16);	
	
	LCD_DrawRecFill(40,40,180,60,BROWN);
	Display_String(43,43,150,16,"������߲����ţ�",16);
	
	LCD_DrawRecFill(40,80,180,120,BROWN);
	
	do{
		key = Key_Scan();
		
		/*�˳�*/
		if((key==KEY_ESC)&&Clear_flag==0){
			Reminder_flag = 0;
			Menu_flag = 1;
		}
		/*ѡ��*/
		if((key==KEY_WKUP)&&Clear_flag){
			Reminder_flag = 0;
			Menu_flag = 1;
			/*���ڼ��Ϸ������Ӻ�*/
		}
	
		/*��ȡ�߲����Ӻ�*/
		Reminder_Table = Key_Input(key);
		Display_String(70,90,120,16,Reminder_Table,16);
		
	}while(Reminder_flag);
	
}

