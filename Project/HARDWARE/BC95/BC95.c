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

void Clear_Buffer(void)//清空缓存
{
//	u8 i;
	Uart1_SendStr(RxBuffer);
//	for(i=0;i<100;i++)
	//RxBuffer[i]=0;
	RxCounter=0;
}
void BC95_Init(void)
{
	printf("AT\r\n"); 		//发送AT指令
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT\r\n"); 
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	}
	
	printf("AT+CMEE=1\r\n"); //允许错误值
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	Clear_Buffer();	

	printf("AT+NBAND?\r\n");//获取频段号
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"+NBAND:5");//返回5  电信
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT+NBAND?\r\n");//获取频段号
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"+NBAND:5");//返回OK
	}

	printf("AT+CIMI\r\n");//获取卡号，类似是否存在卡的意思，比较重要。
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"46011");//返46011
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CIMI\r\n");//获取卡号，类似是否存在卡的意思，比较重要。
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"46011");//返回OK,说明卡是存在的
	}

	printf("AT+CGATT=1\r\n");//激活网络，PDP
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//返46011
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CGATT=1\r\n");//获取卡号，类似是否存在卡的意思，比较重要。
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK,说明卡是存在的
	}
	
	printf("AT+CGATT?\r\n");//激活网络，PDP
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"+CGATT:1");//返1
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CGATT?\r\n");//获取激活状态
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"+CGATT:1");//返回1,表明注网成功
	}

	printf("AT+CSQ\r\n");//查看获取CSQ值
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"+CSQ");//返回CSQ
	if(strx)
	{
		BC95_Status.CSQ=(strx[5]-0x30)*10+(strx[6]-0x30);//获取CSQ
		if(BC95_Status.CSQ==99)//说明扫网失败
		{
			while(1)
			{
				Uart1_SendStr("信号搜索失败，请查看原因!\r\n");
				Delay(300);
			}
		}
	}
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CSQ\r\n");//查看获取CSQ值
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"+CSQ");//
		if(strx)
		{
			BC95_Status.CSQ=(strx[5]-0x30)*10+(strx[6]-0x30);//获取CSQ
			if(BC95_Status.CSQ==99)//说明扫网失败
			{
				while(1)
				{
					Uart1_SendStr("信号搜索失败，请查看原因!\r\n");
					Delay(300);
				}
			}
		}
	}
	Clear_Buffer();	

	printf("AT+CEREG?\r\n");
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"+CEREG:0,1");//返回注册状态
	extstrx=strstr((const char*)RxBuffer,(const char*)"+CEREG:1,1");//返回注册状态
	Clear_Buffer();	
	while(strx==NULL&&extstrx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CEREG?\r\n");//判断运营商
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"+CEREG:0,1");//返回注册状态
		extstrx=strstr((const char*)RxBuffer,(const char*)"+CEREG:1,1");//返回注册状态
	}
	printf("AT+CEREG=1\r\n");
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	Clear_Buffer();	

	while(strx==NULL&&extstrx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CEREG=1\r\n");//判断运营商
		Delay(300);
	    strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	}
	

	/*	 printf("AT+COPS?\r\n");//判断运营商
			Delay(300);
			strx=strstr((const char*)RxBuffer,(const char*)"46011");//返回电信运营商
			Clear_Buffer();	
		while(strx==NULL)
		{
			Clear_Buffer();	
			printf("AT+COPS?\r\n");//判断运营商
			Delay(300);
			strx=strstr((const char*)RxBuffer,(const char*)"46011");//返回电信运营商
		}
		*///偶尔会搜索不到 但是注册是正常的，返回COPS 2,2,""，所以此处先屏蔽掉
}

void BC95_PDPACT(void)//激活场景，为连接服务器做准备
{
 /*  printf("AT+CGATT=0\r\n");//关闭
		 	Delay(300);
	printf("AT+CGATT?\r\n");//获取状态
	 	Delay(300);
	  strx=strstr((const char*)RxBuffer,(const char*)" +CGATT:0");//注册上网络信息
		Clear_Buffer();	
		while(strx==NULL)
		{
			printf("AT+CGATT=0\r\n");//关闭
		 	Delay(300);
		  Clear_Buffer();	
			printf("AT+CGATT?\r\n");//关闭场景
	 	  Delay(300);
			strx=strstr((const char*)RxBuffer,(const char*)"+CGATT:0");//获取返回状态
		}
	*/
	
	printf("AT+CGDCONT=1,\042IP\042,\042HUAWEI.COM\042\r\n");//设置APN
	Delay(300);
//AT+NSOCL=0   关闭UDP
	printf("AT+CGATT=1\r\n");//激活场景
	Delay(300);
	printf("AT+CGATT?\r\n");//激活场景
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)" +CGATT:1");//注册上网络信息
	Clear_Buffer();	
	while(strx==NULL)
	{
		Clear_Buffer();	
		printf("AT+CGATT?\r\n");//激活场景
		Delay(300);
		strx=strstr((const char*)RxBuffer,(const char*)"+CGATT:1");//返回电信运营商
	}
	printf("AT+CSCON?\r\n");//判断连接状态，返回1就是成功
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"+CSCON:0,1");//注册上网络信息
	extstrx=strstr((const char*)RxBuffer,(const char*)"+CSCON:0,0");//注册上网络信息
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
	printf("AT+NSOCL=0\r\n");//关闭socekt连接
	Delay(300);
//	printf("AT+NSOCR=DGRAM,17,3568,1\r\n");//创建一个Socket
	printf("AT+NSOCR=DGRAM,17,10000,1\r\n");//创建一个Socket， 连接谷雨平台
	Delay(300);
//	printf("AT+NSOST=0,120.24.184.124,8010,%c,%s\r\n",'8',"727394ACB8221234");//发送0socketIP和端口后面跟对应数据长度以及数据,
//2号节点发送注册密钥给谷雨平台： ep=UBRM2AUTZ1FNJEY2&pw=123456
	printf("AT+NSOST=0,115.29.240.46,6000,%d,%s\r\n",29,"65703D5542524D324155545A31464E4A4559322670773D313233343536");//发送0socketIP和端口后面跟对应数据长度以及数据,
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	while(strx==NULL)
	{
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	}
	Clear_Buffer();	
	
	//向PC发送成功指令
	DIR485_1;
	delay_ms(1);
	Uart1_SendStr("Connect OK\r\n");
	delay_ms(1);
	DIR485_0;
	
}
void BC95_Senddata(uint8_t len,uint8_t *data)
{
	printf("AT+NSOST=0,115.29.240.46,6000,%d,%s\r\n",len,data);//发送0 socketIP和端口后面跟对应数据长度以及数据,727394ACB8221234
	//printf("AT+NSOST=0,120.24.184.124,8010,%c,%s\r\n",'8',"727394ACB8221234");//发送0socketIP和端口后面跟对应数据长度以及数据,
	Delay(300);
	strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	while(strx==NULL)
	{
		strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	}
	
	//向PC发送成功指令
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
	strx=strstr((const char*)RxBuffer,(const char*)"+NSONMI:");//返回+NSONMI:，表明接收到UDP服务器发回的数据
	if(strx)
	{
		Clear_Buffer();	
		BC95_Status.Socketnum=strx[8];//编号
		BC95_Status.reclen=strx[10];//长度
		printf("AT+NSORF=%c,%c\r\n",BC95_Status.Socketnum,BC95_Status.reclen);//长度以及编号
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
		
		strx=strstr((const char*)RxBuffer,(const char*)",");//获取到第一个逗号
		strx=strstr((const char*)(strx+1),(const char*)",");//获取到第二个逗号
		strx=strstr((const char*)(strx+1),(const char*)",");//获取到第三个逗号
		for(i=0;;i++)
		{ 
			if(strx[i+1]==',')
			break;
			BC95_Status.recdatalen[i]=strx[i+1];//获取数据长度
		}
		strx=strstr((const char*)(strx+1),(const char*)",");//获取到第四个逗号
		for(i=0;;i++)
		{
			if(strx[i+1]==',')
			break;
			BC95_Status.recdata[i]=strx[i+1];//获取数据内容
		}
	}
}
