#include "Application.h"

/****************************��Ӧ���漤��*************************/
u8 Login_flag 								=			0;
u8 Home_flag									=			0;
u8 Menu_flag 									=			0;
u8 Newtable_flag 							=			0;
u8 Order_flag 								=			0;
u8 Reminder_flag 							=			0;
u8 AddFood_flag 							=			0;
u8 RetreatFood_flag 					=			0;
u8 Query_flag 								=			0;
u8 MMS_flag 									=			0;
u8 Settings_flag 							=			0;
u8 Settings_Time_flag 				=			1;
u8 Settings_User_flag 				=			0;
u8 Settings_LAB_flag 					=			0;
u8 Settings_About_flag 				=			0;
u8 Clear_flag 								=			0;
u8 Clear_All									=			1;
u8 Null 											= 		1;
/****************************������ݶ���***************************/
ACCOUNT_TYPE Account={"          ","          "};
ACCOUNT_TYPE DefAcc[4] ={{"123456    ","123456    "}};





/*******************************************************************
	�������ܣ�ʵʱʱ��
********************************************************************/
void RTC_Func(void)
{
	u8 Date_String[20];				//���DATE����
	u8 Time_String[20];				//���TIME����
	TIME_TYPE Disp_Time;			//�洢ʱ��ṹ��
	
	/*���ж���ɺ������ʾ*/
	if(sec_flag){
		/*��ȡʱ��*/
		Get_RTC_Time(RTC_CNT,&Disp_Time);
		/*��ʽת�� XXXX/XX/XX  XX:XX:XX*/
		sprintf((char*)Date_String,"%04d/%02d/%02d",Disp_Time.year,Disp_Time.month,Disp_Time.day);
		sprintf((char*)Time_String,"%02d:%02d:%02d",Disp_Time.hour,Disp_Time.min,Disp_Time.second);
		/*��ʾʱ��*/
		Display_String(70,50,80,16,Date_String,16);
		Display_String(78,70,80,16,Time_String,16);
	}
	
}

/******************************************************************
	�������ܣ��������봦��
	������u8 key���ⲿ����İ���ֵ
				u8 range�����뷶Χ
				u8 *Clear_All�������־
	����ֵ��������֮��������׵�ַ
*******************************************************************/
u8 *Key_Input(u8 key, u8 range, u8 *Clear_All)
{
	static u8 i=0, Esc_flag=1;
	static u8 Input_Data[11]="          ";	
	
	/*������ȡ����*/
	if(i<range){								//���뷶Χ
		if((key>0&&key<10))		//��������1-9
			Input_Data[i++] = key + 0x30;
		if(key==KEY_0)				//��������0
			Input_Data[i++] = '0';
		if(key==KEY_X)				//�����ַ�*
			Input_Data[i++] = '*';
		if(key==KEY_J)				//�����ַ�#
			Input_Data[i++] = '#';
	}
	
	/*�����־λ*/
	if((i==1)&&Clear_flag==0){
		LCD_DrawRecFill(10, 145, 60, 170,BROWN);//���Ч��
	}	
	if(i!=0){
		Clear_flag = 1;
		Display_String(20,150,80,16,"���",16);
	}else{
		Clear_flag = 0;
		Display_String(20,150,80,16,"ȡ��",16);
	}

	/*�������*/
	if(key==KEY_ESC){				//�����
		Esc_flag = 0;
		LCD_DrawRecFill(10, 145, 60, 170,BROWN);//���Ч��
		if(i!=0)							//��Χ���0
			Input_Data[--i] = ' ';
	}else if(Esc_flag==0){
		Esc_flag = 1;
	}
	
	if(*Clear_All){
		for(i=0;i<11;i++)
			Input_Data[i] = ' ';
		i=0;
		Esc_flag=1;
		*Clear_All = 0;
	}
	
	return Input_Data;
}

/***************************************************************
	�������ܣ����ڳ�ʼ��
	������WINDOWS_INIT_TYPE windows ������Ϣ
****************************************************************/
void Windows_Init(WINDOWS_INIT_TYPE windows)
{
	Clear_flag = 0;
	Clear_All = 1;
	LCD_Clear(windows.Clear_Color);
	BACK_COLOR = windows.Back_Color;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(windows.Location,3,130,16,windows.Name,16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,windows.Button1,16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,windows.Button2,16);
	
}

/************************************************************************
	�������ܣ�������Ƭ��
	������WINDOWS_TYPE t ��������Ϣ�� 
				u8 **show			 ����ʾ��Ƭ�����ݣ�
				u8 i					 ����ڼ���
				u8 j					 ���ݵڼ���
				u16 color			 ����Ƭ��ɫ
*************************************************************************/
void Windows_Title(WINDOWS_TYPE t, u8 **show,u8 i, u8 j,u16 color)
{
	LCD_DrawRecFill((t.St_x+j*(t.Weight+t.Jx_x)),(t.St_y+i*(t.Hight+t.Jx_y)), 
									(t.St_x+j*(t.Weight+t.Jx_x)+t.Weight), (t.St_y+i*(t.Hight+t.Jx_y)+t.Hight),color);
	Display_String((t.St_x+j*(t.Weight+t.Jx_x)+4),(t.St_y+i*(t.Hight+t.Jx_y)+4),80,16,(u8 *)show[j+i*t.tls_x],16);	
}

/*************************************************************************
	�������ܣ�������Ƭ
	������WINDOWS_TYPE t ��������Ϣ�� 
				u8 **show			 ����ʾ��Ƭ�����ݣ�
				u16 color			 ����Ƭ��ɫ
**************************************************************************/
void Windows_Titles(WINDOWS_TYPE t, u8 **show,u16 color)
{
	u8 i=0,j=0;
	/*��ʾ�˵�*/
	for(i=0;i<t.tls_y;i++){
		for(j=0;j<t.tls_x;j++)
			Windows_Title(t,show,i,j,color);
	}
}

/**************************************************************************
	�������ܣ�
***************************************************************************/
u8 Common_Key(short *i,short *j,u8 tls_x, u8 tls_y,u8 *Old_flag, u8 *Self_flag,u8 *New_flag)
{
	u8 key;
	key = Key_Scan();
	
	/*�˳�*/
	if((key==KEY_ESC)&&Clear_flag==0){
		*Self_flag = 0;
		*Old_flag = 1;
	}
	/*ѡ��*/
	if(key==KEY_WKUP){
		*Self_flag = 0;
		*New_flag = 1;
	}	
	
	/*������������ѡ��*/
	if(key==KEY_DOWN)		*i += 1;
	if(key==KEY_UP)			*i -= 1;
	if(key==KEY_LEFT)		*j -= 1;
	if(key==KEY_RIGHT)	*j += 1;
	if(*i>tls_y-1) *i = 0;
	if(*j>tls_x-1) *j = 0;
	if(*i<0)	 *i = tls_y - 1;
	if(*j<0)	 *j = tls_x - 1;
	
	return key;
}

