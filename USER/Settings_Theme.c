#include "Application.h"

/*�˵��б�*/
const u8 *Theme_title[3] = {"�ػƻ�","ǳ����","������"};
/*
	�������ܣ���������
*/
void Settings_Theme_Func(void)
{
	short i=0,tmp=1;
	u8 key,update_flag=0;
	/*������ʼ�����꣬����1������2*/
	WINDOWS_INIT_TYPE Settings_Theme_Win={78,"��������","����","ѡ��"};
	/*��ʼ�����꣬��ʼ�����꣬ͼ���ȣ�ͼ��߶ȣ����϶���ݼ�϶��������Ƭ��������������Ƭ������*/
	WINDOWS_TYPE Theme_Info = {10,25,200,25,5,5,1,3};	
	/*���ڳ�ʼ��*/
	Windows_Init(Settings_Theme_Win);	
	/*��ʼ���˵�*/
	Windows_Titles(Theme_Info,(u8 **)Theme_title,Theme_BACK);
	/*���ø���*/
	Windows_Title(Theme_Info,(u8 **)Theme_title,i,0,Theme_SLE);
	
	do{
		/*��ȡ���ܼ�ֵ*/
		key = Common_Key((short *)&i,(short *)&Null,Null,Theme_Info.tls_y, &Settings_flag,&Settings_Theme_flag,&Settings_flag);
		if(key==KEY_WKUP){	
			update_flag = 1;	//���������־λ��1
		}
		if(i!=tmp){
			/*�ָ�����*/
			Windows_Title(Theme_Info,(u8 **)Theme_title,tmp,0,Theme_BACK);
			tmp = i;
			/*���ø���*/
			Windows_Title(Theme_Info,(u8 **)Theme_title,i,0,Theme_SLE);
		}
		
	}while(Settings_Theme_flag);
	
	if(update_flag){						//����ϵͳ����
		switch(i){
			case 0 :{							//�ػƻ�
				Theme_Color = YELLOW;
				Theme_BACK = BROWN;
				Theme_SLE = GRAY;
				break;
			}
			case 1 :{ 							//ǳ����
				Theme_Color = GBLUE;
				Theme_BACK = LBBLUE;
				Theme_SLE = CYAN;			
				break;
			}
			case 2 :{ 							//������
				Theme_Color = MAGENTA;
				Theme_BACK = BRRED;
				Theme_SLE = GRED;			
				break;
			}
		}
		SAVE_Data();						//��������
	}
	
}
