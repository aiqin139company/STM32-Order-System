#include <stm32f10x.h>
#include "Application.h"

/*
	�������ܣ�������
*/
int main(void)
{
	/*Ӳ����ʼ��*/
	Hardware_Init();
	/*��˻�ϵͳ��ʼ��*/
	DCJ_SYSTEM_INIT();
}

