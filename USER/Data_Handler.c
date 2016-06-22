#include "Application.h"

/****************************��Ӧ���漤��*************************/
u8 Login_flag 								=			1;						//��½����
u8 Home_flag									=			0;						//������
u8 Menu_flag 									=			0;						//�˵�����
u8 Newtable_flag 							=			0;						//��������
u8 Order_flag 								=			0;						//��˽���
u8 Reminder_flag 							=			0;						//�߲˽���
u8 AddFood_flag 							=			0;						//�Ӳ˽���
u8 RetreatFood_flag 					=			0;						//�˲˽���
u8 Query_flag 								=			0;						//��ѯ����
u8 MMS_flag 									=			0;						//��Ϣ����
u8 Settings_flag 							=			0;						//���ý���
u8 Settings_Time_flag 				=			0;						//���ý���---ʱ������
u8 Settings_User_flag 				=			0;						//���ý���---�û�����
u8 Settings_LAB_flag 					=			0;						//���ý���---���⼰����
u8 Settings_About_flag 				=			0;						//���ý���---����
u8 Message_Warming_flag				=			0;						//��ʾ��Ϣ����
/************************	*���ϵͳ�������************************/
u8 LCD_BL_LIGHT								=			10;						//��˻�LCD��ʾ�����ȼ���
u8 Clear_flag 								=			0;						//�����־ ��Clear_flag = 1 ʱ���������Ϊ0ʱ�����������
u8 Clear_All									=			1;						//ȫ�������־��
u8 Null 											= 		1;						//��Ч�����ռ�
/****************************������ݶ���***************************/

ACCOUNT_TYPE DefAcc ={"123456    ","123456    "};

/*******************************************************************
	�������ܣ�Ӳ����ʼ��
********************************************************************/
void Hardware_Init(void)
{
	LED_Init();			//LED�Ƴ�ʼ��
	Beep_Init();		//��������ʼ��
	KEY_Init();			//������ʼ��
	Delay_Init();		//��ʱ������ʼ��
	USART1_Init(115200);	//���ڳ�ʼ��
	W25Q64_Init();	//�洢оƬ��ʼ��
	Font_Init();		//�ֿ��ʼ��	
	LCD_Init();			//Һ������ʼ��
	RTC_Init();			//ʵʱʱ�ӳ�ʼ��
	TIM2_PWM_Init(100,720);//��ʱ��2PWM�������ʼ��
}


/*******************************************************************
	�������ܣ�SYSTEM���ݳ�ʼ��

********************************************************************/
void DCJ_SYSTEM_INIT()
{
	Delay_ms(10);																			//�ȴ�ϵͳ�ȶ�
	/*��ȡ���ݲ���ԭ����*/
	BEEP_EN = FlASH_Read_Byte_Data(BEEP_EN_Addr);				//��ȡ������״̬
	KEY_LED = FlASH_Read_Byte_Data(KEY_LED_EN_Addr);		//��ȡ���̵�״̬
	LCD_BL_LIGHT = FlASH_Read_Byte_Data(LCD_BL_Addr);		//��ȡ��Ļ���ȼ���
	LCD_BL_PWM = LCD_BL_LIGHT *5;												//��ԭ��Ļ����
	
//	FLASH_Sector_Erase(USER_Addr);
//	FLASH_Serial_Write_Data(USER_Addr, 10, "123456   ");
//	FLASH_Serial_Write_Data(PASSWD_Addr, 10, "123456   ");
//	FLASH_Serial_Read_Data(USER_Addr, 10, DefAcc.User);	//��ȡ�û���
//	FLASH_Serial_Read_Data(PASSWD_Addr, 10, DefAcc.Passwd);	//��ȡ�û���
}

void SAVE_Data(void)
{
	FLASH_Sector_Erase(BEEP_EN_Addr);		//��Ҫ�Ҳ�������
	FLASH_Sector_Erase(KEY_LED_EN_Addr);
	FLASH_Sector_Erase(LCD_BL_Addr);
	FLASH_Write_Byte_Data(BEEP_EN_Addr,BEEP_EN);
	FLASH_Write_Byte_Data(KEY_LED_EN_Addr,KEY_LED);
	FLASH_Write_Byte_Data(LCD_BL_Addr,LCD_BL_LIGHT);
}

/*******************************************************************
	�������ܣ�SYSTEM��ʼ	
********************************************************************/
void DCJ_SYSTEM_START(void)
{
	while(1){
		if(Login_flag)						Login_Func();								//��½����
		if(Home_flag)							Home_Func();								//������
		if(Menu_flag)							Menu_Func();								//�˵�����
		if(Newtable_flag) 				Newtable_Func();						//��������
		if(Order_flag)						Order_Func();								//��˽���
		if(Reminder_flag)					Reminder_Func();						//�߲˽���
		if(AddFood_flag)					AddFood_Func();							//�Ӳ˽���
		if(RetreatFood_flag)			RetreatFood_Func();					//�˲˽���
		if(Query_flag)						Query_Func();								//��ѯ����
		if(MMS_flag)							MMS_Func();									//��Ϣ����
		if(Settings_flag)					Settings_Func();						//���ý���
		if(Settings_Time_flag)		Settings_Time_Func();				//���ý���--����ʱ��
		if(Settings_User_flag)		Settings_User_Func();				//���ý���--�û�����
		if(Settings_LAB_flag)			Settings_LAB_Func();				//���ý���--���⼰����
		if(Settings_About_flag)		Settings_About_Func();			//���ý���--����
	}
}

