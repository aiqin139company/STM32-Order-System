#include "Application.h"

void MMS_Func(void)
{
	WINDOWS_INIT_TYPE MMS_Win={GBLUE,LBBLUE,94,"信息","返回","选择"};
	/*界面初始化*/
	Windows_Init(MMS_Win);	
	
	do{
		/*获取功能键值*/
		Common_Key((short *)&Null,(short *)&Null,Null,Null, &Menu_flag,&MMS_flag,&Null);
		
	}while(MMS_flag);
	
}
