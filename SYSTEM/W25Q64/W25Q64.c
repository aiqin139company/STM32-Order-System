#include "W25Q64.h"

/*
	�������ܣ�W25Q64��ʼ��
	Ӳ�����ӣ�PC11 ��FLASH_CS1
						PC12 ��FLASH_CS2
*/
void W25Q64_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*����PCʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	/*�������GPIO��*/
	/*PC11,PC12�������*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/*��ʼ��SPI2�ӿ�*/
	SPI1_Init();
}

/*
	�������ܣ�flashоƬ����
*/
void FLASH_Chip_Erase(void)
{
	FLASH_WriteEnable();				//оƬдʹ��
	FLASH_CS = 0;								//ѡ��оƬ
	SPI1_Write_Read_Byte(0xC7);	//����оƬ����ָ��
	FLASH_CS = 1;								//ȡ��Ƭѡ
	FLASH_Check_Busy();					//��æ
}

/*
	�������ܣ���ȡ�豸ID
*/
u16 Get_DeviceID(void)
{
	u16 ID;
	FLASH_CS = 0;								//ѡ��оƬ
	SPI1_Write_Read_Byte(0x90);	//���ͻ�ȡоƬidָ��
	SPI1_Write_Read_Byte(0x00);	//����24λ��ַ��8λ
	SPI1_Write_Read_Byte(0x00);	//����24λ��ַ��8λ
	SPI1_Write_Read_Byte(0x00);	//����24λ��ַ��8λ
	
	ID = SPI1_Write_Read_Byte(0x00);	//��ȡ���쳧��ID
	ID = ID <<8 | (u16)SPI1_Write_Read_Byte(0x00);//��ȡ�豸ID
	
	FLASH_CS = 1;								//ȡ��ѡ��оƬ
	return ID;									//����ID
}	

/*
	�������ܣ���flash�����ȡһ���ֽ�����
	������u32 ReadAddr ��ȡ�ĵ�ַ
	����ֵ����ȡ���ֽ�
*/
u8 FlASH_Read_Byte_Data(u32 addr)
{
	u8 dat;
	FLASH_CS = 0;												//ѡ��оƬ
	SPI1_Write_Read_Byte(0x03);					//���Ͷ�ȡ����ָ��
	
	SPI1_Write_Read_Byte(addr>>16);			//���͵�ַ��8λ
	SPI1_Write_Read_Byte(addr>>8);			//���͵�ַ��8λ
	SPI1_Write_Read_Byte(addr);					//���͵�ַ��8λ
	
	dat = SPI1_Write_Read_Byte(0x00);		//��ȡ����
	FLASH_CS = 1;												//ȡ��Ƭѡ
	
	return dat;													//��������
}

/*
	�������ܣ�flashоƬдʹ��
*/
void FLASH_WriteEnable(void)
{
	FLASH_CS = 0;			//����Ƭѡ
	SPI1_Write_Read_Byte(0x06);	//����дʹ��ָ��
	FLASH_CS = 1;			//����Ƭѡ
}


/*
	�������ܣ�FLASH��æ
*/
void FLASH_Check_Busy(void)
{
	u8 status;
	FLASH_CS = 0;									//����Ƭѡ
	SPI1_Write_Read_Byte(0x05);		//���Ͳ�æָ��
	do{
		status = SPI1_Write_Read_Byte(0x00);	//��״̬�Ĵ���1��ֵ
	}while((status & 0x01)!=0);
	FLASH_CS = 1;									//����Ƭѡ
}

/*
	�������ܣ�flash��������
	������u32 addr ��ַ
*/
void FLASH_Sector_Erase(u32 addr)
{
	FLASH_WriteEnable();						//дʹ��
	FLASH_CS = 0;										//����Ƭѡ
	SPI1_Write_Read_Byte(0x20);			//������������ָ��
	SPI1_Write_Read_Byte(addr>>16);	//���͵�ַ��8λ
	SPI1_Write_Read_Byte(addr>>8);	//���͵�ַ��8λ
	SPI1_Write_Read_Byte(addr);			//���͵�ַ��8λ
	FLASH_CS = 1;										//����Ƭѡ
	FLASH_Check_Busy();							//��æ
}


/*
	�������ܣ���flashоƬ����д��һ���ֽ�����
	������u32 addr ��ַ u8 dat ����
*/
void FLASH_Write_Byte_Data(u32 addr, u8 dat)
{
	FLASH_WriteEnable();							//дʹ��
	FLASH_CS = 0;											//����Ƭѡ
	SPI1_Write_Read_Byte(0x02);				//����ҳдָ��
	SPI1_Write_Read_Byte(addr>>16);		//���͵�ַ��8λ
	SPI1_Write_Read_Byte(addr>>8);		//���͵�ַ��8λ
	SPI1_Write_Read_Byte(addr);				//���͵�ַ��8λ
	SPI1_Write_Read_Byte(dat);				//����Ҫд�������
	FLASH_CS = 1;											//����Ƭѡ
	FLASH_Check_Busy();								//��æ
}


/*
	�������ܣ���flashоƬ�����ȡ���ⳤ������
	������u32 addr ��ַ��u16 len ���ȣ�u8 *dat �����׵�ַ
*/
void FLASH_Serial_Read_Data(u32 addr, u16 len, u8 *dat)
{
	u16 i;
	
	FLASH_CS = 0;											//����Ƭѡ
	SPI1_Write_Read_Byte(0x03);				//���Ͷ�ȡָ��
	SPI1_Write_Read_Byte(addr>>16);		//���͵�ַ��8λ
	SPI1_Write_Read_Byte(addr>>8);		//���͵�ַ��8λ
	SPI1_Write_Read_Byte(addr);				//���͵�ַ��8λ
	
	for(i=0;i<len;i++){								//��ȡ����
		dat[i] = SPI1_Write_Read_Byte(0x00);
	}
	
	FLASH_CS = 1;											//����Ƭѡ
}

/*
	�������ܣ���FLASHоƬ����д������ һ��ҳ
	������u32 addr ��ַ u16 len �ֽ����� u8 *dat ���������׵�ַ
*/
void FLASH_Page_Write_Data(u32 addr, u16 len, u8 *dat)
{
	u16 i;
	FLASH_WriteEnable();							//дʹ��
	FLASH_CS = 0;											//����Ƭѡ
	SPI1_Write_Read_Byte(0x02);				//����ҳдָ��
	SPI1_Write_Read_Byte(addr>>16);		//���͵�ַ��8λ
	SPI1_Write_Read_Byte(addr>>8);		//���͵�ַ��8λ
	SPI1_Write_Read_Byte(addr);				//���͵�ַ��8λ
	
	for(i=0;i<len;i++){
		SPI1_Write_Read_Byte(dat[i]);		//����Ҫд�������
	}
	
	FLASH_CS = 1;											//����Ƭѡ
	FLASH_Check_Busy();								//��æ
}

/*
	�������ܣ���FLASHоƬ���������ַд�����ⳤ�ȵ�����
	������u32 addr ��ַ u16 len �ֽ����� u8 *dat ���������׵�ַ
*/
void FLASH_Serial_Write_Data(u32 WriteAddr, u16 len, u8 *dat)
{
	u16 i=0;
	u16 num=0;
	
	num = 0xff - (u8)WriteAddr + 1;			//����һҳʣ�¶��ٿ�д���ֽ�
	if(num>=len){												//ʣ����д�ֽڿռ���ڵ��ڳ���ʱֱ�ӵ���ҳд
		FLASH_Page_Write_Data(WriteAddr,len,dat);		
	}else{															//�ֽڿռ䳤��С�ڳ���ʱ
		/*��ʼ����һҳ�Ĳ���*/													
		FLASH_Page_Write_Data(WriteAddr,num,dat);		//����һҳд��
		len -= num;													//���ȼ�ȥдȥ�ĳ���
		WriteAddr += num;										//��ַ��дȥ�ĳ���
		dat += num;													//����ָ��ָ��дȥ���ֽڵ���һλ�ֽ�
		/*��������һҳ����*/
		while(len>256){
			FLASH_Page_Write_Data(WriteAddr, 256, dat);		//����д��һ��ҳ
			len -= 256;																		//�������ȼ�ȥһ��ҳ������
			i ++;																					//���������������ٸ�����ҳ
			WriteAddr += i*256;														//��ַ��һ��ҳ
			dat += i*256;																	//���ݵ�ַ��һ��ҳ
		}
		/*ʣ�²���һҳ�Ĳ���*/
		FLASH_Page_Write_Data(WriteAddr,len,dat);
	}
}


