#include "Font.h"

Font_Info Font_Addr;  //�ֿ��ַ��Žṹ��

/*
	�������ܣ������ֿ��ʼ��
*/
void Font_Init(void) 
{
	Font_Addr.F16Addr=0;  //16*16�ֿ���ʼ��ַ����
//	Font_Addr.F24Addr=1;	//û����д24*24���ֿ���������
}

/*
	�������ܣ���FlashоƬ�����ȡ���ֵ�����
	������u8 *code ���֣�
				u8 *buff �洢���ֵ�����ռ��׵�ַ
				u8 size  �������� 16*16 ���� 24*24
*/
void Get_Font_Data(u8 *HZ,u8 *buff,u8 size)
{
	u32 Addr_Offset;
	u8 Csize;
	
	Csize = (size/8+((size%8)?1:0))*(size);						//������Ҫȡ�����ֽڵ�����
	Addr_Offset = ((HZ[0]-0xa1)*94+(HZ[1]-0xa1))*32;	//����ƫ�Ƶ�ַ
	
	switch(size){																			//��ȡ������
		case 16:FLASH_Serial_Read_Data(Addr_Offset+Font_Addr.F16Addr,Csize,buff);break;
		case 24:FLASH_Serial_Read_Data(Addr_Offset+Font_Addr.F24Addr,Csize,buff);break;
	}
}

/*
	�������ܣ���ʾһ�������ַ�
	������u16 x			��ʾ�ĺ�����
				u16 y		 	��ʾ��������
				u8 *font 	��ʾ�ĺ���
				u8 size		��ʾ�������С
*/
void Display_HZ(u16 x,u16 y,u8 *font,u8 size)
{
	u8 i,j,k=0;
	u16 y0 = y;
	u8 HZ[200];										//��������ַ�������
	
	Get_Font_Data(font,HZ,size);	//��flashоƬ�����ȡ�ַ�������
	
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){		//��ʾ����һ�е��ֽ�
			if(HZ[k]&0x80)	
				LCD_DrawPoint(x,y);//�����1�Ļ���ʾ
			else 						
				LCD_DrawPoint_color(x,y,BACK_COLOR);
			y ++;									//y��������1
			HZ[k] <<= 1;					//�Ѵθ�λ������λ
			if((j+1)%8==0) k++;		//�����ʾ��һ���ֽڣ���ʾ��һ���ֽ�
		}
		x ++;										//��ʾ��һ�У�x��ַ����1
		y = y0;									//y������ָ���ԭʼ����
	}					
	
}


/*
	�������ܣ���ʾ�����ַ���
	������u16 x			��ʾ�ĺ�����
				u16 y		 	��ʾ��������
				u16 width ��ʾ�Ŀ��
				u16 height��ʾ�ĸ߶�
				u8 *str 	��ʾ�ĺ����ַ���
				u8 size		��ʾ�������С
*/
void Display_String(u16 x,u16 y,u16 width,u16 height,u8 *str,u8 size)
{					
	u16 x0=x;
	u16 y0=y;							  	      				    				  	  
	while(*str!=0){  									//����δ����
		if(*str>0x80){ 									//�ж��Ƿ��Ǻ���
			if(x>(x0+width-size)){				//���� 
				y += size;
				x = x0;		  
			}
			if(y>(y0+height-size))break; 	//Խ�緵��  	
				
			Display_HZ(x,y,str,size); 	//��ʾ�������
			str += 2;   									//�����������ֽ�
			x += size;  									//��һ������ƫ��	
		}else{  												//��ʾӢ���ַ�
			if(x>(x0+width-size/2)){			//����			   
				y += size;
				x = x0;	   
			}							    
			if(y>(y0+height-size))
				break;      								//Խ�緵��   
			else 
				LCD_ShowChar(x,y,*str,size,0);//��Ч����д�� 
			str ++;     									//ָ���1---Ӣ���ַ�
			x += size/2; 									//�ַ��Ǻ��ֵ�һ�� 
		}				 
	}   
} 

