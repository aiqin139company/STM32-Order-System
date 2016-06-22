#include <stm32f10x.h>
#include "LED.h"
#include "Beep.h"
#include "delay.h"
#include "KEY.h"
#include "USART.h"
#include "W25Q64.h"
#include "Font.h"
#include "ILI9341.h"

/*
	�������ܣ�������
*/
int main(void)
{
	u8 hz[]="��";
	u32 addr;
	u8 hzm[32];
	
	LED_Init();			//LED�Ƴ�ʼ��
	Beep_Init();		//��������ʼ��
	KEY_Init();			//������ʼ��
	Delay_Init();		//��ʱ������ʼ��
	USART1_Init(115200);	//���ڳ�ʼ��
	W25Q64_Init();	//�洢оƬ��ʼ��	
	Font_Init();		//�ֿ��ʼ��
	LCD_Init();			//Һ������ʼ��

//	/*��д�ֿ�*/
//	printf("���ڳ�ʼ���ɹ���\n");
//	printf("оƬ���ڲ�����....\r\n");
//	FLASH_Chip_Erase();				//оƬ����
//	printf("������ɣ�\r\n");
//	printf("�뷢���ֿ��ļ�.....\r\n");
	
	/*��֤�ֿ�*/
	addr = ((hz[0]-0xa1)*94+(hz[1]-0xa1))*32;
	FLASH_Serial_Read_Data(addr,32, hzm);
	Display_HZ(10,10,hzm,BLACK,16);
	
	while(1){
		KEY_LED = !KEY_LED;
		Delay_ms(1000);
	}
}


/*
	�������ܣ������жϷ�����
*/
void USART1_IRQHandler(void)
{
	u8 dat;
	static u32 i=0;
	if(RESET==USART_GetITStatus(USART1, USART_FLAG_RXNE)){	//�������ǿ�
		dat = USART_ReceiveData(USART1);			//�����ַ�
		FLASH_Write_Byte_Data(i++,dat);				//д���ַ�
	}
}

