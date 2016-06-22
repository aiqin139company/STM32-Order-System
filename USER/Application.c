#include "Application.h"

/*******************************************************************
	�������ܣ�ʵʱʱ��
********************************************************************/
void RTC_Func(void)
{
	u8 Date_String[20];				//���DATE����
	u8 Time_String[20];				//���TIME����
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
	if(*i>tls_y-1) *i = 0;
	if(*j>tls_x-1) *j = 0;
	if(*i<0)	 *i = tls_y - 1;
	if(*j<0)	 *j = tls_x - 1;
	
	return key;
}

/******************************************************************
	�������ܣ��������봦��
	������u8 key���ⲿ����İ���ֵ
				u8 range�����뷶Χ
				u8 *Clear_All�������־
	����ֵ��������֮��������׵�ַ
*******************************************************************/
u8 *Key_Input(u8 key, u8 range, u8 *Clear)
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
		LCD_DrawRecFill(10, 145, 60, 170,LBBLUE);//���Ч��
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
		LCD_DrawRecFill(10, 145, 60, 170,LBBLUE);//���Ч��
		if(i!=0)							//��Χ���0
			Input[--i] = ' ';
	}else if(Esc_flag==0){
		Esc_flag = 1;
	}
	
	/*���ȫ������*/
	if(*Clear){
		for(i=0;i<11;i++)
			Input[i] = ' ';
		i=0;
		Esc_flag=1;
		*Clear = 0;
		LCD_DrawRecFill(10, 145, 60, 170,LBBLUE);//���Ч��
	}
	
	#ifdef Debug_Input
	printf("key:%d,i:%d,Clear_flag:%d,*Clear_All:%d,Input_Data:%s\r\n",key,i,Clear_flag,*Clear,Input);
	#endif
	
	return Input;
}


void Key_Input1(u8 x1,u8 y1,u8 x2,u8 y2,u8 key,u8 range,u8 *str)
{
	static u8 Esc_flag=1;
	u8 i=strlen((const char *)str);

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
		LCD_DrawRecFill(10, 145, 60, 170,LBBLUE);//���Ч��
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
		LCD_DrawRecFill(10, 145, 60, 170,LBBLUE);//���Ч��
		LCD_DrawRecFill(x1,y1,x2,y2,CYAN);
		if(i!=0)							//��Χ���0
			str[--i] = '\0';
	}else if(Esc_flag==0){
		Esc_flag = 1;
	}
	
}


/***************************************************************
	�������ܣ����ڳ�ʼ��
	������WINDOWS_INIT_TYPE windows ������Ϣ
****************************************************************/
void Windows_Init(WINDOWS_INIT_TYPE windows)
{
	/*��ʼ��һЩ��ز���*/
	Clear_flag = 0;
	Clear_All = 1;
	LCD_Clear(windows.Clear_Color);
	BACK_COLOR = windows.Back_Color;
	/*��״̬��*/
	LCD_DrawRecFill(0,0,220,20,LBBLUE);
	Display_String(windows.Location,3,130,16,windows.Name,16);
	/*������1*/
	LCD_DrawRecFill(10, 145, 60, 170,LBBLUE);
	Display_String(20,150,80,16,windows.Button1,16);
	/*������2*/
	LCD_DrawRecFill(160, 145, 210, 170,LBBLUE);
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
	WINDOWS_INIT_TYPE Msg_Win={LIGHTBLUE,LBBLUE,94,"��ʾ"," ��"," ��"};
	/*���ڳ�ʼ��*/
	Windows_Init(Msg_Win);	
	LCD_DrawRecFill(50, 50, 170, 96,LBBLUE);
	Display_String(70,60,170,96,Str,16);

	do{
		/*��ȡ���ܼ�ֵ*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null,Old_flag,&Message_Warming_flag,New_flag);
		
	}while(Message_Warming_flag);
	
}


/********************************************************************************/

