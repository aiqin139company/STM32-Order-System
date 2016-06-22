#include "Application.h"

#define Food_Num    30

//void Key_Input2(WINDOWS_TYPE t,u8 x,u8 y,u8 key, u8 range,u8 *str,u16 color);

/*�˵�����,�����޸Ĵ�W25Q64�����ȡ*/
const u8 *Food[Food_Num] = {"����     ��10","����     ��10","����     ��10",
														"����     ��10","����     ��10","����     ��10",
														"����     ��10","���ŷ�   ��12","���շ�   ��13"};
						
const u8 *Null_Num[Food_Num] = {0};		

/*********************************************************************
	��������;������
**********************************************************************/
void Food_Func(u8 *Old_flag, u8 *Self_flag, u8 *New_flag, u8 *name)
{
	#ifdef Debug_Get_Num
	u8 debug=0;
	#endif
	u8 key,sure_flag=0;
	u8 Num[Food_Num][5] = {0};
	short i=0,j=0,tmp1=0,tmp2=0;	
	/*�˵�*/
	LIST_TYPE Menu = {(u8 **)Food,(u8 **)Null_Num,(u8 **)Null_Num};
	/*��ʼ�����꣬��ʼ�����꣬ͼ���ȣ�ͼ��߶ȣ����϶���ݼ�϶��������Ƭ��������������Ƭ������*/
	WINDOWS_TYPE Food_Info = {10,25,130,25,10,5,1,4};
	/*��ʼ�����꣬��ʼ�����꣬ͼ���ȣ�ͼ��߶ȣ����϶���ݼ�϶��������Ƭ��������������Ƭ������*/
	WINDOWS_TYPE Num_Info  = {160,25,50,25,10,5,1,4};
	/*������ɫ��������ɫ��������ʼ�����꣬����1������2*/
	WINDOWS_INIT_TYPE Win={GBLUE,LBBLUE,94,"    ","ȡ��","ȷ��"};
	Win.Name = name;
	/*�����ʼ��*/
	Windows_Init(Win);
	/*��ʾ�˵�*/
	Windows_Titles(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,LBBLUE);
	Windows_Titles(Num_Info,(u8 **)Menu.Num+j*Num_Info.tls_y,LBBLUE);
	/*ѡ���һ��ͼ�꣬��Ӹ���*/
	Windows_Title(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,i,0,CYAN);
	Windows_Title(Num_Info,(u8 **)Menu.Num+j*Num_Info.tls_y,i,0,CYAN);
	/*ѭ���˵�*/
	do{
		/*��ȡ���ܼ�ֵ*/
		key = Common_Key(&i,&j,5, Food_Info.tls_y,Old_flag, Self_flag, New_flag);
		if(key==KEY_WKUP){
			sure_flag = 1;
		}
		
		/*�������*/
		Key_Input1((Num_Info.St_x),
							(Num_Info.St_y+i*(Num_Info.Hight+Num_Info.Jx_y)), 
							(Num_Info.St_x+Num_Info.Weight),
							(Num_Info.St_y+i*(Num_Info.Hight+Num_Info.Jx_y)+Num_Info.Hight),
							key,3,Num[i+j*Food_Info.tls_y]);
		Display_String(164,(Num_Info.St_y+i*(Num_Info.Hight+Num_Info.Jx_y)+4),24,16,Num[i+j*Food_Info.tls_y],16);

		/*��ѡ���ͼ����Ӹ���*/
		if(tmp1!=i){
			/*�����ַ���*/
			Menu.Num[tmp1+tmp2*Num_Info.tls_y] = Num[tmp1+tmp2*Num_Info.tls_y];		//ӳ��Num�ĵ�ַ��Menu.Num ����
			/*�ָ�ԭ����ͼ����ɫ*/
			Windows_Title(Food_Info,(u8 **)Menu.Food+tmp2*Food_Info.tls_y,tmp1,0,LBBLUE);
			Windows_Title(Num_Info,(u8 **)Menu.Num+tmp2*Num_Info.tls_y,tmp1,0,LBBLUE);
			tmp1 = i;
			/*ѡ���µ�ͼ�꣬��Ӹ���*/
			Windows_Title(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,i,0,CYAN);	
			Windows_Title(Num_Info,(u8 **)Menu.Num+j*Num_Info.tls_y,i,0,CYAN);	
			#ifdef Debug_Get_Num
				for(debug=0;debug<30;debug++){
					printf("%s ",Menu.Num[debug]);
				}
				printf("\r\n");
			#endif
		}

		/*�仯�˵�*/
		if(tmp2!=j){
			/*��ʾ�˵�*/
			Windows_Titles(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,LBBLUE);
			Windows_Titles(Num_Info,(u8 **)Menu.Num+j*Num_Info.tls_y,LBBLUE);
			/*ѡ���µ�ͼ�꣬��Ӹ���*/
			Windows_Title(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,i,0,CYAN);
			Windows_Title(Num_Info,(u8 **)Menu.Num+j*Num_Info.tls_y,i,0,CYAN);	
			tmp2 = j;
			i = 0;	
			#ifdef Debug_Get_Num
				for(debug=0;debug<30;debug++)
					printf("%s ",Menu.Num[debug]);
				printf("\r\n");
			#endif
		}
		
	}while(*Self_flag);
	
	if(sure_flag){
		
	}
	
}

/*********************************************************************
	�������ܣ���˽���
*********************************************************************/
void Order_Func(void)
{
	/*�ϵĽ����־����������־���½����־����������*/
	Food_Func(&Menu_flag, &Order_flag,&Menu_flag,"���");
}

/*********************************************************************
	�������ܣ��Ӳ˽���
*********************************************************************/
void AddFood_Func(void)
{		
	/*�ϵĽ����־����������־���½����־����������*/
	Food_Func(&Menu_flag, &AddFood_flag,&Menu_flag,"�Ӳ�");
}

/*********************************************************************
	�������ܣ��˲˽���
*********************************************************************/
void RetreatFood_Func(void)
{	
	/*�ϵĽ����־����������־���½����־����������*/
	Food_Func(&Menu_flag, &RetreatFood_flag,&Menu_flag,"�˲�");
}

/*********************************************************************/

