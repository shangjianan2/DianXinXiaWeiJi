  ///AT+NSOCL=0
#include "bc95.h"
#include "main.h"
#include "string.h"
#include "led.h"

char *strx,*extstrx;
extern char  RxBuffer[100],RxCounter;
BC95 BC95_Status;

void delay_ms(u16 z)  //?????
{
	u16 x,y;
	for(x=z;x>0;x--)
	for(y=110;y>0;y--);
}

void Clear_Buffer(void)//��ջ���
{
//	u8 i;
	Uart1_SendStr(RxBuffer);
//	for(i=0;i<100;i++)
	//RxBuffer[i]=0;
	RxCounter=0;
}
void BC95_Init(void)
{
	printf("AT\r\n"); 		//����ATָ��
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT\r\n"); 
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	}
	
	printf("AT+CMEE=1\r\n"); //�������ֵ
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	Clear_Buffer();	

	printf("AT+NBAND?\r\n");//��ȡƵ�κ�
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"+NBAND:5");//����5  ����
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT+NBAND?\r\n");//��ȡƵ�κ�
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"+NBAND:5");//����OK
	}

	printf("AT+CIMI\r\n");//��ȡ���ţ������Ƿ���ڿ�����˼���Ƚ���Ҫ��
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"46011");//��46011
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CIMI\r\n");//��ȡ���ţ������Ƿ���ڿ�����˼���Ƚ���Ҫ��
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"46011");//����OK,˵�����Ǵ��ڵ�
	}

	printf("AT+CGATT=1\r\n");//�������磬PDP
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//��46011
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CGATT=1\r\n");//��ȡ���ţ������Ƿ���ڿ�����˼���Ƚ���Ҫ��
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK,˵�����Ǵ��ڵ�
	}
	
	printf("AT+CGATT?\r\n");//�������磬PDP
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"+CGATT:1");//��1
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CGATT?\r\n");//��ȡ����״̬
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"+CGATT:1");//����1,����ע���ɹ�
	}

	printf("AT+CSQ\r\n");//�鿴��ȡCSQֵ
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"+CSQ");//����CSQ
	if(strx)
	{
		BC95_Status.CSQ=(strx[5]-0x30)*10+(strx[6]-0x30);//��ȡCSQ
		if(BC95_Status.CSQ==99)//˵��ɨ��ʧ��
		{
			while(1)
			{
				Uart1_SendStr("�ź�����ʧ�ܣ���鿴ԭ��!\r\n");
				Delay(300);
			}
		}
	}
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CSQ\r\n");//�鿴��ȡCSQֵ
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"+CSQ");//
		if(strx)
		{
			BC95_Status.CSQ=(strx[5]-0x30)*10+(strx[6]-0x30);//��ȡCSQ
			if(BC95_Status.CSQ==99)//˵��ɨ��ʧ��
			{
				while(1)
				{
					Uart1_SendStr("�ź�����ʧ�ܣ���鿴ԭ��!\r\n");
					Delay(300);
				}
			}
		}
	}
	Clear_Buffer();	

	printf("AT+CEREG?\r\n");
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"+CEREG:0,1");//����ע��״̬
	extstrx=strstr((const char*)RxBuffer,(const char*)"+CEREG:1,1");//����ע��״̬
	Clear_Buffer();	
	while(strx==NULL&&extstrx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CEREG?\r\n");//�ж���Ӫ��
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"+CEREG:0,1");//����ע��״̬
		extstrx=strstr((const char*)RxBuffer,(const char*)"+CEREG:1,1");//����ע��״̬
	}
	printf("AT+CEREG=1\r\n");
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	Clear_Buffer();	

	while(strx==NULL&&extstrx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CEREG=1\r\n");//�ж���Ӫ��
		Delay(300);
	    strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	}
	

	/*	 printf("AT+COPS?\r\n");//�ж���Ӫ��
			Delay(300);
			strx=strstr((const char*)RxBuffer,(const char*)"46011");//���ص�����Ӫ��
			Clear_Buffer();	
		while(strx==NULL)
		{
			Clear_Buffer();	
			printf("AT+COPS?\r\n");//�ж���Ӫ��
			Delay(300);
			strx=strstr((const char*)RxBuffer,(const char*)"46011");//���ص�����Ӫ��
		}
		*///ż������������ ����ע���������ģ�����COPS 2,2,""�����Դ˴������ε�
}

void BC95_PDPACT(void)//�������Ϊ���ӷ�������׼��
{
 /*  printf("AT+CGATT=0\r\n");//�ر�
		 	Delay(300);
	printf("AT+CGATT?\r\n");//��ȡ״̬
	 	Delay(300);
	  strx=strstr((const char*)RxBuffer,(const char*)" +CGATT:0");//ע����������Ϣ
		Clear_Buffer();	
		while(strx==NULL)
		{
			printf("AT+CGATT=0\r\n");//�ر�
		 	Delay(300);
		  Clear_Buffer();	
			printf("AT+CGATT?\r\n");//�رճ���
	 	  Delay(300);
			strx=strstr((const char*)RxBuffer,(const char*)"+CGATT:0");//��ȡ����״̬
		}
	*/
	
	printf("AT+CGDCONT=1,\042IP\042,\042HUAWEI.COM\042\r\n");//����APN
	Delay(300);
//AT+NSOCL=0   �ر�UDP
	printf("AT+CGATT=1\r\n");//�����
	Delay(300);
	printf("AT+CGATT?\r\n");//�����
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)" +CGATT:1");//ע����������Ϣ
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CGATT?\r\n");//�����
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"+CGATT:1");//���ص�����Ӫ��
	}
	printf("AT+CSCON?\r\n");//�ж�����״̬������1���ǳɹ�
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"+CSCON:0,1");//ע����������Ϣ
	extstrx=strstr((const char*)RxBuffer,(const char*)"+CSCON:0,0");//ע����������Ϣ
	Clear_Buffer();	
	while(strx==NULL&&extstrx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CSCON?\r\n");//
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"+CSCON:0,1");//
		extstrx=strstr((const char*)RxBuffer,(const char*)"+CSCON:0,0");//
	}
}

void BC95_ConUDP(void)
{
//	uint8_t i;
	printf("AT+NSOCL=0\r\n");//�ر�socekt����
	Delay(300);
//	printf("AT+NSOCR=DGRAM,17,3568,1\r\n");//����һ��Socket
	printf("AT+NSOCR=DGRAM,17,10000,1\r\n");//����һ��Socket�� ���ӹ���ƽ̨
	Delay(300);
//	printf("AT+NSOST=0,120.24.184.124,8010,%c,%s\r\n",'8',"727394ACB8221234");//����0socketIP�Ͷ˿ں������Ӧ���ݳ����Լ�����,
//2�Žڵ㷢��ע����Կ������ƽ̨�� ep=UBRM2AUTZ1FNJEY2&pw=123456
	printf("AT+NSOST=0,115.29.240.46,6000,%d,%s\r\n",29,"65703D5542524D324155545A31464E4A4559322670773D313233343536");//����0socketIP�Ͷ˿ں������Ӧ���ݳ����Լ�����,
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	while(strx==NULL)
	{
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	}
	Clear_Buffer();	
	
	//��PC���ͳɹ�ָ��
	DIR485_1;
	delay_ms(1);
	Uart1_SendStr("Connect OK\r\n");
	delay_ms(1);
	DIR485_0;
	
}
void BC95_Senddata(uint8_t len,uint8_t *data)
{
	printf("AT+NSOST=0,115.29.240.46,6000,%d,%s\r\n",len,data);//����0 socketIP�Ͷ˿ں������Ӧ���ݳ����Լ�����,727394ACB8221234
	//printf("AT+NSOST=0,120.24.184.124,8010,%c,%s\r\n",'8',"727394ACB8221234");//����0socketIP�Ͷ˿ں������Ӧ���ݳ����Լ�����,
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	while(strx==NULL)
	{
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
	}
	
	//��PC���ͳɹ�ָ��
	DIR485_1;
	delay_ms(1);
	Uart1_SendStr("Send OK\r\n");
	delay_ms(1);
	DIR485_0;
	
	Clear_Buffer();	
	
}
void BC95_RECData(void)
{
	char i;
//	static char nexti;
	strx=strstr((const char*)RxBuffer,(const char*)"+NSONMI:");//����+NSONMI:���������յ�UDP���������ص�����
	if(strx)
	{
		Clear_Buffer();	
		BC95_Status.Socketnum=strx[8];//���
		BC95_Status.reclen=strx[10];//����
		printf("AT+NSORF=%c,%c\r\n",BC95_Status.Socketnum,BC95_Status.reclen);//�����Լ����
		Delay(300);
		/*
		 p=strstr((const char*)buf,(const char*)"&");//?????
			for(i=0;;i++)
			{
				 btdata.getimei[i]=p[i+1];
				 if( btdata.getimei[i]=='&')
				   break;
			}
		*/
		
		strx=strstr((const char*)RxBuffer,(const char*)",");//��ȡ����һ������
		strx=strstr((const char*)(strx+1),(const char*)",");//��ȡ���ڶ�������
		strx=strstr((const char*)(strx+1),(const char*)",");//��ȡ������������
		for(i=0;;i++)
		{ 
			if(strx[i+1]==',')
			break;
			BC95_Status.recdatalen[i]=strx[i+1];//��ȡ���ݳ���
		}
		strx=strstr((const char*)(strx+1),(const char*)",");//��ȡ�����ĸ�����
		for(i=0;;i++)
		{
			if(strx[i+1]==',')
			break;
			BC95_Status.recdata[i]=strx[i+1];//��ȡ��������
		}
	}
}
