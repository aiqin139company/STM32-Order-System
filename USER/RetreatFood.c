#include "Application.h"

/*�˵�����,�����޸Ĵ�W25Q64�����ȡ*/
const u8 *Food2[9] = {"����","����","����","����","����","����","����","���ŷ�","���շ�"};

/*
	�������ܣ��˲˽���
*/
void RetreatFood_Func(void)
{
//	WINDOWS_INIT_TYPE RetreatFood_Win={YELLOW,BROWN,94,"�˲�","����","ѡ��"};
//	/*���ڳ�ʼ��*/
//	Windows_Init(RetreatFood_Win);
//	
//	do{
//		/*��ȡ���ܼ�ֵ*/
//		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Menu_flag,&RetreatFood_flag,&Null);
//		
//	}while(RetreatFood_flag);
//	
	
	
	u8 key;
	short i=0,j=0,tmp1=1,tmp2=1;
	u8 Food_flag[3][3] = {0};
	/*�˵�*/
	LIST_TYPE Menu = {(u8 **)Food2,"10","10"};
	
	/*��ʼ�����꣬��ʼ�����꣬ͼ���ȣ�ͼ��߶ȣ����϶���ݼ�϶��������Ƭ��������������Ƭ������*/
	WINDOWS_TYPE RetreatFood_Info = {10,33,60,25,10,10,3,3};

	/*������ɫ��������ɫ��������ʼ�����꣬����1������2*/
	WINDOWS_INIT_TYPE RetreatFood_Win={YELLOW,BROWN,94,"�˲�","����","ѡ��"};
	
	/*�����ʼ��*/
	Windows_Init(RetreatFood_Win);
	
	/*��ʾ�˵�*/
	Windows_Titles(RetreatFood_Info,(u8 **)Menu.Food,BROWN);
	
	/*ѭ����˲˵�*/
	do{
		/*��ȡ���ܼ�ֵ*/
		key = Common_Key(&i,&j,RetreatFood_Info.tls_x, RetreatFood_Info.tls_y,&Menu_flag,&RetreatFood_flag,&RetreatFood_flag);
		if(key==KEY_WKUP)
			Food_flag[i][j] = !Food_flag[i][j];
		
		/*��ѡ���ͼ����Ӹ���*/
		if(tmp1!=i||tmp2!=j){	
			/*�ָ�ԭ����ͼ����ɫ*/
			if(!Food_flag[tmp1][tmp2])
				Windows_Title(RetreatFood_Info,(u8 **)Menu.Food,tmp1,tmp2,BROWN);
			tmp1 = i;
			tmp2 = j;
			/*ѡ���µ�ͼ�꣬��Ӹ���*/
			Windows_Title(RetreatFood_Info,(u8 **)Menu.Food,i,j,CYAN);
		}

		/*�����ټ���۸��Լ�����*/
		
	}while(RetreatFood_flag);
	
	
}

