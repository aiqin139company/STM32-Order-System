#ifndef _APPLICATION_H_
#define _APPLICATION_H_
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

/*����˵�ȫ��ʹ�ܱ�־*/
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


/*ʵʱʱ��*/
void RTC_Func(void);
/*��½����*/
void Login_Func(void);
u8 *Input_Scan(void);
/*������*/
void Home_Func(void);
/*�˵�����*/
void Menu_Func(void);
/*��������*/
void Newtable_Func(void);
/*��˽���*/
void Order_Func(void);
/*�߲˽���*/
void Reminder_Func(void);
/*�Ӳ˽���*/
void AddFood_Func(void);
/*�˲˽���*/
void RetreatFood_Func(void);
/*��ѯ����*/
void Query_Func(void);
/*��Ϣ����*/
void MMS_Func(void);
/*���ý���*/
void Settings_Func(void);

#endif
