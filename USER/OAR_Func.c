#include "Application.h"

#define Food_Num    30

/*���ײ���,�����޸Ĵ�W25Q64�����ȡ*/
const u8 *Food[Food_Num] = {"������     ��10","���ݳ���   ��10","����       ��10",
														"�ɳ�ţ��   ��10","ʪ��ţ��   ��10","�����׷�   ��10",
														"������     ��10","����       ��10","����       ��10",
														"����       ��10","���ŷ�     ��12","���շ�     ��13",
														"�����ⷹ   ��15","�ཷ����   ��10","����ţ���� ��15",
														"����ʨ��ͷ ��15","¡����ŷ� ��10","���˼��׷� ��15",
														"��ˮ����   ��00","ˮ����ѡ   ��00"};

/*�������������ʾ��ʱ�򲻻���ʾ����*/														
const u8 *Null_Num[Food_Num] = {" "," "," "," "," ",
																" "," "," "," "," ",
																" "," "," "," "," ",
																" "," "," "," "," ",
																" "," "," "," "," ",
																" "," "," "," "," "};		

/*********************************************************************
	��������;������
**********************************************************************/
void Food_Func(u8 *Old_flag, u8 *Self_flag, u8 *New_flag, u8 *name)
{
	
	/*��ѯ�Ƿ��п���*/
	if(COUSTOMER.Table==0){
		*Self_flag = 0;
		Message_Warming_flag = 1;
		Message_Warming_Func(Old_flag,&Newtable_flag,"���ȿ���?");
	}else{
		
		u8 key,tmp=0;
		u8 *str;
		u8 Num[Food_Num][5] = {0};
		short i=0,j=0,tmp1=0,tmp2=1;			//����do while�������̸�����ʾ���ף���Ҫ�޸�tmp2 ��ʼֵ
		
		/*�˵�*/
		LIST_TYPE Menu = {(u8 **)Food,(u8 **)Null_Num};
		
		/*��ʼ�����꣬��ʼ�����꣬ͼ���ȣ�ͼ��߶ȣ����϶���ݼ�϶��������Ƭ��������������Ƭ������*/
		WINDOWS_TYPE Food_Info = {10,25,130,25,10,5,1,4};
		WINDOWS_TYPE Num_Info  = {160,25,50,25,10,5,1,4};
		
		/*������ʼ�����꣬����1������2*/
		WINDOWS_INIT_TYPE Win={94,"    ","ȡ��","ȷ��"};
		Win.Name = name;
		
		/*�����ʼ��*/
		Windows_Init(Win);
		str = (u8 *)malloc(Food_Num);
		
		do{
			/*��ȡ���ܼ�ֵ*/
			key = Common_Key(&i,&j,5, Food_Info.tls_y,Old_flag, Self_flag, Self_flag);
			if(key==KEY_WKUP){
				*Self_flag = 0;
				Message_Warming_flag = 1;
				/*�����ַ���*/
				Menu.Num[i+j*Num_Info.tls_y] = Num[i+j*Num_Info.tls_y];		//ӳ��Num�ĵ�ַ��Menu.Num ����
			}
			
			/*�������*/
			Key_Input_Str(Num_Info,i,0,key,3,Num[i+j*Food_Info.tls_y]);
			BACK_COLOR = Theme_SLE;
			Display_String(164,(Num_Info.St_y+i*(Num_Info.Hight+Num_Info.Jx_y)+4),24,16,Num[i+j*Food_Info.tls_y],16);
			
			/*��ѡ���ͼ����Ӹ���*/
			if(tmp1!=i){
				/*�����ַ���*/
				Menu.Num[tmp1+tmp2*Num_Info.tls_y] = Num[tmp1+tmp2*Num_Info.tls_y];		//ӳ��Num�ĵ�ַ��Menu.Num ����
				/*�ָ�ԭ����ͼ����ɫ*/
				Windows_Title(Food_Info,(u8 **)Menu.Food+tmp2*Food_Info.tls_y,tmp1,0,Theme_BACK);
				Windows_Title(Num_Info,(u8 **)Menu.Num+tmp2*Num_Info.tls_y,tmp1,0,Theme_BACK);
				tmp1 = i;
				/*ѡ���µ�ͼ�꣬��Ӹ���*/
				Windows_Title(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,i,0,Theme_SLE);	
				Windows_Title(Num_Info,(u8 **)Menu.Num+j*Num_Info.tls_y,i,0,Theme_SLE);	
			}

			/*�仯�˵�*/
			if(tmp2!=j){
				/*��ʾ��ǰ�ڼ�ҳ*/
				sprintf((char *)str,"%d/%d",j+1,Food_Info.tls_y+1);
				BACK_COLOR = Theme_Color;
				Display_String(100,150,24,16,str,16);
				/*��ʾ�˵�*/
				Windows_Titles(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,Theme_BACK);
				Windows_Titles(Num_Info,(u8 **)Menu.Num+j*Num_Info.tls_y,Theme_BACK);
				/*ѡ���µ�ͼ�꣬��Ӹ���*/
				Windows_Title(Food_Info,(u8 **)Menu.Food+j*Food_Info.tls_y,i,0,Theme_SLE);
				Windows_Title(Num_Info,(u8 **)Menu.Num+j*Num_Info.tls_y,i,0,Theme_SLE);	
				tmp2 = j;
				i = 0;	
			}
			
		}while(*Self_flag);
		
		/*��ʾ����*/
		if(*Old_flag==0)
			Message_Warming_Func(Self_flag,New_flag,"�Ƿ�ȷ�ϣ�");
		
		/*���͵�˵����ݣ���������*/
		if(*New_flag==1){	
			
			COUSTOMER.Food = (u8 **)malloc(Food_Num);							//���ٿռ�
			COUSTOMER.Num = (u8 **)malloc(Food_Num);
			
			/*���ҵ�˵�*/
			for(i=0;i<Food_Num;i++){
				if(Menu.Num[i][0]>='0'&&Menu.Num[i][0]<='9'){				//�����е㵽��ʳ��
					COUSTOMER.Num[tmp] = Menu.Num[i];									//����ʳ��������ַ
					COUSTOMER.Food[tmp] = Menu.Food[i]; 							//����ʳ�����Ƶ�ַ
					tmp ++;																						//����ָ����һ��ָ������Ԫ��
				}
			}
		
			/*���͵�˵�*/
			sprintf((char *)str,"���Ӻţ�%d",COUSTOMER.Table);
			Send_msg(0x08,str);
			for(i=0;i<tmp;i++){
				sprintf((char *)str,"%s***������%s",COUSTOMER.Food[i],COUSTOMER.Num[i]);
				Send_msg(0x08,str);
			}
			
			free(COUSTOMER.Food);																				//�ͷſռ�
			free(COUSTOMER.Num);
		}
		free(str);
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

