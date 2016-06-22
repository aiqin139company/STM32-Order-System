#include "Application.h"

u8 user_input_flag=1,passwd_input_flag=0;
ACCOUNT_TYPE Account={"          ","          "};	

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
		LCD_DrawRecFill(10, 145, 60, 170,Theme_BACK);//���Ч��
		if(i!=0)							//��Χ���0
			Input_Data[--i] = ' ';
	}else if(Esc_flag==0){
		Esc_flag = 1;
		BACK_COLOR = Theme_BACK;
		Display_String(20,150,80,16,"���",16);
		BACK_COLOR = Theme_SLE;
	}
	
	/*�����л�*/
	if((key==KEY_UP)&&user_input_flag==0){
		BACK_COLOR = Theme_BACK;
		LCD_DrawRecFill(90, 45, 190, 75,Theme_SLE);
		LCD_DrawRecFill(90, 95, 190, 122,Theme_BACK);
		user_input_flag = 1;											//�û������־Ϊ1
		passwd_input_flag = 0;										//���������־Ϊ0
		strcpy((char*)temp2,(char*)Input_Data);		//������浽temp2����
		strcpy((char*)Input_Data,(char*)temp1);		//���û���ԭ��Input_Data����
		i2 =i;																		//��¼�������뵽�ڼ���
		i = i1;																		//��ԭ�û����뵽�ڼ���
		return temp2;			//����passwd�ĵ�ַ����Ϊ��û���user���˳�֮��ű�
	}
	if((key==KEY_DOWN)&&passwd_input_flag==0){
		BACK_COLOR = Theme_BACK;
		LCD_DrawRecFill(90, 45, 190, 75,Theme_BACK);
		LCD_DrawRecFill(90, 95, 190, 122,Theme_SLE);
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
		LCD_DrawRecFill(160, 145, 210, 170,Theme_BACK);
//		FLASH_Serial_Read_Data(USER_Addr, 10, DefAcc.User);	//��ȡ�û���
//		FLASH_Serial_Read_Data(PASSWD_Addr, 10, DefAcc.Passwd);	//��ȡ�û���
		if(str_cmpx(Account.User,DefAcc.User, 10)&&str_cmpx(Account.Passwd,DefAcc.Passwd,10)){
//		if(str_cmpx(Account.User,"123456    ", 10)&&str_cmpx(Account.Passwd,"123456    ",10)){
			Login_flag = 0;				//ʧ�ܵ�½����
			Home_flag = 1;				//ʹ��������	
		}
		#ifdef Debug_Login
			printf("user:%s\r\npasswd:%s\r\n",Account.User,Account.Passwd);
			printf("DefAcc.user:%s\r\nDefAcc.passwd:%s\r\n",DefAcc.User,DefAcc.Passwd);
		#endif
	}else if(WKUP_flag==0){
		WKUP_flag = 1;
		BACK_COLOR = Theme_BACK;
		Display_String(170,150,80,16,"ȷ��",16);
		BACK_COLOR = Theme_SLE;
	}
	
	return Input_Data;			//���ػ�ȡ���������׵�ַ
}

/*
	�������ܣ���½����
*/
void Login_Func(void)
{

	WINDOWS_INIT_TYPE Login_Win = {77,"�û���½","���","ȷ��"};
	/*���ڳ�ʼ��*/
	Windows_Init(Login_Win);

	LCD_DrawRecFill(20, 45, 80, 75,Theme_BACK);
	Display_String(25,52,80,16,"�û���",16);
	LCD_DrawRecFill(20, 95, 80, 122,Theme_BACK);
	Display_String(25,100,80,16,"���룺",16);
	LCD_DrawRecFill(90, 45, 190, 75,(user_input_flag ? Theme_SLE : Theme_BACK));
	Display_String(95,52,80,16,Account.User,16);
	LCD_DrawRecFill(90, 95, 190, 122,(passwd_input_flag ? Theme_SLE : Theme_BACK));
	Display_String(95,100,80,16,Account.Passwd,16);
	
	do{
		
		/*�����û���*/
		if(user_input_flag){
			BACK_COLOR = Theme_SLE;
			Account.User = Input_Scan();
			Display_String(95,52,80,16,Account.User,16);
		}
		/*��������*/
		if(passwd_input_flag){
			BACK_COLOR = Theme_SLE;
			Account.Passwd = Input_Scan();
			Display_String(95,100,80,16,Account.Passwd,16);
		}
	}while(Login_flag);
	
	#ifdef Debug_Theme
		printf("Color:%X,Back:%X,SLE:%X\r\n",Theme_Color,Theme_BACK,Theme_SLE);
	#endif
}

