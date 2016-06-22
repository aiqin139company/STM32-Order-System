#include "Application.h"

static u8 user_input_flag=1,passwd_input_flag=0,pass_flag=0;
u8 *user,*passwd;
/*
	�������ܣ���ȡ����
	����ֵ����ȡ���������׵�ַ
*/
u8 *Input_Scan(void)
{
	u8 key;
	static u8 i=0,Esc_flag=1,WKUP_flag=1;
	static u8 Input_Data[11]="          ";
	static u8 temp1[11]="          ";			//temp1��user
	static u8 temp2[11]="          ";		  //temp2��passwd
	static u8 i1=0,i2=0;									//i1 ��user i2��passwd
	
	key = Key_Scan();
	if(i<10){								//���뷶Χ0-10
		if((key>0&&key<10))		//��������1-9
			Input_Data[i++] = key + 0x30;
		if(key==KEY_0)				//��������0
			Input_Data[i++] = '0';
		if(key==KEY_X)				//�����ַ�*
			Input_Data[i++] = '*';
		if(key==KEY_J)				//�����ַ�#
			Input_Data[i++] = '#';
	}
	if(key==KEY_ESC){				//�����
		Esc_flag = 0;
		LCD_DrawRecFill(10, 145, 60, 170,BROWN);//���Ч��
		if(i!=0)							//��Χ���0
			Input_Data[--i] = ' ';
	}else if(Esc_flag==0){
		Esc_flag = 1;
		BACK_COLOR = BROWN;
		Display_String(20,150,80,16,"���",16);
		BACK_COLOR = GRAY;
	}
	
	
	/*�����л�*/
	if((key==KEY_UP)&&user_input_flag==0){
		BACK_COLOR = BROWN;
		LCD_DrawRecFill(90, 65, 190, 95,GRAY);
		LCD_DrawRecFill(90, 105, 190, 132,BROWN);
		user_input_flag = 1;											//�û������־Ϊ1
		passwd_input_flag = 0;										//���������־Ϊ0
		strcpy((char*)temp2,(char*)Input_Data);		//������浽temp2����
		strcpy((char*)Input_Data,(char*)temp1);		//���û���ԭ��Input_Data����
		i2 =i;																		//��¼�������뵽�ڼ���
		i = i1;																		//��ԭ�û����뵽�ڼ���
		return temp2;			//����passwd�ĵ�ַ����Ϊ��û���user���˳�֮��ű�
	}
	if((key==KEY_DOWN)&&passwd_input_flag==0){
		BACK_COLOR = BROWN;
		LCD_DrawRecFill(90, 65, 190, 95,BROWN);
		LCD_DrawRecFill(90, 105, 190, 132,GRAY);
		user_input_flag = 0;											//�û������־Ϊ0
		passwd_input_flag = 1;										//���������־Ϊ1
		strcpy((char*)temp1,(char*)Input_Data);		//���û��浽temp1����
		strcpy((char*)Input_Data,(char*)temp2);		//�����뻹ԭ��Input_Data����
		i1 = i;																		//��¼�û����뵽�ڼ���
		i = i2;																		//��ԭ�������뵽�ڼ���
		return temp1;			//����user�ĵ�ַ����Ϊ��û���passwd���˳�֮��ű�
	}
	
	
	/*ȷ������*/
	if((key==KEY_WKUP)&&WKUP_flag){
		WKUP_flag = 0;
		LCD_DrawRecFill(160, 145, 210, 170,BROWN);
		if(str_cmpx(user,"123456     ", 10)&&str_cmpx(passwd,"123456     ",10)){
			KEY_LED = !KEY_LED;
			pass_flag = 1;
			printf("��½�ɹ���%s,%d\r\n",__FILE__,__LINE__);
		}
	}else if(WKUP_flag==0){
		WKUP_flag = 1;
		BACK_COLOR = BROWN;
		Display_String(170,150,80,16,"ȷ��",16);
		BACK_COLOR = GRAY;
	}
	
	return Input_Data;			//���ػ�ȡ���������׵�ַ
}

/*
	�������ܣ���½����
*/
void Login_Func(void)
{
	pass_flag = 0;
	
	LCD_Clear(YELLOW);
	BACK_COLOR = BROWN;
	
	LCD_DrawRecFill(50, 20, 170, 50,BROWN);
	Display_String(77,28,80,16,"�û���½",16);
	
	LCD_DrawRecFill(20, 65, 80, 95,BROWN);
	Display_String(25,72,80,16,"�û���",16);
	
	LCD_DrawRecFill(20, 105, 80, 132,BROWN);
	Display_String(25,110,80,16,"���룺",16);
	
	LCD_DrawRecFill(90, 65, 190, 95,GRAY);
	Display_String(95,72,80,16,user,16);
	
	LCD_DrawRecFill(90, 105, 190, 132,BROWN);
	Display_String(95,110,80,16,passwd,16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,"���",16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,"ȷ��",16);
	
	do{
		/*�����û���*/
		if(user_input_flag){
			BACK_COLOR = GRAY;
			user = Input_Scan();
			Display_String(95,72,80,16,user,16);
		}
		/*��������*/
		if(passwd_input_flag){
			BACK_COLOR = GRAY;
			passwd = Input_Scan();
			Display_String(95,110,80,16,passwd,16);
		}
	}while(!pass_flag);
	
	LCD_Clear(YELLOW);
	BACK_COLOR = YELLOW;
}

