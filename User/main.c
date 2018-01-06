#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "WifiUsart.h"
#include "ESP8266.h"
#include "stdio.h"
/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	
	int i;
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();

	/* ����SysTick Ϊ10us�ж�һ�� */
	SysTick_Init();

	USART_Config();
	
	WifiUSART_Config();
	
	//printf("it is ok!\n");
	for(i = 0; i < 3 ;i++)
	ESP8266_Set("AT"); //����·����ģʽ 1 stationģʽ 2 AP
 
	for(i = 0; i < 3 ;i++)
	ESP8266_Set("AT+CWMODE=1");     //��������wifiģ��
  
	for(i = 0; i < 5;i++)
	ESP8266_Set("AT+CWJAP=\"A304\",\"wildfire\"");

	for(i = 0; i < 3 ;i++)
	ESP8266_Set("AT+CIPMUX=0");//����������ģʽ�����������ͻ��˽���
	
	for(i = 0; i < 5 ;i++)
	ESP8266_Set("AT+CIPSTART=\"TCP\",\"192.168.43.78\",8080");  //����TCP/IP �˿�Ϊ8080 ʵ�ֻ�������//����
  
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
