#ifndef __RF_DAT_H__
#define __RF_DAT_H__

//typedef struct
//{
//    unsigned int adr;     //��ַ
//		unsigned int value;   //��ֵ
//}_RF_Dat;

typedef struct
{
	  unsigned char len;     //����֡����
    unsigned char adr;     //��ַ 
		unsigned char str[50];	//���ַ���
}_RF_Dat;

extern _RF_Dat RF_Dat;

#define RFDATLEN sizeof(RF_Dat) //8���ֽ�



/**********************��С������ת��*************************
				ԭ��:�ߵ�λ����
*************************************************************/
#define LittletoBig16(A)   ((((unsigned short)(A) & 0xff00) >> 8) | (((unsigned short)(A) & 0x00ff) << 8))
#define LittletoBig32(A)   ((((unsigned int)(A) & 0xff000000) >> 24)|(((unsigned int)(A) & 0x00ff0000) >> 8)|(((unsigned int)(A) & 0x0000ff00) << 8)|(((unsigned int)(A) & 0x000000ff) << 24))                                         
/*************************************************************/

extern unsigned char RF_Read_Buff[];//���ջ�����

#endif


