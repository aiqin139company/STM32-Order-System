#include "Application.h"

const u8 *name[2] = {"�û�:","����:"};
const u8 *mima[2] = {"        ","        "};

/*
	�������ܣ���½����
*/
void Login_Func(void)
{
	u8 key=0;
	short i=0,tmp=1;
	ACCOUNT_TYPE Account={0};
	
	/*��ʼ�����꣬��ʼ�����꣬ͼ���ȣ�ͼ��߶ȣ����϶���ݼ�϶��������Ƭ��������������Ƭ������*/
	WINDOWS_TYPE Login_Name = {20,45,60,28,0,22,1,2};
	WINDOWS_TYPE Login_Info = {95,45,100,28,0,22,1,2};
	/*������ʼ�����꣬����1������2*/
	WINDOWS_INIT_TYPE Login_Win = {77,"�û���½","���","ȷ��"};
	/*�����ʼ��*/
	Windows_Init(Login_Win);	
	/*��ʾ�˵�*/
	Windows_Titles(Login_Name,(u8 **)name,Theme_BACK);
	Windows_Titles(Login_Info,(u8 **)mima,Theme_BACK);
	
	do{
		
		/*��ȡ���ܼ�ֵ*/
		key = Common_Key((short *)&i,(short *)&Null,Null,Login_Info.tls_y, (u8 *)&Null,(u8 *)&Null,(u8 *)&Null);
		if(key==KEY_WKUP){
			if(!strcmp((const char *)Account.User,	(const char *)DefAcc.User)&&
				 !strcmp((const char *)Account.Passwd,(const char *)DefAcc.Passwd)){
				Login_flag = 0;				//ʧ�ܵ�½����
				Home_flag = 1;				//ʹ��������	
			}
				
			#ifdef Debug_Login
				printf("user:%s\r\npasswd:%s\r\n",Account.User,Account.Passwd);
				printf("DefAcc.user:%s\r\nDefAcc.passwd:%s\r\n",DefAcc.User,DefAcc.Passwd);
			#endif
		}
		
		/*�����ȡʱ��*/	
		Key_Input_Str(Login_Info,i,0,key,8,i?Account.Passwd:Account.User);
		BACK_COLOR = Theme_SLE;
		Display_String((Login_Info.St_x+4),(Login_Info.St_y+i*(Login_Info.Hight+Login_Info.Jx_y)+4),
										88,16,(i?Account.Passwd:Account.User),16);						
	
		/*������ʾ*/
		if(tmp!=i){	
			/*�ָ�ԭ����ͼ����ɫ*/
			DispStr_Win(Login_Info,tmp,0,tmp?Account.Passwd:Account.User,Theme_BACK);		
			tmp = i;
			/*ѡ���µ�ͼ�꣬��Ӹ���*/
			DispStr_Win(Login_Info,i,0,i?Account.Passwd:Account.User,Theme_SLE);	
		}
		
	}while(Login_flag);
	
}


