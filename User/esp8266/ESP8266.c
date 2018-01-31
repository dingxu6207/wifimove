#include "ESP8266.h"
#include "WifiUsart.h"
#include "bsp_SysTick.h"
#include "bsp_usart.h"
#include "bsp_led.h"


void ESP8266_Set(unsigned char *puf) // ����ָ��*pufָ���ַ�������  
{
	
	  while(*puf!='\0')    //�����ո�����ѭ��
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
      Delay_ms(2000);
}


unsigned char ipstr[100] = {0};
unsigned char Cmdstr[100] = "AT+CIPSTART=\"TCP\",\"192.168.1.3\",8080";
void SetIP(unsigned char *pReIP)
{
	pReIP = pReIP + 3;
	sprintf ( (char*)ipstr, "\"%s\",\"%s\",%s", "TCP", pReIP, "8080" );
	sprintf ( (char*)Cmdstr, "AT+CIPSTART=%s", ipstr );
	printf("ip %s is ok!\n", ipstr);
}

unsigned char NameStr[100] = "\"dx405\"";
void SetWifiName(unsigned char *pReName)
{
	pReName = pReName + 3;
	sprintf((char *)NameStr, "\"%s\"", pReName);
	printf("set wifi name %s is ok!\n", pReName);
}

unsigned char CodeString[100] = "\"xingdu405\"";
void SetWifiCode(unsigned char *pReCode)
{
	pReCode = pReCode + 3;
	sprintf((char *)CodeString, "\"%s\"", pReCode);
	printf("set code %s is ok!\n", CodeString);
}

unsigned char CmdNameCode[100] = "AT+CWJAP=\"dx405\",\"xingdu405\"";
void SetNameCode(void)
{
	sprintf((char *)CmdNameCode, "AT+CWJAP=%s,%s", NameStr, CodeString);
}

void SetWifiConnect(void)
{ 

	   ESP8266_Rst();
		 CmdString("AT"); //����
		 CmdString("AT+RST"); //����
		
		 CmdString("AT+CWMODE=1");     //����·����ģʽ 1 stationģʽ 2 AP	
		 //CmdString("AT+CWJAP=\"A304\",\"wildfire\"");
		 CmdString(CmdNameCode);
		 CmdString("AT+CIPMUX=0");//����������ģʽ�����������ͻ��˽���
		 CmdString(Cmdstr);
		 CmdString("AT+CIPMODE=1");//͸��ģʽ	
		 CmdString("AT+CIPSEND");//����Ƿ����ӳɹ�
	   Wifiuart_FlushRxBuffer();

}
  
void CmdString(unsigned char *ptr)
{
	int i;		
	for(i = 0; i < 3 ;i++)
	{
			Wifiuart_FlushRxBuffer();
			ESP8266_Set(ptr);
			if (strstr((char*)WIFIUART_RxBuffer, "OK"))
				break;
	}
}

void ESP8266IO(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	  
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
     GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

     /*����LED��ص�GPIO����ʱ��*/
	 RCC_APB2PeriphClockCmd( Wirst_GPIO_CLK | Wien_GPIO_CLK, ENABLE);

     /*ѡ��Ҫ���Ƶ�GPIO����*/
	 GPIO_InitStructure.GPIO_Pin = Wirst_GPIO_PIN;	

	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*���ÿ⺯������ʼ��GPIO*/
	GPIO_Init(Wirst_GPIO_PORT, &GPIO_InitStructure);	
		
	/*ѡ��Ҫ���Ƶ�GPIO����*/
	GPIO_InitStructure.GPIO_Pin = Wien_GPIO_PIN;

	/*���ÿ⺯������ʼ��GPIO*/
	GPIO_Init(Wien_GPIO_PORT, &GPIO_InitStructure);	

  GPIO_SetBits(Wirst_GPIO_PORT, Wirst_GPIO_PIN);		
	GPIO_SetBits(Wien_GPIO_PORT, Wien_GPIO_PIN);	
}


void ESP8266_Rst( void )
{
   
		macESP8266_RST_LOW_LEVEL();
		Delay_ms ( 500 ); 
		macESP8266_RST_HIGH_LEVEL();
		
}

