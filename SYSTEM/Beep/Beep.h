#ifndef _BEEP_H_
#define _BEEP_H_
#include <stm32f10x.h>
#include "SYS.h"

/*���IO�ڶ���*/
#define Beep	PAout(12)

/*��غ�������*/
void Beep_Init(void);

#endif

