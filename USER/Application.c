#include "Application.h"

u8 Login_flag = 0;
u8 Home_flag = 0;
u8 Menu_flag = 0;
u8 Newtable_flag = 0;
u8 Order_flag = 0;
u8 Reminder_flag = 0;
u8 AddFood_flag = 0;
u8 RetreatFood_flag = 0;
u8 Query_flag = 0;
u8 MMS_flag = 0;
u8 Settings_flag = 0;
u8 Settings_Time_flag = 1;
u8 Settings_User_flag = 0;
u8 Settings_LAB_flag = 0;
u8 Settings_About_flag = 0;
u8 Clear_flag = 0;

/*
	�������ܣ�ʵʱʱ��
*/
void RTC_Func(void)
{
	u8 Date_String[20];				//���DATE����
	u8 Time_String[20];				//���TIME����
	TIME_TYPE Disp_Time;			//�洢ʱ��ṹ��
	
	Display_HZ(220,60," ",16);	//��һ�£�������Ĳ���
	
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

/*
	�������ܣ��������봦��
	������u8 key���ⲿ����İ���ֵ
	����ֵ��������֮��������׵�ַ
*/
u8 *Key_Input(u8 key, u8 range)
{
	static u8 i=0,Esc_flag=1;
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
	
	return Input_Data;
}

