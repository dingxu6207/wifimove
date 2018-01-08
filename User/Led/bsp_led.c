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

		/*开启LED相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK, ENABLE);
	  RCC_APB2PeriphClockCmd( EN_GPIO_CLK | IN1_GPIO_CLK | IN2_GPIO_CLK, ENABLE);
	
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);

		

		/* 选择控制的GPIO引脚 */
		GPIO_InitStructure.GPIO_Pin = IN1_GPIO_PIN;

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
				
		GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);		
		GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);	     
		GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
		
		GPIO_SetBits(IN1_GPIO_PORT, IN1_GPIO_PIN);
		GPIO_SetBits(IN2_GPIO_PORT, IN2_GPIO_PIN);
		GPIO_ResetBits(EN_GPIO_PORT, EN_GPIO_PIN);
}

void assert_failed(uint8_t* file, uint32_t line)
{
	// 断言错误时执行的代码
	LED1_ON;
}
void Movestep(void)
{
	/* 开启电机 */
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

	/* 关闭电机 */
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);	
}

void ESP8266_Rst ( void )
{

	 macESP8266_RST_LOW_LEVEL();
	 Delay_ms ( 500 ); 
	 macESP8266_RST_HIGH_LEVEL();


}

/*********************************************END OF FILE**********************/
