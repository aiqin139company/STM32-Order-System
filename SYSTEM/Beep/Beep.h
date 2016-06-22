#ifndef _BEEP_H_
#define _BEEP_H_
#include <stm32f10x.h>
#include "SYS.h"
#include "Delay.h"
#include "LED.h"

extern u8 BEEP_EN;

/*���IO�ڶ���*/
#define Beep	PAout(12)

/*��غ�������*/
void Beep_Init(void);
void Beep_Alarm(void);

#endif

