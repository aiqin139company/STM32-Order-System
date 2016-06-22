#ifndef _RTC_H_
#define _RTC_H_
#include "stm32f10x.h"
#include "sys.h"
#include "USART.h"
#include "ILI9341.h"

#define year_base 2008			//���

typedef struct{							//ʱ��ṹ��
	u16 year;			//��
	u8 month;		//��
	u8 day;			//��
	u8 hour;			//ʱ
	u8 min;			//��
	u8 second;		//��
}TIME_TYPE;

extern 	u32 RTC_CNT;
extern  u8 sec_flag;
extern const u8 *COMPILED_DATE;//��ñ�������
extern const u8 *COMPILED_TIME;//��ñ���ʱ��

u8 RTC_Init(void);									//RTC��ʼ��
void Set_RTC_Time(TIME_TYPE time);	//����RTCʱ��
void Get_RTC_Time(u32 RTC_CNT,TIME_TYPE *time);//ת��ʱ��

u8 str_cmpx(u8*s1, u8*s2, u8 len);	//�Ա��ַ���
void Auto_Set_Time(void);						//�Զ�����ʱ��

#endif
