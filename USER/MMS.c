#include "Application.h"

void MMS_Func(void)
{
	_RF_Dat *RF_Dat;
	u8 n=0;
	
	WINDOWS_INIT_TYPE MMS_Win={94,"��Ϣ","����","ѡ��"};
	/*�����ʼ��*/
	Windows_Init(MMS_Win);	
	BACK_COLOR = Theme_Color;
	do{
	/*��ȡ���ܼ�ֵ*/
	Common_Key((short *)&Null,(short *)&Null,Null,Null, &Menu_flag,&MMS_flag,&Null);
	/*��ѯ������Ϣ��ȡ��Ϣ����ʾ����*/	
	if(RF_Sta.DatFlag==OK){
		 RF_Sta.DatFlag=ERR;
		 RF_Dat=(_RF_Dat *)RF_Read_Buff;
		 Display_String(10,25+(n++)*16,200,16,RF_Dat->str,16);
	 }
	 
	}while(MMS_flag);
	
}

/*
	�������ܣ���������
	������u8 adr������������ַ
				u8 *msg�����͵���Ϣ
*/
void Send_msg(u8 adr,u8 *msg)
{
		_RF_Dat Send_Buf;
		Send_Buf.adr=adr;																	//���͵�ַ													
		strcpy((char *)Send_Buf.str,(const char *)msg);		//�����ַ���
		Send_Buf.len=sizeof(Send_Buf)-1;				//�����ֽڱ������������ܳ���
		halRfSendPacket((u8 *)&Send_Buf,sizeof(Send_Buf));//��������
		Delay_ms(200);
}

