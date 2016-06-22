#include "Application.h"

static u8 user_input_flag=1,passwd_input_flag=0,pass_flag=0;
u8 *user,*passwd;
/*
	函数功能：获取输入
	返回值：获取到的数据首地址
*/
u8 *Input_Scan(void)
{
	u8 key;
	static u8 i=0,Esc_flag=1,WKUP_flag=1;
	static u8 Input_Data[11]="          ";
	static u8 temp1[11]="          ";			//temp1是user
	static u8 temp2[11]="          ";		  //temp2是passwd
	static u8 i1=0,i2=0;									//i1 是user i2是passwd
	
	key = Key_Scan();
	if(i<10){								//输入范围0-10
		if((key>0&&key<10))		//输入数字1-9
			Input_Data[i++] = key + 0x30;
		if(key==KEY_0)				//输入数字0
			Input_Data[i++] = '0';
		if(key==KEY_X)				//输入字符*
			Input_Data[i++] = '*';
		if(key==KEY_J)				//输入字符#
			Input_Data[i++] = '#';
	}
	if(key==KEY_ESC){				//清除键
		Esc_flag = 0;
		LCD_DrawRecFill(10, 145, 60, 170,BROWN);//清除效果
		if(i!=0)							//范围最低0
			Input_Data[--i] = ' ';
	}else if(Esc_flag==0){
		Esc_flag = 1;
		BACK_COLOR = BROWN;
		Display_String(20,150,80,16,"清除",16);
		BACK_COLOR = GRAY;
	}
	
	
	/*输入切换*/
	if((key==KEY_UP)&&user_input_flag==0){
		BACK_COLOR = BROWN;
		LCD_DrawRecFill(90, 65, 190, 95,GRAY);
		LCD_DrawRecFill(90, 105, 190, 132,BROWN);
		user_input_flag = 1;											//用户输入标志为1
		passwd_input_flag = 0;										//密码输入标志为0
		strcpy((char*)temp2,(char*)Input_Data);		//把密码存到temp2里面
		strcpy((char*)Input_Data,(char*)temp1);		//把用户还原到Input_Data里面
		i2 =i;																		//记录密码输入到第几个
		i = i1;																		//还原用户输入到第几个
		return temp2;			//返回passwd的地址，因为还没变成user，退出之后才变
	}
	if((key==KEY_DOWN)&&passwd_input_flag==0){
		BACK_COLOR = BROWN;
		LCD_DrawRecFill(90, 65, 190, 95,BROWN);
		LCD_DrawRecFill(90, 105, 190, 132,GRAY);
		user_input_flag = 0;											//用户输入标志为0
		passwd_input_flag = 1;										//密码输入标志为1
		strcpy((char*)temp1,(char*)Input_Data);		//把用户存到temp1里面
		strcpy((char*)Input_Data,(char*)temp2);		//把密码还原到Input_Data里面
		i1 = i;																		//记录用户输入到第几个
		i = i2;																		//还原密码输入到第几个
		return temp1;			//返回user的地址，因为还没变成passwd，退出之后才变
	}
	
	
	/*确认输入*/
	if((key==KEY_WKUP)&&WKUP_flag){
		WKUP_flag = 0;
		LCD_DrawRecFill(160, 145, 210, 170,BROWN);
		if(str_cmpx(user,"123456     ", 10)&&str_cmpx(passwd,"123456     ",10)){
			KEY_LED = !KEY_LED;
			pass_flag = 1;
			printf("登陆成功！%s,%d\r\n",__FILE__,__LINE__);
		}
	}else if(WKUP_flag==0){
		WKUP_flag = 1;
		BACK_COLOR = BROWN;
		Display_String(170,150,80,16,"确认",16);
		BACK_COLOR = GRAY;
	}
	
	return Input_Data;			//返回获取到的数据首地址
}

/*
	函数功能：登陆界面
*/
void Login_Func(void)
{
	pass_flag = 0;
	
	LCD_Clear(YELLOW);
	BACK_COLOR = BROWN;
	
	LCD_DrawRecFill(50, 20, 170, 50,BROWN);
	Display_String(77,28,80,16,"用户登陆",16);
	
	LCD_DrawRecFill(20, 65, 80, 95,BROWN);
	Display_String(25,72,80,16,"用户：",16);
	
	LCD_DrawRecFill(20, 105, 80, 132,BROWN);
	Display_String(25,110,80,16,"密码：",16);
	
	LCD_DrawRecFill(90, 65, 190, 95,GRAY);
	Display_String(95,72,80,16,user,16);
	
	LCD_DrawRecFill(90, 105, 190, 132,BROWN);
	Display_String(95,110,80,16,passwd,16);
	
	LCD_DrawRecFill(10, 145, 60, 170,BROWN);
	Display_String(20,150,80,16,"清除",16);
	
	LCD_DrawRecFill(160, 145, 210, 170,BROWN);
	Display_String(170,150,80,16,"确认",16);
	
	do{
		/*输入用户名*/
		if(user_input_flag){
			BACK_COLOR = GRAY;
			user = Input_Scan();
			Display_String(95,72,80,16,user,16);
		}
		/*输入密码*/
		if(passwd_input_flag){
			BACK_COLOR = GRAY;
			passwd = Input_Scan();
			Display_String(95,110,80,16,passwd,16);
		}
	}while(!pass_flag);
	
	LCD_Clear(YELLOW);
	BACK_COLOR = YELLOW;
}

