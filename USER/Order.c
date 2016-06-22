#include "Application.h"

/*ͼ����Ϣ*/
#define ST_X			10			//��ʼ������
#define ST_Y			33			//��ʼ������
#define Weight 		60			//ͼ����
#define Hight			25			//ͼ��߶�
#define JX			 	10			//��϶
#define titles		3


/*�˵�*/
const u8 Food[titles*titles][8] = {"����","����","����","����","����","����","����","���ŷ�","���շ�"};
/*�˵�ѡ����*/
static u8 Food_flag[titles][titles] = {0};

void Order_Func(void)
{
	u8 key;
	short i=0,j=0,tmp1=1,tmp2=1;
	
	LCD_Clear(YELLOW);
	BACK_COLOR = BROWN;
	
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(94,3,80,16,"���",16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,"����",16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,"ѡ��",16);	
	
	/*��ʾ�˵�*/
	for(i=0;i<titles;i++){
		for(j=0;j<titles;j++){
			LCD_DrawRecFill((ST_X+j*(Weight+JX)), (ST_Y+i*(Hight+JX)), (ST_X+j*(Weight+JX)+Weight), (ST_Y+i*(Hight+JX)+Hight),(Food_flag[i][j]?CYAN:BROWN));
			Display_String((ST_X+j*(Weight+JX)+4),(ST_Y+i*(Hight+JX)+3),60,16,(u8 *)Food[j+i*3],16);	
		}
	}
	i = 0;
	j = 0;
	
	/*ѭ����˲˵�*/
	do{
		key = Key_Scan();
		
		/*�˳�*/
		if(key==KEY_ESC){
			Order_flag = 0;
			Menu_flag = 1;
		}
		/*ѡ��*/
		if(key==KEY_WKUP){
			Food_flag[i][j] = !Food_flag[i][j];
		}	
		
		/*������������ѡ��*/
		if(key==KEY_DOWN)		i ++;
		if(key==KEY_UP)			i --;
		if(key==KEY_LEFT)		j --;
		if(key==KEY_RIGHT)	j ++;
		if(i>=titles) i = 0;
		if(j>=titles) j = 0;
		if(i<0)	 i = titles - 1;
		if(j<0)	 j = titles - 1;
		
		/*��ѡ���ͼ����Ӹ���*/
		if(tmp1!=i||tmp2!=j){	
			/*�ָ�ԭ����ͼ����ɫ*/
			if(!Food_flag[tmp1][tmp2]){
				LCD_DrawRecFill((ST_X+tmp2*(Weight+JX)), (ST_Y+tmp1*(Hight+JX)), (ST_X+tmp2*(Weight+JX)+Weight), (ST_Y+tmp1*(Hight+JX)+Hight),BROWN);
				Display_String((ST_X+tmp2*(Weight+JX)+4),(ST_Y+tmp1*(Hight+JX)+3),60,16,(u8 *)Food[tmp2+tmp1*3],16);	
			}
			tmp1 = i;
			tmp2 = j;
			/*ѡ���µ�ͼ�꣬��Ӹ���*/
			LCD_DrawRecFill((ST_X+j*(Weight+JX)), (ST_Y+i*(Hight+JX)), (ST_X+j*(Weight+JX)+Weight), (ST_Y+i*(Hight+JX)+Hight),CYAN);
			Display_String((ST_X+j*(Weight+JX)+4),(ST_Y+i*(Hight+JX)+4),60,16,(u8 *)Food[j+i*3],16);
		}

		/*�����ټ���۸��Լ�����*/
		
	}while(Order_flag);
	
	
}

