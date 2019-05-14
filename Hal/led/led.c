
/*
 * led.c
 */

#include"stm32f10x_gpio.h"
#include"stm32f10x_rcc.h" 
#include"led.h"
//#include "system.h"
//GPIOC0 -GPIOC7�ֱ���8��LED�Ŀ��ƿڣ� 
void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);         //����GPIOC��ʱ������
	
	GPIO_InitStructure.GPIO_Pin=(GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
														 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);  //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOC,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	
	GPIO_SetBits(GPIOC,(GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
														 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7));   //��LED�˿����ߣ�Ϩ������LED
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
}

void led_task(void)
{
	static unsigned char tmp;
	if(tmp == 1)
	{
		led0_on();
		tmp = 0;
	}
	else
	{
		led0_off();
		tmp = 1;
	}
}

void led0_on(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
}

void led0_off(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_0);
}

