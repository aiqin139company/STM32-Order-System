�����Ѿ���ֲ���˴󲿷�����

�������֣�
1.LED�� ������
2.Beep:	������
3.KEY�� ������
4.LCD:  ������
5.W25Q64:������
6.RTC:	������
7.USART:������
8.ADC:	��ûŪ��������

�ֿⲿ�֣�
1.�ֿ⣺������

�û����棺
1.��½���� ������
2.�����棺��ʼ��
3.���ϵͳ����û��
4.��ѯϵͳ����û��
5.���ý��棺��û��


1.Login_Func;				//��½				�����

2.Home_Func;				//������			�����

4.Menu_Func;				//�˵�				�����

	1).Newtable_Func;		//����				�����

	2).Order_Func;			//���				�������������

	3).Reminder_Func;		//�߲�

	4).AddFood_Func;		//�Ӳ�
	
	5).RetreatFood_Func;	//�˲�
		
	6).Query_Func;			//��ѯ
	
	7).MMS_Func;			//���շ�������Ϣ
	
	8).Settings_Func;		//����
	
		a.Updata_Func;		//����
		
		b.User_Manage_Func;	//�û�����
		
		
extern 	u8 Newtable_flag;
extern  u8 Order_flag;
extern  u8 Reminder_flag;
extern  u8 AddFood_flag;
extern  u8 RetreatFood_flag;
extern  u8 Query_flag;
extern  u8 MMS_flag;
extern  u8 Settings_flag;

2016/3/14 22:40	������Ҫ�õ��Ľ�����Ӧ��c�ļ������ã������������ã�
��������һ��һ����������


2016/3/15 9:00 ��ʼ����������

2016/3/15 10:30 ��ʼ����˽���


��Ƭ �л��㷨ԭ��

00 01 02 
10 11 12
20 21 22

u8 tiepian[3][3];
u8 i=0l;j=0;

/*������������ѡ��*/
if(key==KEY_DOWN)		i ++;
if(key==KEY_UP)			i --;
if(key==KEY_LEFT)		j --;
if(key==KEY_RIGHT)		j ++;
if(i>=3) i = 0;
if(j>=3) j = 0;

/*ͼ����Ϣ*/
#define ST_X			10			//��ʼ������
#define ST_Y			33			//��ʼ������
#define Weight 			60			//ͼ����
#define Hight			25			//ͼ��߶�
#define JX			 	10			//��϶

LCD_DrawRecFill((ST_X+j*(Weight+JX)), (ST_Y+i*(Hight+JX)), (ST_X+j*(Weight+JX)+Weight), (ST_Y+i*(Hight+JX)+Hight),BROWN);
Display_String((ST_X+j*(Weight+JX)+4),(ST_Y+i*(Hight+JX)+3),60,16,(u8 *)Food[j+i*3],16);	

2016/3/15 16:07   �ѻ�����ɵ�˽����ˣ�����û���ʳ��۸��Լ��������


	
