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

	2).Order_Func;			//���				�������

	3).Reminder_Func;		//�߲�				�������������

	4).AddFood_Func;		//�Ӳ�				
	
	5).RetreatFood_Func;	//�˲�
		
	6).Query_Func;			//��ѯ
	
	7).MMS_Func;			//���շ�������Ϣ
	
	8).Settings_Func;		//����				����
	
		a.Settings_Time_Func;	//����ʱ��		���
		
		b.Settings_User_Func;	//�û�����
		
		c.Settings_LAB_Func;	//���⼰����	���
		
		d.Settings_About_Func;	//����			���
		
		
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
u8 i=0;j=0;

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

2016/3/15 16:10	  ��ʼ�����߲˽���

2016/3/15 16:51	  ������ɴ߲˽��棬����������

2016/3/15 16:54	  ��ʼ�������ý���

2016/3/15 21:16   ������ý������

2016/3/17 9:03		��ʼ��������



��Ҫ��������ݣ�
1.�û���
2.�û�����
3.���Ӻ�
4.�˵���
5.��ɶ��
6.�۸�
7.����
8.ʱ�����
9.��������


/*�û�����*/
typedef struct{
	u8 *User;
	u8 *Passwd;
}user;

/*��˲���*/
typedef struct{
	u8 *Table;
	u8 *Food;
	u8 *Price;
	u8 *Num;
}customer;

/*�˵�����*/
typedef struct{
	u8 **Food;
	u8 *Price;
	u8 *Num;
}list;

/*������Ϣ*/
typedef struct{
	u8 
}windows;


2016/3/19  15:14
��ʼ����ϵͳ����

����--����������--������--�����--��ȷ��

2015/3/26 19:00���±�д��¼����

ɾ��ԭ����¼�������д��룬��ͷ��д��
ԭ���ĵ�¼��������ֳ�����׸���������޸ģ�
��Ժ��ڵĹ���Ӱ��̫�󣬹�ɾ����д��
�����Ѿ��Ƚϼ����,�߼�������




2016/3/28  10:06 ��ʼŪ���ػ�

//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI
//CHECK OK
//091209
//WFI  ���߲����ڷ����ж�ʱ������
__asm void WFI_SET(void)
{
    WFI;    
}

/********************************************************************
* Function   : Sys_Standby()
* Description: �������ģʽ
* Calls      : 
* Called By  : 
* Input      : ��
* Output     : ��
* Return     : ��
* Author     : �
* Others     : 
* date of completion : 2015.09.13
* date of last modify: 2015.09.13
*********************************************************************/
void Sys_Standby(void)
{
    SCB->SCR |= 1 << 2; //ʹ��SLEEPDEEPλ (SYS->CTRL)
    RCC->APB1ENR |= 1 << 28; //ʹ�ܵ�Դʱ��
    PWR->CSR |= 1 << 8;      //����WKUP���ڻ���
    PWR->CR |= 1 << 2;       //���Wake-up ��־
    PWR->CR |= 1 << 1;       //PDDS��λ
    WFI_SET();               //ִ��WFIָ��
}



˼·--������ʼ--������һ��WKUP��

���WKUP���Ƿ���1.5��

�������ʱ�䳬��1.5�룬ֱ�ӿ���

���򲻿���������˯��ģʽ

��λ��ѣ�WKUP������ ����


void WKUP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*����PA,AFIOʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO , ENABLE);
	/*�ر�jtag*/
	AFIO->MAPR &= ~(0x7<<24);
	AFIO->MAPR |=  0x04<<24;
	/*�������GPIO��*/
	/*����PA0*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* ����Ϊ���ⲿ�ж�0��PA0�� */
	AFIO->EXTICR[0] &= ~(0xF << 0);
	AFIO->EXTICR[0] |=  (0x0 << 0);
	/* �����ⲿ�ж�0 */
	EXTI->IMR       |=  (1 << 0);
	/* �����ش��� */
	EXTI->RTSR      |=  (1 << 0);
	/*����PA0�ж����ȼ�*/
	Set_NVIC(EXTI0_IRQn ,1,1);	
}


void EXTI0_IRQHandler(void)
{
	 EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ
	 
	 if(0==Check_WKUP()){
		Sys_Standby();
	 }
	 
}



u8 Check_WKUP(void)
{
	u8 t=0,tx=0;
	if(WKUP){
		t ++;
		tx = 0;
	}else{
		t = 0;
		tx ++;
		return 0;
	}
	
	Delay_ms(30);
	
	if(t>50){
		t = 0;
		tx = 0;
		return 1;
	}
	
	return 0;
}

int main(void){
	
	WKUP_Init();
	
	if(0==Check_WKUP()){
		Sys_Standby();
	}
	
	system_init();
	
	while(1){
		
	}
	
}


