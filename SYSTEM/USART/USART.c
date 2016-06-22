#include "USART.h"

/*
	�������ܣ����ڳ�ʼ��
	Ӳ�����ӣ� TX ��PA9
						 RX ��PA10
*/
void USART1_Init(u32 baud)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	/*�������ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	/*�������GPIO��*/
	/*PA9�����������*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*PA10��������*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*���ô�����ؼĴ���*/
	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStructure);
	/*�����ж�*/
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	Set_NVIC(USART1_IRQn,2,2);
	/*ʹ�ܴ���*/
	USART_Cmd(USART1, ENABLE);
	
}

/*
	�������ܣ���дputc����,��Ҫ��Ϊ��ʵ��printf����
	����ԭ�ͣ�
	extern _ARMABI int fputc(int \*c*\, FILE * \*stream*\) __attribute__((__nonnull__(2)));
	�ڡ�stdio.h���ļ���618��
*/
int fputc(int c,FILE *file)
{
	USART_SendData(USART1, c);								//��������
	while(RESET==USART_GetFlagStatus(USART1, USART_FLAG_TXE));	//�ȴ��������
	return c;											//���ط��͵��ַ�
}

/*
	�������ܣ���дgetc��������Ҫ��Ϊ��ʵ��scanf����
	����ԭ��;
	extern _ARMABI int fgetc(FILE * \*stream*\) __attribute__((__nonnull__(1)));
	�ڡ�stdio.h���ļ���594��
*/
int fgetc(FILE *file)
{
	while(RESET==USART_GetFlagStatus(USART1, USART_FLAG_RXNE));	//�ȴ��������ǿ�
	return USART_ReceiveData(USART1);						//���ؽ���������
}


///*
//	�������ܣ������жϷ�����
//*/
//void USART1_IRQHandler(void)
//{
//	u16 dat;
//	if(RESET==USART_GetITStatus(USART1, USART_FLAG_RXNE))
//		dat = USART_ReceiveData(USART1);
//	if(RESET==USART_GetITStatus(USART1, USART_FLAG_TXE))
//		USART_SendData(USART1, dat);
//}

