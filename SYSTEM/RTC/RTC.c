#include "RTC.h"

u32 RTC_CNT;
u8 sec_flag = 0;
const u8 *COMPILED_DATE = __DATE__;//��ñ�������
const u8 *COMPILED_TIME = __TIME__;//��ñ���ʱ��

/*
	�������ܣ�RTC��ʼ��
*/
u8 RTC_Init(void)
{
	u16 i=0;
	
	/*���û���þ�����,�����þ�ֱ������RTC->CR�Ĵ����������ж�*/
	if(BKP_ReadBackupRegister(BKP_DR1) != 0xaaaa){

		/*1.�������ݽӿ�ʱ�ӣ���Դ�ӿ�ʱ��*/
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR, ENABLE);
		PWR_BackupAccessCmd(ENABLE);			//����д��RTC�ͺ󱸼Ĵ���	
		
		/*2.������������ƼĴ���RTC*/
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);//ѡ��LSE������ΪRTCʱ�ӣ�
		
		/*3.�ȴ��ⲿ����LSE��32Khz���񣩾���*/
		while(!RCC->BDCR &1<<1){
			i ++;
			if(i==250) return 1;
		}
		
		/*4.�ⲿ��������ʹ��*/
		RCC_LSEConfig(RCC_LSE_ON);
		
		/*5.�ȴ�RTOFF�Ĵ���ֵΪ1*/
		while(!(RTC->CRL&1<<5));
		
		/*6.��CNFֵΪ1����������ģʽ*/
		RTC_EnterConfigMode();	
		
		/*7.RTC��ؼĴ�������*/
		RTC->PRLH = 0;			//�����Ƶ��������λ
		RTC->PRLL = 0x7fff;	//���÷�Ƶ��������λ���պ�1s
		RTC_ITConfig(RTC_IT_OW|RTC_IT_SEC, ENABLE);//��������ж� �������ж�
		/*����ʱ��*/
		Auto_Set_Time();
		
		/*8. ���CNF��־λ���˳�����ģʽ*/
		RTC_ExitConfigMode();		
		
		/*9. ��ѯRTOFF��ֱ��RTOFFλ��Ϊ��1����ȷ��д�����Ѿ���ɡ�*/
		while(!RTC->CRL&1<<5);
		
		/*10. ��ѯ�����Ƿ�ͬ��*/
		while(!RTC->CRL&1<<3);

		/*11.����RTCʱ��*/
		RCC_RTCCLKCmd(ENABLE);
		/*12.�򱸷���Ĵ���1д���־*/
		BKP_WriteBackupRegister(BKP_DR1, 0xaaaa);
	}else{
		while(!RTC->CRL&1<<5);	//�ȴ�RTOFF�Ĵ�����ֵΪ1���ȴ���һ�β������
		RTC_EnterConfigMode();	//��CNFֵΪ1����������ģʽ
		RTC_ITConfig(RTC_IT_OW|RTC_IT_SEC, ENABLE);//��������ж� �������ж�
		RTC_ExitConfigMode();		//���CNF��־λ���˳�����ģʽ
	}
	
	/*�����ж�*/
	Set_NVIC(RTC_IRQn,2,1);
	
	return 0;
}


/*
	�������ܣ�RTC�жϷ�����
*/
void RTC_IRQHandler(void)
{
	if(RTC_GetITStatus(RTC_IT_SEC))	//���ж�
	{
		sec_flag = 1;
		RTC_CNT = RTC_GetCounter();
	}
	RTC_ClearITPendingBit(RTC_IT_SEC);	//�����־λ
}


/*
	�������ܣ�����RTCʱ��
	������TIME_DATE :ʱ��ṹ������
*/
void Set_RTC_Time(TIME_TYPE time)
{		
		u32 second_base=0;
		u16 day_base=0;
	
		/*�����2008�굽��������ʱ�������*/
		day_base += (time.year - year_base)*365 + (time.year - year_base)/4 
								+ (((time.year-year_base/4)&&(time.year-year_base%4))?1:0);		//�� ��ͨ������+�����������Ĵ���*1��
		day_base += (time.month-1)*30 + (time.month + ((time.month>8)?1:0))/2 
								- ((time.month<3)?0:((time.year%400==0)||((time.year%4==0)&&(time.year%100))?1:2));						//��	
		day_base += time.day - 1;																																			//��
	
		/*�����ܹ��ж�����*/
		second_base += day_base * 24 * 3600;
		second_base += time.hour * 3600;																														//ʱ
		second_base += time.min * 60;																															//��
		second_base += time.second;																																//��
	
		/*�������ݽӿ�ʱ�ӣ���Դ�ӿ�ʱ��*/
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR, ENABLE);
		PWR_BackupAccessCmd(ENABLE);			//����д��RTC�ͺ󱸼Ĵ���	
	
		while(!RTC->CRL&1<<5);				//�ȴ�RTOFF��һ��д�������
		RTC_EnterConfigMode();				//��CNFֵΪ1����������ģʽ
		RTC_SetCounter(second_base);	//��RTC->CNT����д��ʱ��
		RTC_ExitConfigMode();					//���CNF��־λ���˳�����ģʽ
	
}

/*
	�������ܣ�����Ϊ��λ��ʱ��ת��Ϊ��������ʱ����
	������u32 RTC_CNT
*/
void Get_RTC_Time(u32 RTC_CNT,TIME_TYPE *time)
{
		u8 month_base[12]={31,28,31,30,31,30,31,31,30,31,30,31};
		u8 i=0;
			
		sec_flag = 0;													//������־
		time->second 	=  RTC_CNT % 60;				//��
		time->min 		= (RTC_CNT / 60)%60;		//��
		time->hour 		= (RTC_CNT / 3600)%24;	//ʱ
		time->year 		= (RTC_CNT / (3600*24*365)) + year_base;			//�������һ�꣬ģ������
		time->month 	= 1;
		time->day 		= (RTC_CNT / (3600*24))-((time->year-year_base)*365 + ((time->year-year_base)/4)+1);			//�õ�ʣ��һ�������=������-��ȥ���������
		
		if((time->year%400==0)||((time->year%4==0)&&(time->year%100))){							//���������Ļ����޸�����month_base[1]Ϊ29
			month_base[1]	= 29;
			for(i=0;i<12;i++){																				//ѭ����12��
				if(time->day>=month_base[i]){														//�����Ǹ��¼�����
					time->day = time->day-month_base[i];
					time->month += 1;
				}
			}	
			time->day += 1;
		}else{																											//�����ƽ��Ļ����޸�����month_base[1]Ϊ28	
			month_base[1] = 28;
			for(i=0;i<12;i++){
				if(time->day>=month_base[i]){
					time->day = time->day-month_base[i] ;
					time->month += 1;
				}
			}
			time->day += 1;
		}
}


/*
	�������ܣ��Ƚ������ַ���ָ�����ȵ������Ƿ����
	����:s1,s2Ҫ�Ƚϵ������ַ���;len,�Ƚϳ���
	����ֵ:1,���;0,�����
*/
u8 str_cmpx(u8*s1, u8*s2, u8 len)
{
  u8 i;
  for(i=0;i<len;i++){
		if((*s1++) != *s2++)
			return 0;
	}
  return 1;
}

/*
	�������ܣ��Զ�����ʱ��Ϊ������ʱ��
*/
const u8 Month_Tab[12][3] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
void Auto_Set_Time(void)
{
    u8 month[3];
		u8 i,day,hour,min,second;
		u16 year;
		TIME_TYPE time;		
		
		/*�����ַ���*/
		sscanf((char*)COMPILED_DATE,"%s%d%d",month,(int*)&day,(int*)&year);
		sscanf((char*)COMPILED_TIME,"%d:%d:%d",(int*)&hour,(int*)&min,(int*)&second);
		/*�����·�*/
    for(i=0;i<12;i++)
			if(str_cmpx((u8*)Month_Tab[i],month,3))break;
    time.month = i + 1; 			//�õ��·�
		/*����ֵ����time�ṹ��*/
		time.day = day;
		time.year = year;
		time.hour = hour;
		time.min = min;
		time.second = second;
		/*���Դ�ӡʱ��*/
//		printf("%d %d %d\r\n%d:%d:%d\r\n",time.year,time.month,time.day,time.hour,time.min,time.second);
		/*����ʱ��*/
		Set_RTC_Time(time);
}


