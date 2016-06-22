#include "Application.h"

#define Menu_YS   40
#define Menu_YE		118

const u16 Menu_Color[10] = {CYAN,DARKBLUE,BLUE,BRED,GRED,GBLUE,RED,MAGENTA,CYAN,DARKBLUE};
const u8 Menu_Name[10][6] = {"  ","����","���","�߲�","�Ӳ�","�˲�","��ѯ","��Ϣ","����","  "};

WINDOWS_INIT_TYPE Menu_Win={YELLOW,BROWN,94,"�˵�","����","ѡ��"};

/*
	�������ܣ��˵�����
*/
void Menu_Func(void)
{
	static short Menu_Num=0,temp=0;
	
	/*���ڳ�ʼ��*/
	Windows_Init(Menu_Win);
	
	LCD_DrawRecFill(20, Menu_YS, 60, Menu_YE,Menu_Color[Menu_Num+2]);
	LCD_DrawRecFill(80, Menu_YS, 140, Menu_YE,Menu_Color[Menu_Num+1]);
	LCD_DrawRecFill(160, Menu_YS, 200, Menu_YE,Menu_Color[Menu_Num]);	
	LCD_Fill(90,126,130,150,YELLOW);
	Display_String(94,130,80,16,(unsigned char *)Menu_Name[Menu_Num+1],16);
	
	do{

		/*��ȡ���ܼ�ֵ*/
		Common_Key((short *)&Null,&Menu_Num,8,Null, &Home_flag,&Menu_flag,&Null);
		
		/*������ʾ��Ϣ*/
		if(temp!=Menu_Num){	
			temp = Menu_Num;
			LCD_DrawRecFill(20, Menu_YS, 60, Menu_YE,Menu_Color[Menu_Num+2]);
			LCD_DrawRecFill(80, Menu_YS, 140, Menu_YE,Menu_Color[Menu_Num+1]);
			LCD_DrawRecFill(160, Menu_YS, 200, Menu_YE,Menu_Color[Menu_Num]);
			LCD_Fill(90,126,130,150,YELLOW);
			Display_String(94,130,80,16,(unsigned char *)Menu_Name[Menu_Num+1],16);			
		}
	
	}while(Menu_flag);
	
	/*��Home_flag��������ʱ������Menu_numѡ�񼤻��Ǹ�����*/
	if(Home_flag==0)
		switch (Menu_Num){
			case 0 : Newtable_flag 		= 1; break;
			case 1 : Order_flag    		= 1; break;
			case 2 : Reminder_flag 		= 1; break;
			case 3 : AddFood_flag  		= 1; break;
			case 4 : RetreatFood_flag = 1; break;
			case 5 : Query_flag 			= 1; break;
			case 6 : MMS_flag 				=	1; break;
			case 7 : Settings_flag 		= 1; break;
		}
	
}


