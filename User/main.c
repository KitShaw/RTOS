
#include "stm32f10x.h"
#include "misc.h"
#include "led.h"
#include "usart.h"
#include "stdio.h"
#include "key.h"

unsigned char task_1ms_flag;
unsigned char task_1ms_count;
unsigned char task_10ms_flag;
unsigned char task_10ms_count;
unsigned char task_1s_flag;
unsigned char task_1s_count;

void task_1ms(void)
{
	task_1ms_flag = 0;
	if(++task_10ms_count >=10) {task_10ms_count = 0; task_10ms_flag = 1;}
	key_task(); 
}

void task_10ms(void)
{
	task_10ms_flag = 0;
	if(++task_1s_count >=100) {task_1s_count = 0; task_1s_flag = 1;}
	
}
void task_1s(void)
{
	task_1s_flag = 0;
	printf("Hello STM32!\n");
}

void systick_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);   //ϵͳʱ�ӵ�8��Ƶ��ΪSystick��ʱ��Դ
	SysTick_Config(9000);  //
}


int main(void)
{
//	unsigned char a;
//	int i;
	systick_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	led_init();
	key_init();
	USART1_init(9600);
	while(1)
	{
		if(task_1ms_flag == 1) task_1ms();
		if(task_10ms_flag == 1) task_10ms();
		if(task_1s_flag == 1) task_1s();
	}
}


void SysTick_Handler(void)
	//
{
	if(++task_1ms_count >= 8)
	{
		task_1ms_count = 0;
		task_1ms_flag = 1;
	}
}
