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
	  
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	 /*����LED��ص�GPIO����ʱ��*/		
	  RCC_APB2PeriphClockCmd( EN_GPIO_CLK | IN1_GPIO_CLK | IN2_GPIO_CLK, ENABLE);
		/* ѡ����Ƶ�GPIO���� */
		GPIO_InitStructure.GPIO_Pin = IN1_GPIO_PIN;

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

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
		GPIO_SetBits(IN1_GPIO_PORT, IN1_GPIO_PIN);
		GPIO_SetBits(IN2_GPIO_PORT, IN2_GPIO_PIN);
		GPIO_ResetBits(EN_GPIO_PORT, EN_GPIO_PIN);
}

void assert_failed(uint8_t* file, uint32_t line)
{
	// ���Դ���ʱִ�еĴ���
	LED1_ON;
}


bool DetermineBreak(u16 uDReCmdStep)
{
    bool bturn = false;
	
    
	if (Stepcounter >= uDReCmdStep)
	{
		
		bturn = true;
	}		
	else
	{
	    Stepcounter++;
		bturn = false;
	}	
	return bturn;
		
}

u16 Stepcounter = 0;
bool Movestep(uc16 TimeMs, u16 uReCmdStep)
{
    bool bBreakCount = false;
	/* 00 */
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	Delay_ms(TimeMs);
	
	if (DetermineBreak(uReCmdStep))
	{
		bBreakCount = true;
		return bBreakCount;
	}
		
    
	/* 01 */
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	Delay_ms(TimeMs);
	if (DetermineBreak(uReCmdStep))
	{
		bBreakCount = true;
		return bBreakCount;
	}

	/* 11 */
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	Delay_ms(TimeMs);
	if (DetermineBreak(uReCmdStep))
	{
		bBreakCount = true;
		return bBreakCount;
	}

	/* 10 */
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	Delay_ms(TimeMs);
	if (DetermineBreak(uReCmdStep))
	{
		bBreakCount = true;
		return bBreakCount;
	}

	
	return bBreakCount;
}

bool DetermineBreakL(u16 uDReCmdStep)
{
    bool bturn = false;
	
    
	if (Stepcounter <= uDReCmdStep)
	{
		
		bturn = true;
	}		
	else
	{
	    Stepcounter--;
		bturn = false;
	}	
	return bturn;
		
}

//-------------------------------------------
//��ת
bool MovestepL(uc16 TimeMs, u16 uReCmdStep)
{
	bool bBreakCount = false;
		
	/* 10 */
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	Delay_ms(TimeMs);
	if (DetermineBreakL(uReCmdStep))
	{
		bBreakCount = true;
		return bBreakCount;
	}

	/* 11 */
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	Delay_ms(TimeMs);
	if (DetermineBreakL(uReCmdStep))
	{
		bBreakCount = true;
		return bBreakCount;
	}

    /* 01 */
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	Delay_ms(TimeMs);
	if (DetermineBreakL(uReCmdStep))
	{
		bBreakCount = true;
		return bBreakCount;
	}

	/* 00 */
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	Delay_ms(TimeMs);
	
	if (DetermineBreakL(uReCmdStep))
	{
		bBreakCount = true;
		return bBreakCount;
	}
		
	return bBreakCount;
}

void initalMoveR(void)
{
	/* �رյ�� */
	GPIO_ResetBits(EN_GPIO_PORT, EN_GPIO_PIN);	
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);

	Delay_ms(200);
}

void initalMoveL(void)
{
	/* �رյ�� */
	GPIO_ResetBits(EN_GPIO_PORT, EN_GPIO_PIN);	
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);	
	Delay_ms(200);
}

/*********************************************END OF FILE**********************/
