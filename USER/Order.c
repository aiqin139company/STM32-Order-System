#include "Application.h"

/*�˵�����,�����޸Ĵ�W25Q64�����ȡ*/
const u8 *Food[9] = {"����","����","����","����","����","����","����","���ŷ�","���շ�"};

/*
	��������;������
*/
void Food_Func(u8 *Old_flag, u8 *Self_flag, u8 *New_flag, u8 *name)
{
	u8 key;
	static short i=0,j=0,tmp1=1,tmp2=1;
	u8 Food_flag[3][3] = {0};
	/*�˵�*/
	LIST_TYPE Menu = {(u8 **)Food,"10","10"};
	/*��ʼ�����꣬��ʼ�����꣬ͼ���ȣ�ͼ��߶ȣ����϶���ݼ�϶��������Ƭ��������������Ƭ������*/
	WINDOWS_TYPE Food_Info = {10,33,60,25,10,10,3,3};
	/*������ɫ��������ɫ��������ʼ�����꣬����1������2*/
	WINDOWS_INIT_TYPE Win={GBLUE,LBBLUE,94,"    ","����","ѡ��"};
	Win.Name = name;
	/*�����ʼ��*/
	Windows_Init(Win);
	/*��ʾ�˵�*/
	Windows_Titles(Food_Info,(u8 **)Menu.Food,LBBLUE);
	/*ѡ���µ�ͼ�꣬��Ӹ���*/
	Windows_Title(Food_Info,(u8 **)Menu.Food,i,j,CYAN);
	
	/*ѭ����˲˵�*/
	do{
		/*��ȡ���ܼ�ֵ*/
		key = Common_Key(&i,&j,Food_Info.tls_x, Food_Info.tls_y,Old_flag, Self_flag, Self_flag);
		if(key==KEY_WKUP)
			Food_flag[i][j] = !Food_flag[i][j];
		
		/*��ѡ���ͼ����Ӹ���*/
		if(tmp1!=i||tmp2!=j){	
			/*�ָ�ԭ����ͼ����ɫ*/
			if(!Food_flag[tmp1][tmp2])
				Windows_Title(Food_Info,(u8 **)Menu.Food,tmp1,tmp2,LBBLUE);
			tmp1 = i;
			tmp2 = j;
			/*ѡ���µ�ͼ�꣬��Ӹ���*/
			Windows_Title(Food_Info,(u8 **)Menu.Food,i,j,CYAN);
		}

		/*�����ټ���۸��Լ�����*/
		
	}while(*Self_flag);
	
}

/*
	�������ܣ���˽���
*/
void Order_Func(void)
{
	/*�ϵĽ����־����������־���½����־����������*/
	Food_Func(&Menu_flag, &Order_flag,&Null,"���");
}

/*
	�������ܣ��Ӳ˽���
*/
void AddFood_Func(void)
{		
	/*�ϵĽ����־����������־���½����־����������*/
	Food_Func(&Menu_flag, &AddFood_flag,&Null,"�Ӳ�");
}

/*
	�������ܣ��˲˽���
*/
void RetreatFood_Func(void)
{	
	/*�ϵĽ����־����������־���½����־����������*/
	Food_Func(&Menu_flag, &RetreatFood_flag,&Null,"�Ӳ�");
}

