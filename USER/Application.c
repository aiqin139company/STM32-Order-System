#include "Application.h"

/****************************��Ӧ���漤��*************************/
u8 Login_flag 								=			1;						//��½����
u8 Home_flag									=			0;						//������  
u8 Menu_flag 									=			0;						//�˵�����
u8 Newtable_flag 							=			0;						//��������
u8 Order_flag 								=			0;						//��˽���
u8 Reminder_flag 							=			0;						//�߲˽���
u8 AddFood_flag 							=			0;						//�Ӳ˽���
u8 RetreatFood_flag 					=			0;						//�˲˽���
u8 Query_flag 								=			0;						//��ѯ����
u8 MMS_flag 									=			0;						//��Ϣ����
u8 Settings_flag 							=			0;						//���ý���
u8 Settings_Time_flag 				=			0;						//���ý���---ʱ������
u8 Settings_Theme_flag 				=			0;						//���ý���---�û�����
u8 Settings_LAB_flag 					=			0;						//���ý���---���⼰����
u8 Settings_About_flag 				=			0;						//���ý���---����
u8 Message_Warming_flag				=			0;						//��ʾ��Ϣ����

/*****************************�������*****************************/
u16 Theme_Color 							= 		GBLUE;				//��������ɫ
u16 Theme_BACK  							= 		LBBLUE;				//���ⱳ��ɫ
u16 Theme_SLE 								= 		CYAN;					//����ѡ��ɫ

/****************************������ݶ���***************************/
ACCOUNT_TYPE DefAcc ={"123456","123456"};					//Ĭ���û�
CUSTOMER_TYPE COUSTOMER;													//�˿�

/************************	*���ϵͳ�������************************/
u8 LCD_BL_LIGHT								=			10;						//��˻�LCD��ʾ�����ȼ���
u8 Clear_flag 								=			0;						//�����־ ��Clear_flag = 1 ʱ���������Ϊ0ʱ�����������
u32 Null 											= 		1;						//��Ч�����ռ�

/*******************************************************************
	�������ܣ�Ӳ����ʼ��
********************************************************************/
void Hardware_Init(void)
{
	LED_Init();												//LED�Ƴ�ʼ��
	Beep_Init();											//��������ʼ��
	KEY_Init();												//������ʼ��
	Delay_Init();											//��ʱ������ʼ��
	#ifdef Debug
		USART1_Init(115200);						//���ڳ�ʼ��
	#endif
	W25Q64_Init();										//�洢оƬ��ʼ��
	Font_Init();											//�ֿ��ʼ��	
	LCD_Init();												//Һ������ʼ��
	RTC_Init();												//ʵʱʱ�ӳ�ʼ��
	TIM2_PWM_Init(100,720);						//��ʱ��2PWM�������ʼ��

	if(CC1101_Init())									//��ʼ��433ģ��
	{
		Open_GD0_Interrupt();
	}		
	else 	LCD_ShowString(50,10,200,16,16,"CC1101 RESET ERR");		
}

/*******************************************************************
	�������ܣ�SYSTEM���ݳ�ʼ��

********************************************************************/
void DCJ_SYSTEM_INIT()
{
	#ifdef Debug_Save
		u8 i;
		u8 tmp[10]={0};
	#endif
	Delay_ms(100);																		//�ȴ�ϵͳ�ȶ�
	/*�ж�ϵͳ�Ƿ��һ��ʹ��*/
	FlASH_Read_Byte_Data(FIRST_USE);									//������Ĳ�������һ������ ����		
	if(FlASH_Read_Byte_Data(FIRST_USE)!=0xaa){
		FLASH_Sector_Erase(FIRST_USE);									//��Ҫ�Ҳ�������
		FLASH_Write_Byte_Data(FIRST_USE,0xaa);					//��һ��ʹ��д����־0xaa
	}else{	
		/*��ȡ���ݲ���ԭ����*/
		Theme_Color = (u16)FlASH_Read_Byte_Data(Theme_Addr+0)<<8 | FlASH_Read_Byte_Data(Theme_Addr+1) ;
		Theme_BACK  = (u16)FlASH_Read_Byte_Data(Theme_Addr+2)<<8 | FlASH_Read_Byte_Data(Theme_Addr+3) ;
		Theme_SLE   = (u16)FlASH_Read_Byte_Data(Theme_Addr+4)<<8 | FlASH_Read_Byte_Data(Theme_Addr+5) ;
		
		#ifdef Debug_Save
			FLASH_Serial_Read_Data(Theme_Addr, 6, tmp);
			for(i=0;i<6;i++){
				printf("%X ",tmp[i]);
			}
			printf("Color:%X,Back:%X,SLE:%X\r\n",Theme_Color,Theme_BACK,Theme_SLE);
		#endif
		
		BEEP_EN = FlASH_Read_Byte_Data(BEEP_EN_Addr);				//��ȡ������״̬
		KEY_LED = FlASH_Read_Byte_Data(KEY_LED_EN_Addr);		//��ȡ���̵�״̬
		LCD_BL_LIGHT = FlASH_Read_Byte_Data(LCD_BL_Addr);		//��ȡ��Ļ���ȼ���
		LCD_BL_PWM = LCD_BL_LIGHT *5;												//��ԭ��Ļ����
	}
}
/*******************************************************************
	�������ܣ�SYSTEM���ݱ���

********************************************************************/
void SAVE_Data(void)
{
	FLASH_Sector_Erase(FIRST_USE);										//��Ҫ�Ҳ�������
	FLASH_Write_Byte_Data(FIRST_USE,0xaa);					
	FLASH_Write_Byte_Data(BEEP_EN_Addr,BEEP_EN);
	FLASH_Write_Byte_Data(KEY_LED_EN_Addr,KEY_LED);
	FLASH_Write_Byte_Data(LCD_BL_Addr,LCD_BL_LIGHT);
	FLASH_Write_Byte_Data(Theme_Addr+0,Theme_Color>>8);
	FLASH_Write_Byte_Data(Theme_Addr+1,Theme_Color);
	FLASH_Write_Byte_Data(Theme_Addr+2,Theme_BACK>>8);
	FLASH_Write_Byte_Data(Theme_Addr+3,Theme_BACK);
	FLASH_Write_Byte_Data(Theme_Addr+4,Theme_SLE>>8);
	FLASH_Write_Byte_Data(Theme_Addr+5,Theme_SLE);
}
/*******************************************************************
	�������ܣ�SYSTEM_BACK
********************************************************************/
void DCJ_SYSTEM_BACK(void)
{
	if(
		Login_flag 							==	0 &&
		Home_flag  							==	0 &&
		Menu_flag  							==	0 &&
		Newtable_flag						==	0	&&
		Order_flag 							==	0 &&
		Reminder_flag 					==	0 &&
		AddFood_flag 						==	0 &&
		RetreatFood_flag			  ==	0 &&
		Query_flag							==	0 &&
		MMS_flag 								==	0	&&
		Settings_flag						==	0	&&
		Settings_Time_flag			==	0	&&
		Settings_Theme_flag			==	0	&&
		Settings_LAB_flag				==	0	&&
		Settings_About_flag			==	0	&&
		Message_Warming_flag		==	0	
	)
	{
		Home_Func();															//ϵͳ��ƫ�˻ع����˵�
	}
}

/*******************************************************************
	�������ܣ�SYSTEM��ʼ	
********************************************************************/
void DCJ_SYSTEM_START(void)
{
	while(1){
		if(Login_flag)						Login_Func();								//��½����
		if(Home_flag)							Home_Func();								//������
		if(Menu_flag)							Menu_Func();								//�˵�����
		if(Newtable_flag) 				Newtable_Func();						//��������
		if(Order_flag)						Order_Func();								//��˽���
		if(Reminder_flag)					Reminder_Func();						//�߲˽���
		if(AddFood_flag)					AddFood_Func();							//�Ӳ˽���
		if(RetreatFood_flag)			RetreatFood_Func();					//�˲˽���
		if(Query_flag)						Query_Func();								//��ѯ����
		if(MMS_flag)							MMS_Func();									//��Ϣ����
		if(Settings_flag)					Settings_Func();						//���ý���
		if(Settings_Time_flag)		Settings_Time_Func();				//���ý���--����ʱ��
		if(Settings_Theme_flag)		Settings_Theme_Func();			//���ý���--��������
		if(Settings_LAB_flag)			Settings_LAB_Func();				//���ý���--���⼰����
		if(Settings_About_flag)		Settings_About_Func();			//���ý���--����
		DCJ_SYSTEM_BACK();																		//ϵͳ��ƫ�˻ع����˵�
	}
}

/*******************************************************************
	�������ܣ�ʵʱʱ��
********************************************************************/
void RTC_Func(void)
{
	u8 Date_String[10];				//���DATE����
	u8 Time_String[10];				//���TIME����
	TIME_TYPE Disp_Time;			//�洢ʱ��ṹ��
	
	/*���ж���ɺ������ʾ*/
	if(sec_flag){
		/*��ȡʱ��*/
		Get_RTC_Time(RTC_CNT,&Disp_Time);
		/*��ʽת�� XXXX/XX/XX  XX:XX:XX*/
		sprintf((char*)Date_String,"%04d/%02d/%02d",Disp_Time.year,Disp_Time.month,Disp_Time.day);
		sprintf((char*)Time_String,"%02d:%02d:%02d",Disp_Time.hour,Disp_Time.min,Disp_Time.second);
		/*��ʾʱ��*/
		Display_String(70,50,80,16,Date_String,16);
		Display_String(78,70,80,16,Time_String,16);
	}
	
}

/**************************************************************************
	�������ܣ�ͨ�ù��ܰ���
	������short *i: ���¼�
				short *j:	���Ҽ�
				u8 tls_x:���ҷ�Χ
				u8 tls_y:���·�Χ
				u8 *Old_flag:�Ͻ����־
				u8 *Self_flag:�Լ������־
				u8 *New_flag:�½����־
***************************************************************************/
u8 Common_Key(short *i,short *j,u8 tls_x, u8 tls_y,u8 *Old_flag, u8 *Self_flag,u8 *New_flag)
{
	u8 key;
	key = Key_Scan();
	
	/*�˳�*/
	if((key==KEY_ESC)&&Clear_flag==0){
		*Self_flag = 0;
		*Old_flag = 1;
	}
	/*ѡ��*/
	if(key==KEY_WKUP){
		*Self_flag = 0;
		*New_flag = 1;
	}	
	
	/*������������ѡ��*/
	if(key==KEY_DOWN)		*i += 1;
	if(key==KEY_UP)			*i -= 1;
	if(key==KEY_LEFT)		*j -= 1;
	if(key==KEY_RIGHT)	*j += 1;
	if(*i>tls_y-1) 			*i = 0;
	if(*j>tls_x-1)			*j = 0;
	if(*i<0)					 	*i = tls_y - 1;
	if(*j<0)	 					*j = tls_x - 1;
	
	return key;
}

/******************************************************************
	�������ܣ��������봦��
	������u8 key���ⲿ����İ���ֵ
				u8 range�����뷶Χ
				u8 *Clear_All�������־
	����ֵ��������֮��������׵�ַ
*******************************************************************/
u8 *Key_Input(u8 key, u8 range)
{
	static u8 i=0, Esc_flag=1;
	static u8 Input[11]="           ";	
	
	/*������ȡ����*/
	if(i<range){								//���뷶Χ
		if((key>0&&key<10))		//��������1-9
			Input[i++] = key + 0x30;
		if(key==KEY_0)				//��������0
			Input[i++] = '0';
		if(key==KEY_X)				//�����ַ�*
			Input[i++] = '*';
		if(key==KEY_J)				//�����ַ�#
			Input[i++] = '#';
	}
	
	/*�����־λ*/
	if((i==1)&&Clear_flag==0){
		LCD_DrawRecFill(10, 145, 60, 170,Theme_BACK);//���Ч��
	}	
	if(i!=0){
		Clear_flag = 1;
		Display_String(20,150,80,16,"���",16);
	}else{
		Clear_flag = 0;
		Display_String(20,150,80,16,"ȡ��",16);
	}

	/*�������*/
	if(key==KEY_ESC){				//�����
		Esc_flag = 0;
		LCD_DrawRecFill(10, 145, 60, 170,Theme_BACK);//���Ч��
		if(i!=0)							//��Χ���0
			Input[--i] = ' ';
	}else if(Esc_flag==0){
		Esc_flag = 1;
	}
	
	#ifdef Debug_Input
	printf("key:%d,i:%d,Clear_flag:%d,Input_Data:%s\r\n",key,i,Clear_flag,Input);
	#endif
	
	return Input;
}

/******************************************************************
	�������ܣ��������봦��
	������WINDOWS_TYPE t��������Ϣ
				u8 x��������Ƭ��ڼ���
				u8 y��������Ƭ�ݵڼ���
				u8 key��  �ⲿ����İ���ֵ
				u8 range�����뷶Χ
				u8 *str�� �������ȡ���ַ�
	����ֵ��������֮��������׵�ַ
*******************************************************************/
void Key_Input_Str(WINDOWS_TYPE t,u8 x,u8 y,u8 key,u8 range,u8 *str)
{
	static u8 Esc_flag=1;
	u8 i=strlen((const char *)str);

	BACK_COLOR = Theme_BACK;
	
	#ifdef Debug_Input
		printf("str:%s\r\ni:%d\r\n",str,i);
	#endif
	
	/*������ȡ����*/
	if(i<range){						//���뷶Χ
		if((key>0&&key<10))		//��������1-9
			str[i++] = key + 0x30;
		if(key==KEY_0)				//��������0
			str[i++] = '0';
		if(key==KEY_X)				//�����ַ�*
			str[i++] = '*';
		if(key==KEY_J)				//�����ַ�#
			str[i++] = '#';
	}
	
	/*�����־λ*/
	if((i==1)&&Clear_flag==0){
		LCD_DrawRecFill(10, 145, 60, 170,Theme_BACK);//���Ч��
	}	
	if(i!=0){
		Clear_flag = 1;
		Display_String(20,150,80,16,"���",16);
	}else{
		Clear_flag = 0;
		Display_String(20,150,80,16,"ȡ��",16);
	}

	/*�������*/
	if(key==KEY_ESC){				//�����
		Esc_flag = 0;
		LCD_DrawRecFill(10, 145, 60, 170,Theme_BACK);//�����Ч��
		LCD_DrawRecFill((t.St_x+y*(t.Weight+t.Jx_x)),												//x1
										(t.St_y+x*(t.Hight+t.Jx_y)), 												//y1
										(t.St_x+y*(t.Weight+t.Jx_x)+t.Weight),							//x2
										(t.St_y+x*(t.Hight+t.Jx_y)+t.Hight),								//y2
										 Theme_SLE);
		if(i!=0)	str[--i] = '\0';									//��Χ���0
		
	}else if(Esc_flag==0){
		Esc_flag = 1;
	}
	
}


/***************************************************************
	�������ܣ���������ʾ�ַ���
	������WINDOWS_INIT_TYPE windows ������Ϣ
				u8 x����ڼ��鴰��
				u8 y���ݵڼ��鴰��
				u8 *show����ʾ���ַ���
				u16 color����ʾ�������ɫ
****************************************************************/
void DispStr_Win(WINDOWS_TYPE t,u8 x,u8 y,u8 *show,u16 color)
{
	BACK_COLOR = color;
	LCD_DrawRecFill((t.St_x+y*(t.Weight+t.Jx_x)),								//x1 
									(t.St_y+x*(t.Hight+t.Jx_y)), 								//y1
									(t.St_x+y*(t.Weight+t.Jx_x)+t.Weight), 			//x2
									(t.St_y+x*(t.Hight+t.Jx_y)+t.Hight),color);	//y2
	Display_String((t.St_x+y*(t.Weight+t.Jx_x)+4),(t.St_y+x*(t.Hight+t.Jx_y)+4),88,16,show,16);					//��ʾ�ַ���
}

/***************************************************************
	�������ܣ����ڳ�ʼ��
	������WINDOWS_INIT_TYPE windows ������Ϣ
****************************************************************/
void Windows_Init(WINDOWS_INIT_TYPE windows)
{
	/*��ʼ��һЩ��ز���*/
	Clear_flag = 0;
	LCD_Clear(Theme_Color);
	BACK_COLOR = Theme_BACK;
	/*��״̬��*/
	LCD_DrawRecFill(0,0,220,20,Theme_BACK);
	Display_String(windows.Location,3,130,16,windows.Name,16);
	/*������1*/
	LCD_DrawRecFill(10, 145, 60, 170,Theme_BACK);
	Display_String(20,150,80,16,windows.Button1,16);
	/*������2*/
	LCD_DrawRecFill(160, 145, 210, 170,Theme_BACK);
	Display_String(170,150,80,16,windows.Button2,16);
}

/************************************************************************
	�������ܣ�������Ƭ��
	������WINDOWS_TYPE t ��������Ϣ�� 
				u8 **show			 ����ʾ��Ƭ�����ݣ�
				u8 i					 ����ڼ���
				u8 j					 ���ݵڼ���
				u16 color			 ����Ƭ��ɫ
*************************************************************************/
void Windows_Title(WINDOWS_TYPE t, u8 **show,u8 i, u8 j,u16 color)
{
	BACK_COLOR = color;
	LCD_DrawRecFill((t.St_x+j*(t.Weight+t.Jx_x)),(t.St_y+i*(t.Hight+t.Jx_y)), 
									(t.St_x+j*(t.Weight+t.Jx_x)+t.Weight), (t.St_y+i*(t.Hight+t.Jx_y)+t.Hight),color);
	Display_String((t.St_x+j*(t.Weight+t.Jx_x)+4),(t.St_y+i*(t.Hight+t.Jx_y)+4),160,16,(u8 *)show[j+i*t.tls_x],16);	
}

/*************************************************************************
	�������ܣ�������Ƭ
	������WINDOWS_TYPE t ��������Ϣ�� 
				u8 **show			 ����ʾ��Ƭ�����ݣ�
				u16 color			 ����Ƭ��ɫ
**************************************************************************/
void Windows_Titles(WINDOWS_TYPE t, u8 **show,u16 color)
{
	u8 i=0,j=0;
	/*��ʾ�˵�*/
	for(i=0;i<t.tls_y;i++){
		for(j=0;j<t.tls_x;j++)
			Windows_Title(t,show,i,j,color);
	}
}

/***************************************************************************
	�������ܣ���Ϣ��ʾ��
	������u8 *Old_flag���ϵĽ����־��
				u8 *New_flag���µĽ����־��
				u8 *Str����ʾ���ݣ�
****************************************************************************/
void Message_Warming_Func(u8 *Old_flag,u8 *New_flag, u8 *Str)
{
	WINDOWS_INIT_TYPE Msg_Win={94,"��ʾ"," ��"," ��"};
	/*���ڳ�ʼ��*/
	Windows_Init(Msg_Win);	
	LCD_DrawRecFill(50, 50, 170, 96,Theme_BACK);
	Display_String(70,60,170,96,Str,16);

	do{
		/*��ȡ���ܼ�ֵ*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null,Old_flag,&Message_Warming_flag,New_flag);
		
	}while(Message_Warming_flag);
	
}

/********************************END****************************************/

