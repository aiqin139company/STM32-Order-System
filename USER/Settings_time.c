#include "Application.h"

/*ʱ����*/
const u8 *Time[6] = {"��","��","��","ʱ","��","��"};
const u8 *Null_time[6] = {0};

/*
	�������ܣ���������
*/
void Disp_Time_Info(WINDOWS_TYPE t,u8 x,u8 y,u8 *show,u16 color)
{
	LCD_DrawRecFill((t.St_x+y*(t.Weight+t.Jx_x)), (t.St_y+x*(t.Hight+t.Jx_y)), 
									(t.St_x+y*(t.Weight+t.Jx_x)+t.Weight), (t.St_y+x*(t.Hight+t.Jx_y)+t.Hight),color);
	Display_String((t.St_x+y*(t.Weight+t.Jx_x)+4),(t.St_y+x*(t.Hight+t.Jx_y)+4),36,16,show,16);					//��ʾʱ��
}

/*
	�������ܣ�����ʱ��
*/
void Settings_Time_Func(void)
{
	u8 key;
	u8 set_flag=0;
	short i=0,j=0,tmp1=1,tmp2=1;
	u8 date_time[6][5] = {0};
	TIME_TYPE time;
	
	/*��ʼ�����꣬��ʼ�����꣬ͼ���ȣ�ͼ��߶ȣ����϶���ݼ�϶��������Ƭ��������������Ƭ������*/
	WINDOWS_TYPE Set_Name_Info = {45,53,25,25,48,10,3,2};
	WINDOWS_TYPE Set_Time_Info = {5,53,40,25,33,10,3,2};
	/*������ɫ��������ɫ��������ʼ�����꣬����1������2*/
	WINDOWS_INIT_TYPE Set_Time_Win={78,"����ʱ��","ȡ��","ȷ��"};
	/*�����ʼ��*/
	Windows_Init(Set_Time_Win);	
	/*��ʾ�˵�*/
	Windows_Titles(Set_Name_Info,(u8 **)Time,Theme_BACK);
	Windows_Titles(Set_Time_Info,(u8 **)Null_time,Theme_BACK);
	
	do{
		
		/*��ȡ���ܼ�ֵ*/
		key = Common_Key(&i,&j,Set_Time_Info.tls_x,Set_Time_Info.tls_y,&Settings_flag,&Settings_Time_flag,&Settings_flag);		
		if(key==KEY_WKUP){
			set_flag = 1;
		}
		
		/*�����ȡʱ��*/	
		Key_Input1(Set_Time_Info,i,j,key,4,date_time[j+i*Set_Time_Info.tls_x]);
		Display_String((Set_Time_Info.St_x+j*(Set_Time_Info.Weight+Set_Time_Info.Jx_x)+4),	//��ʾʱ��
									(Set_Time_Info.St_y+i*(Set_Time_Info.Hight+Set_Time_Info.Jx_y)+4),36,16,date_time[j+i*Set_Time_Info.tls_x],16);					
		
		/*������ʾ*/
		if(tmp1!=i||tmp2!=j){	
			/*�ָ�ԭ����ͼ����ɫ*/
			Disp_Time_Info(Set_Time_Info,tmp1,tmp2,(u8 *)date_time[tmp2+tmp1*Set_Time_Info.tls_x],Theme_BACK);			
			tmp1 = i;
			tmp2 = j;
			/*ѡ���µ�ͼ�꣬��Ӹ���*/
			Disp_Time_Info(Set_Time_Info,i,j,(u8 *)date_time[tmp2+tmp1*Set_Time_Info.tls_x],Theme_SLE);
		}
		
	}while(Settings_Time_flag);	
	/*����ʱ��*/
	if(set_flag){
		sscanf((char *)date_time[0],"%d",(int*)&time.year);
		sscanf((char *)date_time[1],"%d",(int*)&time.month);
		sscanf((char *)date_time[2],"%d",(int*)&time.day);
		sscanf((char *)date_time[3],"%d",(int*)&time.hour);
		sscanf((char *)date_time[4],"%d",(int*)&time.min);
		sscanf((char *)date_time[5],"%d",(int*)&time.second);
		Set_RTC_Time(time);
	}
}



