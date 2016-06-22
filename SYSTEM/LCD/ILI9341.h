#ifndef ILI9341_H
#define ILI9341_H		
#include "sys.h"	 
#include "stdlib.h"
#include "math.h"
#include "Delay.h"

/*������Ļ��С*/
#define LCDWIDTH         240
#define LCDHEIGHT        320

/*LCD��Ҫ������*/
typedef struct  
{										    
	u16 width;			//LCD ���
	u16 height;			//LCD �߶�
	u16 id;				  //LCD ID
	u8  dir;			  //���������������ƣ�0��������1��������	
	u8	wramcmd;		//��ʼдgramָ��
	u8  setxcmd;		//����x����ָ��
	u8  setycmd;		//����y����ָ��	 
}_lcd_dev; 	  

/*ɨ�跽����*/
#define L2R_U2D  0 //������,���ϵ���
#define L2R_D2U  1 //������,���µ���
#define R2L_U2D  2 //���ҵ���,���ϵ���
#define R2L_D2U  3 //���ҵ���,���µ���

#define U2D_L2R  4 //���ϵ���,������
#define U2D_R2L  5 //���ϵ���,���ҵ���
#define D2U_L2R  6 //���µ���,������
#define D2U_R2L  7 //���µ���,���ҵ���	 

#define DFT_SCAN_DIR  R2L_D2U  //Ĭ�ϵ�ɨ�跽��

/*TFTLCD������Ҫ���õĺ���*/
extern _lcd_dev LCDDEV;	//����LCD��Ҫ����
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ
extern const unsigned char ASCII_12[95][12];   //ASCII�ַ���
extern const unsigned char ASCII_16[95][16];

/*���廭����ɫ*/
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	   0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //��ɫ
#define BRRED 			     0XFC07 //�غ�ɫ
#define GRAY  			     0X8430 //��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
#define LIGHTGREEN     	 0X841F //ǳ��
#define LGRAY 			     0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

/*LCD��ض˿ڶ���*/
#define  LCD_BL 	  PAout(3)					 //LCD_BL����				PA3
#define  LCD_CS     PCout(9)     		   //Ƭѡ�˿�         PC9
#define  LCD_RS     PCout(8)           //����/����        PC8           
#define  LCD_WR     PCout(7)           //д����           PC7
#define  LCD_RD     PCout(6)           //������           PC6
/*������*/
#define  DATA_OUT()		{GPIOB->CRL = 0x0;GPIOB->CRH = 0x0;GPIOB->CRL = 0x33333333;GPIOB->CRH = 0x33333333;GPIOB->ODR = 0xffff;}
#define  DATA_IN()		{GPIOB->CRL = 0x0;GPIOB->CRH = 0x0;GPIOB->CRL = 0x88888888;GPIOB->CRH = 0x88888888;GPIOB->ODR = 0;}
#define  DataOut(x) 	 GPIOB->ODR = x 	 //�������
#define  DataIn     	 GPIOB->IDR   		 //��������

/*
	д8λ���ݺ����ú궨��,����ٶ�
*/
#define LCD_WR_DATA(data){\
	DATA_OUT();\
	LCD_RS=1;\
	LCD_CS=0;\
	DataOut(data);\
	LCD_WR=0;\
	LCD_WR=1;\
	LCD_CS=1;\
	DATA_IN();\
}							
/*
	д8λ�Ĵ��������ú궨��,����ٶ�
*/
#define LCD_WR_REG(data){\
	DATA_OUT();\
	LCD_RS=0;\
	LCD_CS=0;\
	DataOut(data);\
	LCD_WR=0;\
	LCD_WR=1;\
	LCD_CS=1;\
	DATA_IN();\
}

/*
	��غ�������
*/
void Show_Font(u16 x,u16 y,u8 *dzk,u8 size);    															  
void LCD_Init(void);													   	 //��ʼ��
void LCD_DisplayOn(void);													 //����ʾ
void LCD_DisplayOff(void);													//����ʾ
void LCD_Clear(u16 Color);	 												//����
void LCD_SetCursor(u16 Xpos, u16 Ypos);							//���ù��
void LCD_DrawPoint(u16 x,u16 y);									  //����
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);			//���ٻ���
u16  LCD_ReadPoint(u16 x,u16 y); 										//���� 
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color);								//��Բ
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);							  //����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   			//������
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);		   				//��䵥ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);			//���ָ����ɫ
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);						//��ʾһ���ַ�
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  						//��ʾһ������
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);		//��ʾ ����
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);		//��ʾһ���ַ���,12/16����
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
u16 LCD_ReadReg(u8 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);		  
void LCD_Scan_Dir(u8 dir);							//������ɨ�跽��
void LCD_Display_Dir(u8 dir);						//������Ļ��ʾ����
void LCD_Pic(const unsigned char * p);
//����
//x,y:����
//color:�˵����ɫ
void LCD_DrawPoint_color(u16 x,u16 y,u16 color);

//�Զ���ĺ���
void Draw_Circle_Line(int x,int y,int r,int du,int color);
void Draw_Circles(int x,int y,int r,int q,int color);
void Draw_Circle_Dot(int x,int y,int r,int q,int du,int color);
void LCD_DrawRecFill(u16 x0, u16 y0, u16 x1, u16 y1,u16 color);

#endif
