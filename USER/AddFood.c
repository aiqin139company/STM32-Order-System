#include "Application.h"


/*�˵�����,�����޸Ĵ�W25Q64�����ȡ*/
const u8 *Food1[9] = {"����","����","����","����","����","����","����","���ŷ�","���շ�"};

void AddFood_Func(void)
{	
	u8 key;
	static short i=0,j=0,tmp1=1,tmp2=1;
	u8 Food_flag[3][3] = {0};
	/*�˵�*/
	LIST_TYPE Menu = {(u8 **)Food1,"10","10"};
	
	/*��ʼ�����꣬��ʼ�����꣬ͼ���ȣ�ͼ��߶ȣ����϶���ݼ�϶��������Ƭ��������������Ƭ������*/
	WINDOWS_TYPE AddFood_Info = {10,33,60,25,10,10,3,3};
	/*������ɫ��������ɫ��������ʼ�����꣬����1������2*/
	WINDOWS_INIT_TYPE AddFood_Win={YELLOW,BROWN,94,"�Ӳ�","����","ѡ��"};
	/*�����ʼ��*/
	Windows_Init(AddFood_Win);
	/*��ʾ�˵�*/
	Windows_Titles(AddFood_Info,(u8 **)Menu.Food,BROWN);
	/*ѡ���µ�ͼ�꣬��Ӹ���*/
	Windows_Title(AddFood_Info,(u8 **)Menu.Food,i,j,CYAN);	

	do{
		/*��ȡ���ܼ�ֵ*/
		key = Common_Key(&i,&j,AddFood_Info.tls_x, AddFood_Info.tls_y,&Menu_flag,&AddFood_flag,&AddFood_flag);
		if(key==KEY_WKUP)
			Food_flag[i][j] = !Food_flag[i][j];
		
		/*��ѡ���ͼ����Ӹ���*/
		if(tmp1!=i||tmp2!=j){	
			/*�ָ�ԭ����ͼ����ɫ*/
			if(!Food_flag[tmp1][tmp2])
				Windows_Title(AddFood_Info,(u8 **)Menu.Food,tmp1,tmp2,BROWN);
			tmp1 = i;
			tmp2 = j;
			/*ѡ���µ�ͼ�꣬��Ӹ���*/
			Windows_Title(AddFood_Info,(u8 **)Menu.Food,i,j,CYAN);
		}

		/*�����ټ���۸��Լ�����*/
		
	}while(AddFood_flag);
	
}
