#include "SYSTEM_WKUP.h"

//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI
//CHECK OK
//091209
//WFI  ���߲����ڷ����ж�ʱ������
__asm void WFI_SET(void)
{
    WFI;    
}

/********************************************************************
* Function   : Sys_Standby()
* Description: �������ģʽ,��������Ҫ���жϻ���
* Calls      : 
* Called By  : 
* Input      : ��
* Output     : ��
* Return     : ��
* Author     : �
* Others     : 
* date of completion : 2015.09.13
* date of last modify: 2015.09.13
*********************************************************************/
void Sys_Standby(void)
{
    SCB->SCR |= 1 << 2; //ʹ��SLEEPDEEPλ (SYS->CTRL)
    RCC->APB1ENR |= 1 << 28; //ʹ�ܵ�Դʱ��
    PWR->CSR |= 1 << 8;      //����WKUP���ڻ���
    PWR->CR |= 1 << 2;       //���Wake-up ��־
    PWR->CR |= 1 << 1;       //PDDS��λ
    WFI_SET();               //ִ��WFIָ��
}


/*
	�������ܣ����ػ���ʼ��
*/
void WKUP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*����PA��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	/*�ر�jtag*/
	AFIO->MAPR &= ~(0x7<<24);
	AFIO->MAPR |=  0x04<<24;
	/*�������GPIO��*/
	/*����PA0*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);

	RTC_Init();		//ʵʱʱ�ӳ�ʼ��
	Delay_Init();	//��ʱ������ʼ��.�������ʱ���ı�Ҫ
}

/*
	�������ܣ���鰴���Ƿ���1.5��
	����ֵ���Ƿ���1.5�� 0��û�� 1:��
*/
u8 Check_WKUP(void)
{
	u8 i=0;
	while(1){
		if(WKUP)	i ++;
		else			return 0;	//�����κι��ˣ���Ϊ������ʱ�������ڽ��뵽���������ʱ�򣬰����Ѿ�������
												//��һ��ʼû�����أ�����һ����ʱ���󴥻��ѣ����������ʱ�����ˣ��ý���͹���ģʽ���ǻ����
												//������һ�����⣬�ĵ�������û����
		Delay_ms(10);				//��ʱ��⣬ͬʱ��߰���ʶ�������ȣ�����Ҳ������ʱ����
		if(i>150){					//1.5��
			i = 0;
			return 1;
		}
	}	
}

