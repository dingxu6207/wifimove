#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "WifiUsart.h"
#include "ESP8266.h"
#include "stdio.h"
/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{	
	int i;
	/* LED 端口初始化 */
	LED_GPIO_Config();

	/* 配置SysTick 为10us中断一次 */
	SysTick_Init();

	USART_Config();
	
	WifiUSART_Config();
	
	//printf("it is ok!\n");
	for(i = 0; i < 3 ;i++)
	ESP8266_Set("AT"); //设置路由器模式 1 station模式 2 AP
 
	for(i = 0; i < 3 ;i++)
	ESP8266_Set("AT+CWMODE=1");     //重新启动wifi模块
  
	for(i = 0; i < 5;i++)
	ESP8266_Set("AT+CWJAP=\"A304\",\"wildfire\"");

	for(i = 0; i < 3 ;i++)
	ESP8266_Set("AT+CIPMUX=0");//开启多连接模式，允许多个各客户端接入
	
	for(i = 0; i < 5 ;i++)
	ESP8266_Set("AT+CIPSTART=\"TCP\",\"192.168.43.78\",8080");  //启动TCP/IP 端口为8080 实现基于网络//控制
  
	for(i = 0; i < 5 ;i++)
  ESP8266_Set("AT+CIPMODE=1");//AT+CIPSEND

	for(i = 0; i < 3 ;i++)
	ESP8266_Set("AT+CIPSEND");
	
	while(1)
	{
		Delay_ms(1000);
		printf("%s\n", UART_RxBuffer);
		
		Delay_ms(1000);
		//uart_FlushRxBuffer();
	}	
	
}


/*********************************************END OF FILE**********************/
