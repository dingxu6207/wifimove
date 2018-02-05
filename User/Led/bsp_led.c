/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   led应用函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./led/bsp_led.h"   
#include "bsp_SysTick.h"
#include "bsp_usart.h"



 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{		
	  /*定义一个GPIO_InitTypeDef类型的结构体*/
	  GPIO_InitTypeDef GPIO_InitStructure;
	  
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	 /*开启LED相关的GPIO外设时钟*/		
	  RCC_APB2PeriphClockCmd( EN_GPIO_CLK | IN1_GPIO_CLK | IN2_GPIO_CLK, ENABLE);
		/* 选择控制的GPIO引脚 */
		GPIO_InitStructure.GPIO_Pin = IN1_GPIO_PIN;

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(IN1_GPIO_PORT, &GPIO_InitStructure);

		/* 选择控制的GPIO引脚 */
		GPIO_InitStructure.GPIO_Pin = IN2_GPIO_PIN;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(IN2_GPIO_PORT, &GPIO_InitStructure);

		/* 选择控制的GPIO引脚 */
		GPIO_InitStructure.GPIO_Pin = EN_GPIO_PIN;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(EN_GPIO_PORT, &GPIO_InitStructure);

		/* 设置全部为高电平 */		
		GPIO_SetBits(IN1_GPIO_PORT, IN1_GPIO_PIN);
		GPIO_SetBits(IN2_GPIO_PORT, IN2_GPIO_PIN);
		GPIO_ResetBits(EN_GPIO_PORT, EN_GPIO_PIN);
}

void assert_failed(uint8_t* file, uint32_t line)
{
	// 断言错误时执行的代码
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
//反转
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
	/* 关闭电机 */
	GPIO_ResetBits(EN_GPIO_PORT, EN_GPIO_PIN);	
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);

	Delay_ms(200);
}

void initalMoveL(void)
{
	/* 关闭电机 */
	GPIO_ResetBits(EN_GPIO_PORT, EN_GPIO_PIN);	
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);	
	Delay_ms(200);
}

/*********************************************END OF FILE**********************/
