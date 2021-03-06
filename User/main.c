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
#include <stdlib.h>
#include "bsp_exti.h"
/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
//:FW192.168.**.**#20细分18°
extern bool bFlagRun;
extern bool bRunMotor;
u16 uCmdStep = 0;
int main(void)
{	
    bool bRdeter = false;
	char cStr [ 100 ] = { 0 };
	char cTimeStr [100] = {0};


	u16 SetTime = 10;
	
	/* LED 端口初始化 */
	LED_GPIO_Config();

	ESP8266IO();

	/* 配置SysTick 为1us中断一次 */
	SysTick_Init();

	USART_Config();
	
	WifiUSART_Config();
	
	EXTI_Key_Config();
	
	bFlagRun = true;
	sprintf((char*)CmdUART_RxBuffer, ":FY#");
	
	bRunMotor = true;
								
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
							SetWifiCode(CmdUART_RxBuffer);
						}
							
						else if (CmdUART_RxBuffer[2] == 'Y')
						{
							SetNameCode();
							SetWifiConnect();	

							sprintf((char*)WIFIUART_RxBuffer, "%s", ":F+725#");
						}
							
								
				  	}	
			bFlagRun = false;
			CmdUsart_FlushRxBuffer();
		}

		if (bRunMotor == true)		
		{   
			
			if (WIFIUART_RxBuffer[0] == ':')
				if (WIFIUART_RxBuffer[1] == 'F')
				{				
					if (WIFIUART_RxBuffer[2] == '+')
					{					 
					  //initalMoveR();
						/* 开启电机 */
						GPIO_SetBits(EN_GPIO_PORT, EN_GPIO_PIN);
											
                        uCmdStep = atoi((char const *)WIFIUART_RxBuffer + 3);												
						while(1)
						{
							bRdeter = Movestep(SetTime, uCmdStep);
							if(bRdeter)
								break;
						}
						/* 关闭电机 */
						GPIO_ResetBits(EN_GPIO_PORT, EN_GPIO_PIN);	

						if (ExtiClear == true)
						{
							ExtiClear = false;
							Stepcounter = 0;
						}
						
						sprintf ( cStr, ":FS%d#\n", Stepcounter);
			  		WifiUsart_SendString(USART3, cStr);
						
					}
					else if (WIFIUART_RxBuffer[2] == '-')
					{
						
						//  initalMoveL();
						/* 开启电机 */
						GPIO_SetBits(EN_GPIO_PORT, EN_GPIO_PIN);
																	
						uCmdStep = atoi((char const *)WIFIUART_RxBuffer + 3);								
						while(1)
						{
							bRdeter = MovestepL(SetTime, uCmdStep);
							if(bRdeter)
								break;
						}
                        /* 关闭电机 */
						GPIO_ResetBits(EN_GPIO_PORT, EN_GPIO_PIN);

						if (ExtiClear == true)
						{
							ExtiClear = false;
							Stepcounter = 0;
						}
						
						sprintf ( cStr, ":FS%d#\n", Stepcounter);
			  			WifiUsart_SendString(USART3, cStr);
					}
					else if (WIFIUART_RxBuffer[2] == 'V')
					{
							SetTime = atoi((char const *)WIFIUART_RxBuffer + 3);
						sprintf(cTimeStr, ":FV%d#\n", SetTime);
							WifiUsart_SendString(USART3, cTimeStr);
					}
						
				}
			  
			  Wifiuart_FlushRxBuffer();
			  bRunMotor =false;
			  
		}		
		
		
	}			
	
}


/*********************************************END OF FILE**********************/
