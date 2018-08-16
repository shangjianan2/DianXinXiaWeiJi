#include "bc95_wjl.h"
#include "main.h"
#include "string.h"
#include "led.h"

extern char *strx,*extstrx;
extern char  RxBuffer[100],RxCounter;
extern BC95 BC95_Status;

void Clear_Buffer_wjl(void)//清空缓存
{
//	u8 i;
	Uart1_SendStr(RxBuffer);
//	for(i=0;i<100;i++)
	//RxBuffer[i]=0;
	RxCounter=0;
}

void BC95_Init_wjl(void)
{
	printf("AT+CMEE=1\r\n"); 		//发送AT指令
	Delay(300);
	strx = "";
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CMEE=1\r\n"); 
		Delay(300);
		strx = "";
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	}
	output_usart1(strx);
	
	printf("AT+CFUN=0\r\n"); 		//发送AT指令
	Delay(300);
	strx = "";
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CFUN=0\r\n"); 
		Delay(300);
		strx = "";
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	}
	output_usart1(strx);
	
	printf("AT+CGSN=1\r\n"); 		//发送AT指令
	Delay(300);
	strx = "";
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CGSN=1\r\n"); 
		Delay(300);
		strx = "";
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	}
	output_usart1(strx);
	
	printf("AT+NCDP=180.101.147.115,5683\r\n"); 		//发送AT指令
	Delay(300);
	strx = "";
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT+NCDP=180.101.147.115,5683\r\n"); 
		Delay(300);
		strx = "";
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	}
	output_usart1(strx);
	
	printf("AT+CFUN=1\r\n"); 		//发送AT指令
	Delay(300);
	strx = "";
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	Clear_Buffer();	
	while(strx==NULL || str_contain(strx, "ERROR", strlen(strx), strlen("ERROR")) == 1)
	{
		Clear_Buffer();	
		printf("AT+CFUN=1\r\n"); 
		Delay(300);
		strx = "";
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	}
	output_usart1(strx);
	
	printf("AT+CGATT=1\r\n"); 		//发送AT指令
	Delay(300);
	strx = "";
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	Clear_Buffer();	
	while(str_contain(strx, "+CEREG:2", strlen(strx), strlen("+CEREG:2")) == 1 || str_contain(strx, "ERROR", strlen(strx), strlen("ERROR")) == 1)
	//while(strcmp(strx, "OK\r\n\r\n+CEREG:2\r\n1106\r\n\r\nOK\r\n") == 0)
	{
		Clear_Buffer();	
		printf("AT+CGATT=1\r\n"); 
		Delay(300);
		strx = "";
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	}
	output_usart1(strx);
	
	printf("AT+NMGS=21,01031001010208000040004000141C0600000068BD"); 		//发送AT指令
	//Delay(300);
	strx = "";
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	Clear_Buffer();	
//	while(str_contain(strx, "+CEREG:2", strlen(strx), strlen("+CEREG:2")) == 1 || str_contain(strx, "ERROR", strlen(strx), strlen("ERROR")) == 1)
//	//while(strcmp(strx, "OK\r\n\r\n+CEREG:2\r\n1106\r\n\r\nOK\r\n") == 0)
//	{
//		Clear_Buffer();	
//		printf("AT+NMGS=21,01031001010208000040004000141C0600000068BD"); 
//		Delay(300);
//		strx = "";
//		strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
//	}
	output_usart1(strx);
}

void output_usart1(char *p_str)
{
	DIR485_1;
	delay_ms(1);
	Uart1_SendStr(p_str);
	delay_ms(1);
	DIR485_0;
}

int str_contain(char *str_1, char *str_2, int size_1, int size_2)
{
	int i = 0;
	for(i = 0; i < size_1; i++)
	{
		int j = 0;
		for(j = 0; j < size_2; j++)
		{
			if(str_1[i + j] != str_2[j])
				break;
		}
		if(j == size_2)
			return 1;//如果含有子字符串,返回1
	}
	return 0;//如果没有子字符串,返回0
}


