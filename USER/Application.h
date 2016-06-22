#ifndef _APPLICATION_H_
#define _APPLICATION_H_
/***************************����ͷ�ļ�***********************************/
#include <stm32f10x.h>
#include "sys.h"
#include "LED.h"
#include "Beep.h"
#include "delay.h"
#include "KEY.h"
#include "USART.h"
#include "W25Q64.h"
#include "Font.h"
#include "ILI9341.h"
#include "RTC.h"
#include "string.h"
#include "Debug.h"
#include "TIM.h"
/*****************************��������***********************************/
/*****************************�û�����***********************************/
typedef struct{
	u8 *User;
	u8 *Passwd;
}ACCOUNT_TYPE;

/*****************************��˲���***********************************/
typedef struct{
	u8 Table;
	u8 *Food;
	u8 *Num;
}CUSTOMER_TYPE;

/*****************************�˵�����***********************************/
typedef struct{
	u8 **Food;
	u8 **Num;
}LIST_TYPE;

/*****************************������Ϣ***********************************/
typedef struct{
	u8 St_x;				//��ʼxλ��
	u8 St_y;				//��ʼyλ��
	u8 Weight;			//��
	u8 Hight;				//��
	u8 Jx_x;				//���϶
	u8 Jx_y;				//�ݼ�϶
	u8 tls_x;				//������Ƭ������
	u8 tls_y;				//������Ƭ������
}WINDOWS_TYPE;

/**************************�����ʼ����Ϣ********************************/
typedef struct{
	u16 Clear_Color;
	u16 Back_Color;
	u8 Location;
	u8 *Name;
	u8 *Button1;
	u8 *Button2;
}WINDOWS_INIT_TYPE;

/****************************����˵�ȫ��ʹ�ܱ�־***********************/
extern u8 Login_flag;
extern u8 Home_flag;
extern u8 Menu_flag;
extern u8 Newtable_flag;
extern u8 Order_flag;
extern u8 Reminder_flag;
extern u8 AddFood_flag;
extern u8 RetreatFood_flag;
extern u8 Query_flag;
extern u8 MMS_flag;
extern u8 Settings_flag;
extern u8 Settings_Time_flag;
extern u8 Settings_User_flag;
extern u8 Settings_LAB_flag;
extern u8 Settings_About_flag;
extern u8 Message_Warming_flag;
extern u8 Clear_flag;
extern u8 Clear_All;
extern u8 Null;
extern u8 LCD_BL_LIGHT;
extern ACCOUNT_TYPE Account;
extern ACCOUNT_TYPE DefAcc;
extern CUSTOMER_TYPE COUSTOMER;
/*****************************���ݴ洢��ַ*******************************/
#define DATA_BASE								(0x050000)
#define BEEP_EN_Addr						(0x00+DATA_BASE)
#define KEY_LED_EN_Addr					(0x10+DATA_BASE)
#define LCD_BL_Addr							(0x20+DATA_BASE)
#define USER_Addr								(0x30+DATA_BASE)
#define PASSWD_Addr							(0x40+DATA_BASE)

/*****************************��������***********************************/
void Hardware_Init(void);								/*Ӳ�����ֳ�ʼ��*/						
void DCJ_SYSTEM_INIT(void);							/*��˻�ϵͳ���ݳ�ʼ��*/
void DCJ_SYSTEM_START(void);						/*��˻�ϵͳ��ʼ*/
void SAVE_Data(void);										/*��������*/
void Login_Func(void);									/*��½����*/						
void Home_Func(void);										/*������*/							
void Menu_Func(void);										/*�˵�����*/						
void Newtable_Func(void);								/*��������*/								
void Order_Func(void);									/*��˽���*/						
void Reminder_Func(void);								/*�߲˽���*/									
void AddFood_Func(void);								/*�Ӳ˽���*/								
void RetreatFood_Func(void);						/*�˲˽���*/									
void Query_Func(void);									/*��ѯ����*/							
void MMS_Func(void);										/*��Ϣ����*/					
void Settings_Func(void);								/*���ý���*/								
void Settings_Time_Func(void);					/*���ý���--����ʱ��*/										
void Settings_User_Func(void);					/*���ý���--�û�����*/											
void Settings_LAB_Func(void);						/*���ý���--���⼰����*/									
void Settings_About_Func(void);					/*���ý���--����*/											
void RTC_Func(void);										/*ʵʱʱ��*/	
void Message_Warming_Func(u8 *Old_flag, u8 *New_flag, u8 *Str);		/*��Ϣ��ʾ����*/

/*******************************������غ���*******************************/
u8 *Input_Scan(void);																								//�������벻����Χ
u8 *Key_Input(u8 key, u8 range, u8 *Clear_All);											//�����������Χ
void Key_Input1(u8 x1,u8 y1,u8 x2,u8 y2,u8 key,u8 range,u8 *str);
u8 Common_Key(short *i,short *j,u8 tls_x, u8 tls_y,u8 *Old_flag, u8 *Self_flag,u8 *New_flag);	//���ܼ�

/*******************************������غ���********************************/
void Windows_Init(WINDOWS_INIT_TYPE windows);												//�����ʼ��
void Windows_Title(WINDOWS_TYPE t, u8 **show,u8 i, u8 j,u16 color);	//������Ƭ��
void Windows_Titles(WINDOWS_TYPE t, u8 **show,u16 color);						//������Ƭ

/********************************��ȡ���Ӻ�*********************************/
u16 Get_Table_Func(u8 *Old_flag, u8 *Self_flag, u8 *New_flag,u8 *name,u8 *show,u8 *warming);

#endif
