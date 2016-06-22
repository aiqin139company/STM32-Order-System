#include "SPI.h"

/*
	�������ܣ�SPI��ʼ��
	Ӳ�����ӣ�PA5 :SCLK
						PA6 :MISO
						PA7 :MOSI
*/
void SPI1_Init(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	/*����SPI1ʱ�ӣ�PBʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1,ENABLE);
	/*�������GPIO��*/
	/*PA5 PA6 PA7�����������*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*����SPI1��ؼĴ���*/
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 0;
	SPI_Init(SPI1, &SPI_InitStructure);
	/*ʹ��SPI1*/
	SPI_Cmd(SPI1, ENABLE);
}

/*
	�������ܣ�SPI1��дһ���ֽ�����
	������u8 Write_Dat:Ҫд�������
	����ֵ����ȡ��������
*/
u8 SPI1_Write_Read_Byte(u8 Write_Dat)
{
	u8 Read_Dat,i=0;
	while(RESET==SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)){
		i ++;	if(i==250) break;				//��ʱ�˳�
	}
	i = 0;
	SPI_I2S_SendData(SPI1,Write_Dat);
	while(RESET==SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)){
		i ++; if(i==250) break;				//��ʱ�˳�
	}
	Read_Dat = SPI_I2S_ReceiveData(SPI1);
	return Read_Dat;
}

