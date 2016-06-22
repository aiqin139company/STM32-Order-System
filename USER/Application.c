#include "Application.h"


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
		sprintf((char*)Date_String,"%d/%d/%d",Disp_Time.year,Disp_Time.month,Disp_Time.day);
		sprintf((char*)Time_String,"%d:%d:%d",Disp_Time.hour,Disp_Time.min,Disp_Time.second);
		/*��ʾʱ��*/
		Display_String(80,50,80,16,Date_String,16);
		Display_String(83,70,80,16,Time_String,16);
	}
	
}
