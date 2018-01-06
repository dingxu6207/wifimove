#include "ESP8266.h"
#include "WifiUsart.h"
#include "bsp_SysTick.h"
#include "bsp_usart.h"

void ESP8266_Set(unsigned char *puf) // 数组指针*puf指向字符串数组  
{
	#if 0
	WifiUsart_SendString(USART3, puf);
	Usart_SendString(USART1, puf);
	Delay_us(5);

	WifiUsart_SendByte(USART3, '\r');
	Usart_SendByte(USART1, '\r');
    Delay_us(5);
	
	WifiUsart_SendByte(USART3, '\n');
	Usart_SendByte(USART1, '\n');
    Delay_ms(1000);	
	#endif

	  while(*puf!='\0')    //遇到空格跳出循环
      {
           WifiUsart_SendByte(USART3, *puf);
		   Usart_SendByte(USART1, *puf);
           Delay_us(5);
           puf++;      
      }
      Delay_us(5);
     
      WifiUsart_SendByte(USART3, '\r');
			Usart_SendByte(USART1, '\r');
      Delay_us(5);
      
			WifiUsart_SendByte(USART3, '\n');
      Usart_SendByte(USART1, '\n');
      Delay_ms(1000);
}



