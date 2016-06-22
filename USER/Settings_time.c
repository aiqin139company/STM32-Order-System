#include "Application.h"

/*ʱ����*/
const u8 *Time[6] = {"    ��","    ��","    ��","    ʱ","    ��","    ��"};
u8 date_time[6][11] = {0};

/*
	�������ܣ���������
*/
void Disp_Time_Info(WINDOWS_TYPE t,u8 x,u8 y,u16 color)
{
	LCD_DrawRecFill((t.St_x+y*(t.Weight+t.Jx_x)), (t.St_y+x*(t.Hight+t.Jx_x)), (t.St_x+y*(t.Weight+t.Jx_x)+t.Weight), (t.St_y+x*(t.Hight+t.Jx_x)+t.Hight),color);
	Display_String((t.St_x+y*(t.Weight+t.Jx_x)+10),(t.St_y+x*(t.Hight+t.Jx_x)+4),60,16,(u8 *)Time[y+x*3],16);
	Display_String((t.St_x+y*(t.Weight+t.Jx_x)+4),(t.St_y+x*(t.Hight+t.Jx_x)+4),36,16,date_time[y+x*3],16);					//��ʾʱ��
}

/*
	�������ܣ�����ʱ��
*/
void Settings_Time_Func(void)
{
	u8 key;
	u8 *str;
	u8 set_flag=0;
	static short i=0,j=0,tmp1=0,tmp2=0;
	TIME_TYPE time;
	
	/*��ʼ�����꣬��ʼ�����꣬ͼ���ȣ�ͼ��߶ȣ����϶���ݼ�϶��������Ƭ��������������Ƭ������*/
	WINDOWS_TYPE Set_Time_Info = {10,53,60,25,10,10,3,2};
	/*������ɫ��������ɫ��������ʼ�����꣬����1������2*/
	WINDOWS_INIT_TYPE Set_Time_Win={YELLOW,BROWN,78,"����ʱ��","ȡ��","ȷ��"};
	/*�����ʼ��*/
	Windows_Init(Set_Time_Win);	
	/*��ʾ�˵�*/
	Windows_Titles(Set_Time_Info,(u8 **)Time,BROWN);
	Disp_Time_Info(Set_Time_Info,i,j,CYAN);
	do{
		
		/*��ȡ���ܼ�ֵ*/
		key = Common_Key(&i,&j,Set_Time_Info.tls_x,Set_Time_Info.tls_y,&Settings_flag,&Settings_Time_flag,&Settings_flag);		
		if(key==KEY_WKUP){
			set_flag = 1;
			strcpy((char *)date_time[j+i*Set_Time_Info.tls_x],(const char *)str);
		}
		
		/*������ʾ*/
		if(tmp1!=i||tmp2!=j){	
			/*�ָ�ԭ����ͼ����ɫ*/
			strcpy((char *)date_time[tmp2+tmp1*Set_Time_Info.tls_x],(const char *)str);
			Disp_Time_Info(Set_Time_Info,tmp1,tmp2,BROWN);		
			tmp1 = i;
			tmp2 = j;
			Clear_All = 1;
			/*ѡ���µ�ͼ�꣬��Ӹ���*/
			Disp_Time_Info(Set_Time_Info,i,j,CYAN);
		}
		/*�����ȡʱ��*/
		str = Key_Input(key,4,&Clear_All);			
		Display_String((Set_Time_Info.St_x+j*(Set_Time_Info.Weight+Set_Time_Info.Jx_x)+4),	//��ʾʱ��
										(Set_Time_Info.St_y+i*(Set_Time_Info.Hight+Set_Time_Info.Jx_x)+4),36,16,str,16);					
		
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




