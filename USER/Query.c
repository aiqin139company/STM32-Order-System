#include "Application.h"

void Query_Func(void)
{
	u8 key;
	
	LCD_Clear(YELLOW);
	BACK_COLOR = BROWN;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(94,3,80,16,"��ѯ",16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,"����",16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,"ѡ��",16);	
	
	do{
		key = Key_Scan();
		
		/*�˳�*/
		if(key==KEY_ESC){
			Query_flag = 0;
			Menu_flag = 1;
		}
		/*ѡ��*/
		if(key==KEY_WKUP){
			
		}
	
	}while(Query_flag);
}
