#include "bc95_wjl.h"
#include "main.h"
#include "string.h"
#include "led.h"


extern char *strx,*extstrx;
extern char  RxBuffer[100],RxCounter;
extern BC95 BC95_Status;

void Clear_Buffer_wjl(void)//��ջ���
{
//	u8 i;
	Uart1_SendStr(RxBuffer);
//	for(i=0;i<100;i++)
	//RxBuffer[i]=0;
	RxCounter=0;
}

void BC95_Init_wjl(void)
{
	printf("AT+CMEE=1\r\n"); 		//����ATָ��
	Delay(300);
	strx = "";
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
//		printf("AT+CMEE=1\r\n"); 
//		Delay(300);
		strx = "";
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	}
	output_usart1(RxBuffer);
	
	Delay(500);
	
	printf("AT+CFUN=0\r\n"); 		//����ATָ��
	Delay(300);
	strx = "";
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
//		printf("AT+CFUN=0\r\n"); 
//		Delay(300);
		strx = "";
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	}
	output_usart1(RxBuffer);
	
	Delay(500);
	
	printf("AT+CGSN=1\r\n"); 		//����ATָ��
	Delay(300);
	strx = "";
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
//		printf("AT+CGSN=1\r\n"); 
//		Delay(300);
		strx = "";
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	}
	output_usart1(RxBuffer);
	
	Delay(500);
	
	printf("AT+NCDP=180.101.147.115,5683\r\n"); 		//����ATָ��
	Delay(300);
	strx = "";
	strx=strstr((const char*)RxBuffer,(const char*)"N:");//����OK
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
//		printf("AT+NCDP=180.101.147.115,5683\r\n"); 
//		Delay(300);
		strx = "";
		strx=strstr((const char*)RxBuffer,(const char*)"N:");//����OK
	}
	output_usart1(RxBuffer);
	
	Delay(500);
	
	printf("AT+CFUN=1\r\n"); 		//����ATָ��
	Delay(300);
	strx = "";
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	Clear_Buffer();	
	while(strx==NULL || str_contain(strx, "ERROR", strlen(strx), strlen("ERROR")) == 1)
	{
		Clear_Buffer();	
//		printf("AT+CFUN=1\r\n"); 
//		Delay(300);
		strx = "";
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	}
	output_usart1(RxBuffer);
	
	Delay(500);
	
	printf("AT+CGATT=1\r\n"); 		//����ATָ��
	Delay(300);
	strx = "";
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	Clear_Buffer();	
	while(str_contain(strx, "+CEREG:2", strlen(strx), strlen("+CEREG:2")) == 1 || str_contain(strx, "ERROR", strlen(strx), strlen("ERROR")) == 1)
	//while(strcmp(strx, "OK\r\n\r\n+CEREG:2\r\n1106\r\n\r\nOK\r\n") == 0)
	{
		Clear_Buffer();	
//		printf("AT+CGATT=1\r\n"); 
//		Delay(300);
		strx = "";
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	}
	output_usart1(RxBuffer);
	
	Delay(500);
	
	Clear_Buffer();
	printf("AT+NMGS=21,01031001010208000040004000141C0600000068BD"); 		//����ATָ��
	//Delay(300);
	strx = "";
	
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
		
//	while(str_contain(strx, "+CEREG:2", strlen(strx), strlen("+CEREG:2")) == 1 || str_contain(strx, "ERROR", strlen(strx), strlen("ERROR")) == 1)
//	//while(strcmp(strx, "OK\r\n\r\n+CEREG:2\r\n1106\r\n\r\nOK\r\n") == 0)
//	{
//		Clear_Buffer();	
//		printf("AT+NMGS=21,01031001010208000040004000141C0600000068BD"); 
//		Delay(300);
//		strx = "";
//		strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
//	}
	output_usart1("strx:  ");
	output_usart1(RxBuffer);
	
	Delay(500);
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
			return 1;//����������ַ���,����1
	}
	return 0;//���û�����ַ���,����0
}

void send_printRec(char *str_send)
{
	printf("%s", str_send); 		//����ATָ��
	Delay(300);
	strx = "";
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("%s", str_send); 
		Delay(300);
		strx = "";
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	}
	output_usart1(RxBuffer);
}
void send_printRec_2(char *str_send)
{
	printf("%s", str_send); 		//����ATָ��
	Delay(300);
	//strx = "";
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//����ַ������Ƿ���OK,�����,����OK֮����ַ���,��֮���ؿ�
	//Clear_Buffer();	
	while(strstr((const char*)RxBuffer,(const char*)"OK") == NULL || strstr((const char*)RxBuffer,(const char*)"ERROR") != NULL)//û��OK,���ߺ���ERROR�����ѭ��
	{
		//strx=strstr((const char*)RxBuffer,(const char*)"OK");//����ַ������Ƿ���OK,�����,����OK֮����ַ���,��֮���ؿ�
		__nop();
	}
	output_usart1(RxBuffer);
	Clear_Buffer();//��ӡ֮���������
}

void bc95_init_new(void)
{
	send_printRec_2("AT+CMEE=1\r\n");
	Delay(500);
	output_usart1("Step1 Over\r\n");
	send_printRec_2("AT+CFUN=0\r\n");
	Delay(500);
	output_usart1("Step2 Over\r\n");
	send_printRec_2("AT+CGSN=1\r\n");
	Delay(500);
	output_usart1("Step3 Over\r\n");
	send_printRec_2("AT+NCDP=180.101.147.115,5683\r\n");
	Delay(500);
	output_usart1("Step4 Over\r\n");
	send_printRec_2("AT+CFUN=1\r\n");
	//send_printRec_2("AT+NBAND?\r\n");//ò��Ĭ��ֵ����5,����ֱ��ʹ���5
	Delay(1500);//
	output_usart1("Step5 Over\r\n");
	send_printRec_2("AT+CGATT=1\r\n");
	Delay(500);
	output_usart1("Step6 Over\r\n");
//	send_printRec_2("AT+CGPADDR\r\n");
//	output_usart1("Step7 Over\r\n");
//	send_printRec_2("AT+NMGS=21,01031001010208000040004000141C0600000068BD");
//	send_printRec_2("AT+NMGS=21,01031001010208000040004000141C0600000068BD");
//	send_printRec_2("AT+NMGS=21,01031001010208000040004000141C0600000068BD");
}

void BC95_Senddata_wjl(uint8_t len,uint8_t *data)
{
	printf("AT+NMGS=%d,%s\r\n",len,data);//����0 socketIP�Ͷ˿ں������Ӧ���ݳ����Լ�����,727394ACB8221234
	//printf("AT+NSOST=0,120.24.184.124,8010,%c,%s\r\n",'8',"727394ACB8221234");//����0socketIP�Ͷ˿ں������Ӧ���ݳ����Լ�����,
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	while(strx==NULL)
	{
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	}
	
	//��PC���ͳɹ�ָ��
	output_usart1(RxBuffer);
	
	Clear_Buffer();	
	
}




