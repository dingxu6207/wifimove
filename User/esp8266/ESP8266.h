#ifndef		__ESP8266_H
#define		__ESP8266_H

#include "stm32f10x.h"
#include "stdio.h"
#include <string.h>  

void ESP8266_Set(unsigned char *puf); // ����ָ��*pufָ���ַ������� 
void SetIP(unsigned char *pReIP);
void SetWifiConnect(void);
void CmdString(unsigned char *ptr);
void SetWifiName(unsigned char *pReName);
void SetNameCode(void);
void SetWifiCode(unsigned char *pReCode);
void ESP8266IO(void);
void ESP8266_Rst( void );


#define Wirst_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define Wirst_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define Wirst_GPIO_PIN		GPIO_Pin_9			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define Wien_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define Wien_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define Wien_GPIO_PIN		GPIO_Pin_8			        /* ���ӵ�SCLʱ���ߵ�GPIO */


#define     macESP8266_RST_HIGH_LEVEL()        GPIO_SetBits ( Wien_GPIO_PORT, Wien_GPIO_PIN )
#define     macESP8266_RST_LOW_LEVEL()         GPIO_ResetBits ( Wien_GPIO_PORT, Wien_GPIO_PIN )

#endif

