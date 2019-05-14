
/*
 * led.c
 */

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h" 
#include "key.h"
#include "system.h"
#include "led.h"
#include "stdio.h"

unsigned char k_up_count = 0;
unsigned char k_down_count = 0;
unsigned char k_left_count = 0;
unsigned char k_right_count = 0;

unsigned char k_up_flag = 0;
unsigned char k_down_flag = 0;
unsigned char k_left_flag = 0;
unsigned char k_right_flag = 0;





/*******************************************************************************
* �� �� ��         : KEY_Init
* ��������		   : ������ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void key_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //����ṹ�����	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;	   //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//��������  
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	   //���ô�������
	GPIO_Init(GPIOA,&GPIO_InitStructure);		  /* ��ʼ��GPIO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//��������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
}

/*******************************************************************************
* �� �� ��         : key_task
* ��������		     : �������� 1ms����һ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void key_task(void)
{
	if( key_scan() == 0) return;    // û�м�����ֱ�ӷ���
	
	if((K_UP == 1) &&(K_DOWN == 1) && (K_RIGHT == 1) && (K_LEFT == 1))
		//K_UP����
	{
		//k_up_count = 0;
		k_down_count = 0;
		k_right_count = 0;
		k_left_count = 0;
		if(k_up_flag == 0)
		{
			if(++k_up_count > 10)
			{
				led_task();
				printf("k_up");
				k_up_flag = 1;
			}
		}
	}
	
	if((K_UP == 0) &&(K_DOWN == 0) && (K_RIGHT == 1) && (K_LEFT == 1))
		//K_DOWN����
	{
		k_up_count = 0;
		//k_down_count = 0;
		k_right_count = 0;
		k_left_count = 0;
		if(k_down_flag == 0)
		{
			if(++k_down_count > 10)
			{
				led_task();
				printf("k_down");
				k_down_flag = 1;
			}
		}
	}
	
	if((K_UP == 0) &&(K_DOWN == 1) && (K_RIGHT == 0) && (K_LEFT == 1))
		//K_RIGHT����
	{
		k_up_count = 0;
		k_down_count = 0;
		//k_right_count = 0;
		k_left_count = 0;
		if(k_right_flag == 0)
		{
			if(++k_right_count > 10)
			{
				led_task();
				printf("k_right");
				k_right_flag = 1;
			}
		}
	}
	
	if((K_UP == 0) &&(K_DOWN == 1) && (K_RIGHT == 1) && (K_LEFT == 0))
		//K_LEFT����
	{
		k_up_count = 0;
		k_down_count = 0;
		k_right_count = 0;
		//k_left_count = 0;
		if(k_left_flag == 0)
		{
			if(++k_left_count > 10)
			{
				led_task();
				printf("k_left");
				k_left_flag = 1;
			}
		}
	}
}

/*******************************************************************************
* �� �� ��         : key_scan
* ��������		     : �������� key_task�����
* ��    ��         : ��
* ��    ��         : �м����·���1�� û�����·���0
*******************************************************************************/

unsigned char key_scan(void)
{
	unsigned char tmp;
	if((K_UP == 0) &&(K_DOWN == 1) && (K_RIGHT == 1) && (K_LEFT == 1))
	{
		k_up_count = 0;
		k_down_count = 0;
		k_right_count = 0;
		k_left_count = 0;
		tmp = 0; //û�а������·���0
	}
	else tmp = 1;  //�м����·���1
	
	if(k_up_flag == 1)  //�ȴ������ͷ�
	{
		if(K_UP == 0)
		{
			k_up_flag = 0;
			k_up_count = 0;
		}
	}
	
	if(k_down_flag == 1)  //�ȴ������ͷ�
	{
		if(K_DOWN == 1)
		{
			k_down_flag = 0;
			k_down_count = 0;
		}
	}
	
	if(k_right_flag == 1)  //�ȴ������ͷ�
	{
		if(K_RIGHT == 1)
		{
			k_right_flag = 0;
			k_right_count = 0;
		}
	}
	
	if(k_left_flag == 1)  //�ȴ������ͷ�
	{
		if(K_LEFT == 1)
		{
			k_left_flag = 0;
			k_left_count = 0;
		}
	}
	
	return tmp;
}



