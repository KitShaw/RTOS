/******************** (C) COPYRIGHT 2013 VeryAI Team **************************
 * ����    ��VeryAI Team
 * ��汾  ��ST3.5.0
 * ʵ��ƽ̨��VeryAI STM32������
 * ����    ����ʱ����  
 *
 * ��̳    ��http://www.veryai.com
 * �Ա�    ��http://veryaishop.taobao.com
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "delay.h"
#include "system.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
//#if SYSTEM_SUPPORT_UCOS
//#include "includes.h"				//ucos ʹ��	  
//#endif

#include "FreeRTOS.h"
#include "task.h"
#include "list.h"
 
static u8  fac_us=0;				//us��ʱ������
static u16 fac_ms=0;				//ms��ʱ������

//#ifdef OS_CRITICAL_METHOD 	//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
/*
 * ��������SysTick_Handler
 * ����  ��systick�жϷ�����,ʹ��ucosʱ�õ�
 * ����  ����
 * ���  ����
 */	
extern void xPortSysTickHandler(void);
void SysTick_Handler(void)
{				   
	if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) //ϵͳ�Ѿ�����
	{
		xPortSysTickHandler();
	}
}
//#endif

/*
 * ��������delay_init
 * ����  ����ʼ���ӳٺ�������ʹ��ucos��ʱ��,�˺������ʼ��ucos��ʱ�ӽ���
					 SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8�SYSCLK:ϵͳʱ��
 * ����  ����
 * ���  ����
 */	
void delay_init()	 
{
	u32 reload;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	//ѡ���ⲿʱ,SysTick_CLKSource_HCLK_Div8,SysTick_CLKSource_HCLK
	fac_us=SystemCoreClock/1000000;//Ϊϵͳʱ�ӵ�1/8 
	
	reload=SystemCoreClock/8000000;//ÿ���ӵļ������� ��λΪK	   
	reload*=1000000/configTICK_RATE_HZ;//����configTICK_RATE_HZ�趨���ʱ��,
	                                  //reloadΪ24λ�Ĵ���,���ֵ:16777216,��72M��,Լ��1.86s����	
	fac_ms=1000/configTICK_RATE_HZ;//����os������ʱ�����ٵ�λ  
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;//����SYSTICK�ж�
	SysTick->LOAD=reload; 		//ÿ1/OS_TICKS_PER_SEC���ж�һ��	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//����SYSTICK    
}								    
/*
 * ��������delay_us
 * ����  : us��ʱ����.
 * ����  ��nusΪҪ��ʱ��us��.
 * ���  ����
 */	
void delay_us(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;	//LOAD��ֵ	    	 
	ticks=nus*fac_us; 				//��Ҫ�Ľ�����	  		 
	tcnt=0;
	told=SysTick->VAL;        //�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;	//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}  
	}; 									    
}

/*
 * ��������delay_ms
 * ����  ��ms��ʱ����
 * ����  ��nms:Ҫ��ʱ��ms��
 * ���  ����
 */	
void delay_ms(u16 nms)
{	
	if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)				//���os�Ѿ�������	    
	{		  
		if(nms>=fac_ms)					//��ʱ��ʱ�����ucos������ʱ������ 
		{
			vTaskDelay(nms/fac_ms);//ucos��ʱ
		}
		nms%=fac_ms;						//ucos�Ѿ��޷��ṩ��ôС����ʱ��,������ͨ��ʽ��ʱ    
	}
	delay_us((u32)(nms*1000));//��ͨ��ʽ��ʱ,��ʱucos�޷���������.
}

/*
 * ��������delay_ms
 * ����  ��ms��ʱ����, ���������������
 * ����  ��nms:Ҫ��ʱ��ms��
 * ���  ����
 */	

void delay_xms(u16 nms)
{
	u32 i;
	for(i = 0; i<nms; i++) delay_us(1000);
}



































