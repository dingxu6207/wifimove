/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ledӦ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./led/bsp_led.h"   
#include "bsp_SysTick.h"
#include "bsp_usart.h"
 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK, ENABLE);
	  RCC_APB2PeriphClockCmd( EN_GPIO_CLK | IN1_GPIO_CLK | IN2_GPIO_CLK, ENABLE);
	
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIOF*/
		GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);

		

		/* ѡ����Ƶ�GPIO���� */
		GPIO_InitStructure.GPIO_Pin = IN1_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIOF*/
		GPIO_Init(IN1_GPIO_PORT, &GPIO_InitStructure);

		/* ѡ����Ƶ�GPIO���� */
		GPIO_InitStructure.GPIO_Pin = IN2_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIOF*/
		GPIO_Init(IN2_GPIO_PORT, &GPIO_InitStructure);

		/* ѡ����Ƶ�GPIO���� */
		GPIO_InitStructure.GPIO_Pin = EN_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIOF*/
		GPIO_Init(EN_GPIO_PORT, &GPIO_InitStructure);

		/* ����ȫ��Ϊ�ߵ�ƽ */
				
		GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);		
		GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);	     
		GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
		
		GPIO_SetBits(IN1_GPIO_PORT, IN1_GPIO_PIN);
		GPIO_SetBits(IN2_GPIO_PORT, IN2_GPIO_PIN);
		GPIO_ResetBits(EN_GPIO_PORT, EN_GPIO_PIN);
}

void assert_failed(uint8_t* file, uint32_t line)
{
	// ���Դ���ʱִ�еĴ���
	LED1_ON;
}
void Movestep(void)
{
	/* ������� */
	GPIO_SetBits(EN_GPIO_PORT, EN_GPIO_PIN);

	/* 00 */
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	Delay_ms(500);

	/* 01 */
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	Delay_ms(500);

	/* 11 */
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	Delay_ms(500);

	/* 10 */
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	Delay_ms(500);

	/* �رյ�� */
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);	
}

void ESP8266_Rst ( void )
{

	 macESP8266_RST_LOW_LEVEL();
	 Delay_ms ( 500 ); 
	 macESP8266_RST_HIGH_LEVEL();


}

/*********************************************END OF FILE**********************/
