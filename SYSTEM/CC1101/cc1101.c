/*
** CC1101 433MHz����ģ���໥ͨ��
** 2014-11-16
*/
#include "cc1101.h"

//#include "RF_Send.h"
//#include "task.h"
//***************���๦�ʲ������ÿ���ϸ�ο�DATACC1100Ӣ���ĵ��е�48-49ҳ�Ĳ�����******************
//INT8U PaTabel[8] = {0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04};  //-30dBm   ������С
//INT8U PaTabel[8] = {0x17,0x17 ,0x17 ,0x17 ,0x17 ,0x17,0x17 ,0x17}; //-20dBm
//INT8U PaTabel[8] = {0x1D,0x1D ,0x1D ,0x1D ,0x1D ,0x1D,0x1D ,0x1D}; //-15dBm
//INT8U PaTabel[8] = {0x26,0x26 ,0x26 ,0x26 ,0x26 ,0x26,0x26 ,0x26}; //-10dBm
//INT8U PaTabel[8] = {0x37,0x37 ,0x37 ,0x37 ,0x37 ,0x37,0x37 ,0x37}; //-6dBm
//INT8U PaTabel[8] = {0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60};//0dBm
//INT8U PaTabel[8] = {0x86,0x86 ,0x86 ,0x86 ,0x86 ,0x86,0x86 ,0x86}; //5dBm

const u8 PaTabel[8] = {0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0};//10dBm

u8 RF_Read_Buff[66];//���ջ�����

_RF_Sta  RF_Sta;//RF״̬
/////////////////////////////////////////////////////////////////
const RF_SETTINGS rfSettings =
{
    0x00,
    0x08,   // FSCTRL1   Frequency synthesizer control.
    0x00,   // FSCTRL0   Frequency synthesizer control.
    0x10,   // FREQ2     Frequency control word, high byte.
    0xA7,   // FREQ1     Frequency control word, middle byte.
    0x62,   // FREQ0     Frequency control word, low byte.
    0x5B,   // MDMCFG4   Modem configuration.
    0xF8,   // MDMCFG3   Modem configuration.
    0x03,   // MDMCFG2   Modem configuration.
    0x22,   // MDMCFG1   Modem configuration.
    0xF8,   // MDMCFG0   Modem configuration.

    0x08,   // CHANNR    Channel number.//����ͨ����,���ͺͽ��ձ���һ��
    0x47,   // DEVIATN   Modem deviation setting (when FSK modulation is enabled).
    0xB6,   // FREND1    Front end RX configuration.
    0x10,   // FREND0    Front end RX configuration.
    0x18,   // MCSM0     Main Radio Control State Machine configuration.
// 0x0F,   // MCSM1     Main Radio Control State Machine configuration.
    0x1D,   // FOCCFG    Frequency Offset Compensation Configuration.
    0x1C,   // BSCFG     Bit synchronization Configuration.
    0xC7,   // AGCCTRL2  AGC control.
    0x00,   // AGCCTRL1  AGC control.
    0xB2,   // AGCCTRL0  AGC control.

    0xEA,   // FSCAL3    Frequency synthesizer calibration.
    0x2A,   // FSCAL2    Frequency synthesizer calibration.
    0x00,   // FSCAL1    Frequency synthesizer calibration.
    0x11,   // FSCAL0    Frequency synthesizer calibration.
    0x59,   // FSTEST    Frequency synthesizer calibration.
    0x81,   // TEST2     Various test settings.
    0x35,   // TEST1     Various test settings.
    0x09,   // TEST0     Various test settings.
    0x0B,   // IOCFG2    GDO2 output pin configuration.
    0x06,   // IOCFG0D   ��64ҳ
//�������յ�����ʱΪMCU�ṩ�ж��ź�
//GDO0 output pin configuration. Refer to SmartRF?Studio User Manual for detailed pseudo register explanation.

    0x05,   // PKTCTRL1  Packet automation control.  //��ַУ���Լ�0(0x00)Ϊ�㲥��ַ�������ܹ㲥

    0x05,   // PKTCTRL0  Packet automation control.   //ʹ��"�ɱ����ݰ�����ģʽ"
    0x08,   // ADDR      Device address.              //�豸��ַΪ0x08
    0xff    // PKTLEN    Packet length.               //�ڷǹ̶�����ʱ����Ϊ255
};




//*****************************************************************************************
//��������delayus(unsigned int s)
//���룺ʱ��
//�������
//������������ͨ͢ʱ,�ڲ���
//*****************************************************************************************

void delayus(u16 timeout)
{
    u8 i;
    do
    {
        for(i=0; i<20; i++);
    }
    while (--timeout);

}

/*****************************************************************************************/
//��������CC1101_SpiInit()
//���룺��
//�������
//����������SPI��ʼ������
/*****************************************************************************************/
void CC1101_SpiInit(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	/*����PA PCʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);
	/*�������GPIO��*/
	/*����PC4��CSN Ϊ�������*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);
	/*����PA4 GDO0��������*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	/*����PPC5��GDO2Ϊ��������*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC, GPIO_Pin_5);
	/*SPI�ӿڳ�ʼ��*/
	SPI1_Init();								
}


void Open_GD0_Interrupt(void)
{
	/* ʹ��io����ʱ�� */
	RCC->APB2ENR |=  1 << 0;
	/* ����Ϊ���ⲿ�ж�4��PA4�� */
	AFIO->EXTICR[1] &= ~(0xF << 0);
	AFIO->EXTICR[1] |=  (0x0 << 0);

	/* �����ⲿ�ж�4 */
	EXTI->IMR       |=  (1 << 4);

	/* �����ش��� */
	EXTI->RTSR      |=  (1 << 4);
	EXTI->FTSR      &= ~(1 << 4);
	
	/*����PA4�ж����ȼ�*/
	Set_NVIC(EXTI4_IRQn ,2,2);			

}
//*****************************************************************************************
//��������SpisendByte(INT8U dat)
//���룺���͵�����
//�������
//����������SPI����һ���ֽ�
//*****************************************************************************************
//u8 SpiTxRxByte(u8 dat)
//{
//    u8 i,j,temp= 0;
//    SCK = 0;
//    for(i=0; i<8; i++)
//    {
//        if(dat & 0x80)MOSI = 1;
//        else MOSI = 0;
//        j++;
//        j++;//ֻ���𵽼���ʱ
//        dat <<= 1;
//        j++;
//        j++;
//        SCK = 1;
//        j++;
//        j++;
//        temp <<= 1;
//        if(MISO)temp++;
//        SCK = 0;
//        j++;
//        j++;
//    }
//    return temp;
//}

//*****************************************************************************************
//��������void RESET_CC1100(void)
//���룺��
//�������
//������������λCC1100
//*****************************************************************************************
u8 RESET_CC1100(void)
{
    u16 n=0;
    CSN = 0;
    while(MISO)
    {
        if(++n>300)return 0;
        delayus(5);
    }
    n=0;
    SpiTxRxByte(CCxxx0_SRES); 		//д�븴λ����
    while(MISO)
    {
        if(++n>300)return 0;
        delayus(5);
    }
    CSN = 1;
    return 1;
}

//*****************************************************************************************
//��������void POWER_UP_RESET_CC1100(void)
//���룺��
//�������
//�����������ϵ縴λCC1100
//*****************************************************************************************
u8 POWER_UP_RESET_CC1100(void)
{
    CSN = 1;
    delayus(10);
    CSN = 0;
    delayus(10);
    CSN = 1;
    delayus(100);
    if(RESET_CC1100())return 1;  		//��λCC1100
    return 0;
}

//*****************************************************************************************
//��������void halSpiWriteReg(INT8U addr, INT8U value)
//���룺��ַ��������
//�������
//����������SPIд�Ĵ���
//*****************************************************************************************
void halSpiWriteReg(u8 addr, u8 value)
{
    u16 n=0;
    CSN = 0;
    while(MISO)
    {
        if(++n>300)break;
        delayus(5);
    }
    SpiTxRxByte(addr);		//д��ַ
    SpiTxRxByte(value);		//д������
    CSN = 1;
}

//*****************************************************************************************
//��������void halSpiWriteBurstReg(INT8U addr, INT8U *buffer, INT8U count)
//���룺��ַ��д�뻺������д�����
//�������
//����������SPI����д���üĴ���
//*****************************************************************************************
void halSpiWriteBurstReg(u8 addr, u8 *buffer, u8 count)
{
    u8 i, temp;
    temp = addr | WRITE_BURST;
    CSN = 0;
    while(MISO)
    {
        if(++i>250)break;
        delayus(5);
    }
    SpiTxRxByte(temp);
    for (i = 0; i < count; i++)
    {
        SpiTxRxByte(buffer[i]);
    }
    CSN = 1;
}

//*****************************************************************************************
//��������void halSpiStrobe(INT8U strobe)
//���룺����
//�������
//����������SPIд����
//*****************************************************************************************
void halSpiStrobe(u8 strobe)
{
    u8 n=0;
    CSN = 0;
    while(MISO)
    {
        if(++n>250)break;
        delayus(5);
    }
    SpiTxRxByte(strobe);		//д������
    CSN = 1;
}

//*****************************************************************************************
//��������INT8U halSpiReadReg(INT8U addr)
//���룺��ַ
//������üĴ�����������
//����������SPI���Ĵ���
//*****************************************************************************************
u8 halSpiReadReg(u8 addr)
{
    u8 temp, value=0;
    temp = addr|READ_SINGLE;//���Ĵ�������
    CSN = 0;
    while(MISO)
    {
        if(++value>250)break;
        delayus(5);
    }
    SpiTxRxByte(temp);
    value = SpiTxRxByte(0);
    CSN = 1;
    return value;
}


//*****************************************************************************************
//��������void halSpiReadBurstReg(INT8U addr, INT8U *buffer, INT8U count)
//���룺��ַ���������ݺ��ݴ�Ļ��������������ø���
//�������
//����������SPI����д���üĴ���
//*****************************************************************************************
void halSpiReadBurstReg(u8 addr, u8 *buffer, u8 count)
{
    u8 i=0,temp;
    temp = addr | READ_BURST;		//д��Ҫ�������üĴ�����ַ�Ͷ�����
    CSN = 0;
    while(MISO)
    {
        if(++i>250)break;
        delayus(5);
    }
    SpiTxRxByte(temp);
    for (i = 0; i < count; i++)
    {
        buffer[i] = SpiTxRxByte(0);
    }
    CSN = 1;
}


//*****************************************************************************************
//��������INT8U halSpiReadReg(INT8U addr)
//���룺��ַ
//�������״̬�Ĵ�����ǰֵ
//����������SPI��״̬�Ĵ���
//*****************************************************************************************
u8 halSpiReadStatus(u8 addr)
{
    u8 value=0,temp;
    temp = addr | READ_BURST;		//д��Ҫ����״̬�Ĵ����ĵ�ַͬʱд�������
    CSN = 0;
    while(MISO)
    {
        if(++value>250)break;
        delayus(5);
    }
    SpiTxRxByte(temp);
    value = SpiTxRxByte(0);
    CSN = 1;
    return value;
}

//*****************************************************************************************
//��������void CC1101_Set_PKTLEN(u8 len)
//���룺��
//�������
//��������������CC1101���ݳ���
//*****************************************************************************************
void CC1101_Set_PKTLEN(u8 len)//����CC1101���ݳ���
{
    halSpiWriteReg(CCxxx0_PKTLEN,len);
}

//*****************************************************************************************
//��������void halRfWriteRfSettings(RF_SETTINGS *pRfSettings)
//���룺��
//�������
//��������������CC1100�ļĴ���
//*****************************************************************************************
void halRfWriteRfSettings(void)
{

    halSpiWriteReg(CCxxx0_FSCTRL0,  rfSettings.FSCTRL2);//���Ѽӵ�
		// Write register settings
    halSpiWriteReg(CCxxx0_FSCTRL1,  rfSettings.FSCTRL1);
    halSpiWriteReg(CCxxx0_FSCTRL0,  rfSettings.FSCTRL0);
    halSpiWriteReg(CCxxx0_FREQ2,    rfSettings.FREQ2);
    halSpiWriteReg(CCxxx0_FREQ1,    rfSettings.FREQ1);
    halSpiWriteReg(CCxxx0_FREQ0,    rfSettings.FREQ0);
    halSpiWriteReg(CCxxx0_MDMCFG4,  rfSettings.MDMCFG4);
    halSpiWriteReg(CCxxx0_MDMCFG3,  rfSettings.MDMCFG3);
    halSpiWriteReg(CCxxx0_MDMCFG2,  rfSettings.MDMCFG2);
    halSpiWriteReg(CCxxx0_MDMCFG1,  rfSettings.MDMCFG1);
    halSpiWriteReg(CCxxx0_MDMCFG0,  rfSettings.MDMCFG0);
    halSpiWriteReg(CCxxx0_CHANNR,   rfSettings.CHANNR);
    halSpiWriteReg(CCxxx0_DEVIATN,  rfSettings.DEVIATN);
    halSpiWriteReg(CCxxx0_FREND1,   rfSettings.FREND1);
    halSpiWriteReg(CCxxx0_FREND0,   rfSettings.FREND0);
    halSpiWriteReg(CCxxx0_MCSM0 ,   rfSettings.MCSM0 );
    halSpiWriteReg(CCxxx0_FOCCFG,   rfSettings.FOCCFG);
    halSpiWriteReg(CCxxx0_BSCFG,    rfSettings.BSCFG);
    halSpiWriteReg(CCxxx0_AGCCTRL2, rfSettings.AGCCTRL2);
    halSpiWriteReg(CCxxx0_AGCCTRL1, rfSettings.AGCCTRL1);
    halSpiWriteReg(CCxxx0_AGCCTRL0, rfSettings.AGCCTRL0);
    halSpiWriteReg(CCxxx0_FSCAL3,   rfSettings.FSCAL3);
    halSpiWriteReg(CCxxx0_FSCAL2,   rfSettings.FSCAL2);
    halSpiWriteReg(CCxxx0_FSCAL1,   rfSettings.FSCAL1);
    halSpiWriteReg(CCxxx0_FSCAL0,   rfSettings.FSCAL0);
    halSpiWriteReg(CCxxx0_FSTEST,   rfSettings.FSTEST);
    halSpiWriteReg(CCxxx0_TEST2,    rfSettings.TEST2);
    halSpiWriteReg(CCxxx0_TEST1,    rfSettings.TEST1);
    halSpiWriteReg(CCxxx0_TEST0,    rfSettings.TEST0);
    halSpiWriteReg(CCxxx0_IOCFG2,   rfSettings.IOCFG2);
    halSpiWriteReg(CCxxx0_IOCFG0,   rfSettings.IOCFG0);
    halSpiWriteReg(CCxxx0_PKTCTRL1, rfSettings.PKTCTRL1);
    halSpiWriteReg(CCxxx0_PKTCTRL0, rfSettings.PKTCTRL0);
    halSpiWriteReg(CCxxx0_ADDR,     rfSettings.ADDR);
    halSpiWriteReg(CCxxx0_PKTLEN,   rfSettings.PKTLEN);
		//halSpiWriteReg(CCxxx0_IOCFG0 ,   rfSettings.PKTLEN);
}


//******************************************************************************************
//��������void Set_TxMode(void)
//���룺��
//�������
//��������������CC1100Ϊ����ģʽ
//*****************************************************************************************
void Set_TxMode(void)
{
    RF_Sta.mode=RF_TXMODE;
    RF_Sta.Busy=BUSY;//��æ
    GDO0_INTON;//���ж�
    halSpiStrobe(CCxxx0_SIDLE);//ǿ�ƽ������ģʽ
    halSpiStrobe(CCxxx0_STX);		//���뷢��ģʽ��������
}
//*****************************************************************************************
//��������void Set_RxMode(void)
//���룺��
//�������
//��������������CC1100Ϊ�������ģʽ
//*****************************************************************************************
void Set_RxMode(void)
{
    RF_Sta.mode=RF_RXMODE;
    halSpiStrobe(CCxxx0_SFRX);//��ϴ���ջ�����
    halSpiStrobe(CCxxx0_SIDLE);//ǿ�ƽ������ģʽ
    halSpiStrobe(CCxxx0_SRX);//�������ģʽ
    GDO0_INTON;//���ж�
}
//*****************************************************************************************
//��������void halRfSendPacket(INT8U *txBuffer, INT8U size)
//���룺���͵Ļ��������������ݸ���
//�����OK �ѷ���,����,�����־
//����������CC1100����һ������
//*****************************************************************************************

u8 halRfSendPacket(u8 *txBuffer, u8 size)
{
    halSpiWriteBurstReg(CCxxx0_TXFIFO, txBuffer, size);	//д��Ҫ���͵�����
    Set_TxMode();//���뷢��ģʽ��������
    while(RF_Sta.Busy==BUSY);//�ȴ��������
    return OK;
}

//*****************************************************************************************
//��������u8 halRfReceivePacket(u8 *rxBuffer)
//���룺u8 *rxBuffer ���յĻ�������
//�����CRC_OK ���ճɹ�,����,����ʧ��
//����������CC1100����һ������
//*****************************************************************************************
u8 halRfReceivePacket(u8 *rxBuffer)
{
    u8 status[2];
    u8 packetLength;
    if((halSpiReadStatus(CCxxx0_RXBYTES) & BYTES_IN_RXFIFO)) //����ӵ��ֽ�����Ϊ0
    {
        packetLength = halSpiReadReg(CCxxx0_RXFIFO);//������һ���ֽڣ����ֽ�Ϊ��֡���ݳ���
        halSpiReadBurstReg(CCxxx0_RXFIFO,(rxBuffer+1), packetLength); //�������н��յ�������
			  
        rxBuffer[0] = packetLength;				//�ѽ������ݳ��ȵ��޸�Ϊ��ǰ���ݵĳ���
        halSpiReadBurstReg(CCxxx0_RXFIFO, status, 2); 	//����CRCУ��λ
        halSpiStrobe(CCxxx0_SFRX);		//��ϴ���ջ�����
        return (status[1] & CRC_OK);	//���У��ɹ����ؽ��ճɹ�
    }
    return 0;
}
//*****************************************************************************************
//��������u8 CC1101_Init(void)
//���룺��
//�����1,��ʼ���ɹ�   0,��ʼ��ʧ��
//����������CC1100��ʼ��
//*****************************************************************************************
u8 CC1101_Init(void)
{
		CC1101_SpiInit();
    if(POWER_UP_RESET_CC1100())//��λCC1100
    {
        halRfWriteRfSettings();//����CC1100
        halSpiWriteBurstReg(CCxxx0_PATABLE, (u8 *)PaTabel, 8);//���ù���
        RF_Sta.Busy=IDLE;//����
        RF_Sta.DatFlag=ERR;
        Set_RxMode();//�������״̬
        return 1;
    }
		return 0;
}



//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
    EXTI->PR=1<<4;  //���LINE4�ϵ��жϱ�־λ
    GDO0_INTOFF;//���ж�
		KEY_LED=!KEY_LED;
    if(GDO0)
    {
        delayus(20);
        if(GDO0)
        {
            while(GDO0);
            switch(RF_Sta.mode)
            {
            case RF_TXMODE:
                halSpiStrobe(CCxxx0_SFTX);//��ϴ���ͻ�����
                RF_Sta.Busy=IDLE;//����
                RF_Sta.DatFlag=ERR;
                break;
            case RF_RXMODE:
                if(halRfReceivePacket(RF_Read_Buff))//��RXFIFO
                {
                    KEY_LED=!KEY_LED;
                    RF_Sta.DatFlag=OK;
                }
                break;
            default:
                break;
            }
        }
    }
    Set_RxMode();//�������״̬
}
