#include "SYS.h"

/*
	�жϷ��鶨��
*/
#define NVIC_PriorityGroup0  7-0    // ��ռ���ȼ� 0 λ �����ȼ� 4 λ
#define NVIC_PriorityGroup1  7-1    // ��ռ���ȼ� 1 λ �����ȼ� 3 λ
#define NVIC_PriorityGroup2  7-2    // ��ռ���ȼ� 2 λ �����ȼ� 2 λ
#define NVIC_PriorityGroup3  7-3    // ��ռ���ȼ� 3 λ �����ȼ� 1 λ
#define NVIC_PriorityGroup4  7-4    // ��ռ���ȼ� 4 λ �����ȼ� 0 λ
#define NVIC_PriorityGroup		NVIC_PriorityGroup2		//ʵ�ʷ��鶨��

/*
	�������ܣ���ʼ���ж����ȼ��ͷ���
	������
		EXTIx_IRQn ���ж���
		PreemptPriority����ռ���ȼ�
		SubPriority�������ȼ�
		
	�����÷���Set_NVIC (�ж���,��ռ���ȼ�,�����ȼ�);				
		
*/
void Set_NVIC(IRQn_Type EXTIx_IRQn, u32 PreemptPriority, u32 SubPriority)
{
	u32 Priority;	//���ȼ����
	
	/*NVIC������غ���----*/
  NVIC_SetPriorityGrouping(NVIC_PriorityGroup);									//���÷���
  Priority = NVIC_EncodePriority (NVIC_PriorityGroup, PreemptPriority, SubPriority);			//�������ȼ���� 
 	NVIC_SetPriority(EXTIx_IRQn,Priority); 					//����EXTIx�ж����ȼ�	Pxx
  NVIC_EnableIRQ(EXTIx_IRQn);               			//ʹ��EXTIx��Ӧ�ж���	Pxx
}
