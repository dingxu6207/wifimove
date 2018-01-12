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
void SetIP(unsigned char *pReIP);
void CmdString(unsigned char *ptr);
void SetWifiName(unsigned char *pReName);
void SetNameCode(void);


unsigned char ipstr[100] = {0};
unsigned char Cmdstr[100] = "AT+CIPSTART=\"TCP\",\"192.168.43.78\",8080";
void SetIP(unsigned char *pReIP)
{
	pReIP = pReIP + 3;
	sprintf ( (char*)ipstr, "\"%s\",\"%s\",%s", "TCP", pReIP, "8080" );
	sprintf ( (char*)Cmdstr, "AT+CIPSTART=%s", ipstr );
	printf("ip is ok!\n");
}


unsigned char NameStr[100] = "\"A305\"";
void SetWifiName(unsigned char *pReName)
{
	pReName = pReName + 3;
	sprintf((char *)NameStr, "\"%s\"", pReName);
	printf("set wifi name is ok!\n");
}

unsigned char CodeString[100] = "\"wildfired\"";
void SetCode(unsigned char *pReCode)
{
	pReCode = pReCode + 3;
	sprintf((char *)CodeString, "\"%s\"", pReCode);
	printf("set code is ok!\n");
}

unsigned char CmdNameCode[100] = "AT+CWJAP=\"A304\",\"wildfire\"";
void SetNameCode(void)
{
	sprintf((char *)CmdNameCode, "AT+CWJAP=%s,%s", NameStr, CodeString);
}

void SetWifiConnect(void)
{ 

	   ESP8266_Rst();
		 CmdString("AT"); //测试
		 CmdString("AT+RST"); //测试
		
		 CmdString("AT+CWMODE=1");     //设置路由器模式 1 station模式 2 AP	
		 //CmdString("AT+CWJAP=\"A304\",\"wildfire\"");
		 CmdString(CmdNameCode);
		 CmdString("AT+CIPMUX=0");//开启多连接模式，允许多个各客户端接入
		 CmdString(Cmdstr);
		 CmdString("AT+CIPMODE=1");//透传模式	
		 CmdString("AT+CIPSEND");//检测是否连接成功
	   uart_FlushRxBuffer();

}
  
void CmdString(unsigned char *ptr)
{
	int i;		
	for(i = 0; i < 3 ;i++)
	{
			uart_FlushRxBuffer();
			ESP8266_Set(ptr);
			if (strstr((char*)UART_RxBuffer, "OK"))
				break;
	}
}


/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
//:FW192.168.**.**#20细分18°
extern bool bFlagRun;
extern bool bRunMotor;
u8 Stepcounter = 0;
int main(void)
{	

	char cStr [ 100 ] = { 0 };
	int i;
	/* LED 端口初始化 */
	LED_GPIO_Config();

	/* 配置SysTick 为10us中断一次 */
	SysTick_Init();

	USART_Config();
	
	WifiUSART_Config();
	
	//SetWifiConnect();
	bFlagRun = true;
	sprintf((char*)CmdUART_RxBuffer, ":FY#");
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
						else if (CmdUART_RxBuffer[2] == 'A')
						{
							CmdUART_RxBuffer[CmdUART_RxPtr - 1] = '\0';	
							SetWifiName(CmdUART_RxBuffer);
						}
						else if (CmdUART_RxBuffer[2] == 'C')
						{
							CmdUART_RxBuffer[CmdUART_RxPtr - 1] = '\0';	
							SetCode(CmdUART_RxBuffer);
						}
							
						else if (CmdUART_RxBuffer[2] == 'Y')
						{
							SetNameCode();
							SetWifiConnect();	
						}
							
								
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
						for(i = 0; i < 5; i++)
						//Movestep();
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
