#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "WifiUsart.h"
#include "ESP8266.h"
#include "stdio.h"
#include <string.h>  
#include <stdbool.h>
#include "stm32f10x_it.h"


void SetWifiConnect(void);
void SetIP(char *pReIP);

char ipstr[100] = {0};
char Cmdstr[100] = "AT+CIPSTART=\"TCP\",\"192.168.43.78\",8080";
void SetIP(char *pReIP)
{
	pReIP = pReIP + 3;
	sprintf ( ipstr, "\"%s\",\"%s\",%s", "TCP", pReIP, "8080" );
	sprintf ( Cmdstr, "AT+CIPSTART=%s", ipstr );
	printf("ip is ok!\n");
}

void SetWifiConnect(void)
{ 	int i;

	ESP8266_Rst();
	
	for(i = 0; i < 3 ;i++)
	ESP8266_Set("AT+RST"); //����
 
	for(i = 0; i < 3 ;i++)
	ESP8266_Set("AT+CWMODE=1");     //����·����ģʽ 1 stationģʽ 2 AP
  
	for(i = 0; i < 5;i++)
	ESP8266_Set("AT+CWJAP=\"A304\",\"wildfire\"");

	for(i = 0; i < 3 ;i++)
	ESP8266_Set("AT+CIPMUX=0");//����������ģʽ�����������ͻ��˽���
	
	for(i = 0; i < 5 ;i++)
	//ESP8266_Set("AT+CIPSTART=\"TCP\",\"192.168.43.78\",8080");  //����TCP/IP �˿�Ϊ8080 ʵ�ֻ�������//����
	ESP8266_Set(Cmdstr);
	
	for(i = 0; i < 3 ;i++)
  	ESP8266_Set("AT+CIPMODE=1");//͸��ģʽ

	for(i = 0; i < 3 ;i++)
	ESP8266_Set("AT+CIPSEND");//����Ƿ����ӳɹ�
  
	Delay_ms(1000);
	if (strstr(UART_RxBuffer, "OK"))
	{
		  uart_FlushRxBuffer();
		  printf("set wifi is ok!\n");
	}
}


/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
//:FW192.168.**.**#
extern bool bFlagRun;
extern bool bRunMotor;
u8 Stepcounter = 0;
int main(void)
{	

	char cStr [ 100 ] = { 0 };
	int i;
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();

	/* ����SysTick Ϊ10us�ж�һ�� */
	SysTick_Init();

	USART_Config();
	
	WifiUSART_Config();
	
	//SetWifiConnect();
	bFlagRun = true;
	sprintf(CmdUART_RxBuffer, ":FY#");
	while(1)
	{		
		if (bFlagRun == true)
		{
			if (CmdUART_RxBuffer[0] == ':')
				  if (CmdUART_RxBuffer[1] == 'F')
				  	{
						if (CmdUART_RxBuffer[2] == 'W')
						{
							CmdUART_RxBuffer[CmdUART_RxPtr - 1] = '\0';							
							SetIP(CmdUART_RxBuffer);
						}
						else if (CmdUART_RxBuffer[2] == 'Y')
							SetWifiConnect();	
				  	}	
			bFlagRun = false;
			CmdUsart_FlushRxBuffer();
		}

		if (bRunMotor == true)		
		{   
			if (UART_RxBuffer[0] == ':')
				if (UART_RxBuffer[1] == 'F')
				{
					if (UART_RxBuffer[2] == '+')
					{
						for(i = 0; i < 2600; i++)
						Movestep();
						Stepcounter++;
						sprintf ( cStr, "Moving %d is ok!\n", Stepcounter);
			  			WifiUsart_SendString(USART3, cStr);
					}
					else if(UART_RxBuffer[2] == 'Q')
						GPIO_ResetBits(GPIOA, GPIO_Pin_4);					
				}
			  
			  uart_FlushRxBuffer();
			  bRunMotor =false;
			  
		}		
		
		
	}			
	
}


/*********************************************END OF FILE**********************/
