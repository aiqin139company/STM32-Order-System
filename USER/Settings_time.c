#include "Application.h"

/*��ʼ�����꣬��ʼ�����꣬ͼ���ȣ�ͼ��߶ȣ����϶���ݼ�϶��������Ƭ��������������Ƭ������*/
WINDOWS_TYPE Settings_Time_Info = {10,53,60,25,10,10,3,2};

/*������ɫ��������ɫ��������ʼ�����꣬����1������2*/
WINDOWS_INIT_TYPE Settings_Time_Win={YELLOW,BROWN,78,"����ʱ��","ȡ��","ȷ��"};


/*ͼ����Ϣ*/
#define ST_X			10			//��ʼ������
#define ST_Y			53			//��ʼ������
#define Weight 		60			//ͼ����
#define Hight			25			//ͼ��߶�
#define JX			 	10			//��϶
#define titles_x	3
#define titles_y	2

/*ʱ����*/
const u8 Time[titles_x*titles_y][3] = {"��","��","��","ʱ","��","��"};
/*ʱ��ѡ����*/
u8 Time_flag[titles_y][titles_x] = {0};
u8 date_time[titles_x*titles_y][11] = {"2016","3","16","16","31","20"};

/*
	�������ܣ�����ʱ��
*/
void Settings_Time_Func(void)
{
	u8 key;
	u8 *str;
	u8 set_flag=0;
	short i=0,j=0,tmp1=0,tmp2=0;
	TIME_TYPE time;
	
	/*���ڳ�ʼ��*/
	Windows_Init(Settings_Time_Win);	

//	/*��ʾ�˵�*/
//	Windows_Titles(Settings_Time_Info,(u8 **)Time,BROWN);
	
	/*��ʾ���*/
	for(i=0;i<titles_y;i++){
		for(j=0;j<titles_x;j++){
			LCD_DrawRecFill((ST_X+j*(Weight+JX)), (ST_Y+i*(Hight+JX)), (ST_X+j*(Weight+JX)+Weight), (ST_Y+i*(Hight+JX)+Hight),BROWN);
			Display_String((ST_X+j*(Weight+JX)+40),(ST_Y+i*(Hight+JX)+4),20,16,(u8 *)Time[j+i*3],16);	
		}
	}
	i = 0;
	j = 0;
	
	do{
		
		/*��ȡ���ܼ�ֵ*/
		key = Common_Key(&i,&j,3,2, &Settings_flag,&Settings_Time_flag,&Settings_flag);		
		if(key==KEY_WKUP){
			set_flag = 1;
			strcpy((char *)date_time[j+i*3],(const char *)str);
		}
		
		/*��ѡ���ͼ����Ӹ���*/
		if(tmp1!=i||tmp2!=j){	
			/*�ָ�ԭ����ͼ����ɫ*/

			LCD_DrawRecFill((ST_X+tmp2*(Weight+JX)), (ST_Y+tmp1*(Hight+JX)), (ST_X+tmp2*(Weight+JX)+Weight), (ST_Y+tmp1*(Hight+JX)+Hight),BROWN);
			Display_String((ST_X+tmp2*(Weight+JX)+40),(ST_Y+tmp1*(Hight+JX)+3),20,16,(u8 *)Time[tmp2+tmp1*3],16);	
			strcpy((char *)date_time[tmp2+tmp1*3],(const char *)str);
			Display_String((ST_X+tmp2*(Weight+JX)+4),(ST_Y+tmp1*(Hight+JX)+4),36,16,date_time[tmp2+tmp1*3],16);		//��ʾʱ��
			tmp1 = i;
			tmp2 = j;
			Time_flag[i][j] = 1; 
			
			/*ѡ���µ�ͼ�꣬��Ӹ���*/
			LCD_DrawRecFill((ST_X+j*(Weight+JX)), (ST_Y+i*(Hight+JX)), (ST_X+j*(Weight+JX)+Weight), (ST_Y+i*(Hight+JX)+Hight),CYAN);
			Display_String((ST_X+j*(Weight+JX)+40),(ST_Y+i*(Hight+JX)+4),20,16,(u8 *)Time[j+i*3],16);
			Display_String((ST_X+j*(Weight+JX)+4),(ST_Y+i*(Hight+JX)+4),36,16,date_time[j+i*3],16);					//��ʾʱ��
		}
		
		str = Key_Input(key,4,&Time_flag[i][j]);			//��ȡʱ��
		Display_String((ST_X+j*(Weight+JX)+4),(ST_Y+i*(Hight+JX)+4),36,16,str,16);					//��ʾʱ��
		
	}while(Settings_Time_flag);	
	Clear_flag = 0;
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
