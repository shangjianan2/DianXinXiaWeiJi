/**
  ******************************************************************************
  * @file    Project/STM32L1xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    16-May-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "timer.h"
#include "bc95.h"
#include "led.h"

GPIO_InitTypeDef GPIO_InitStructure;
static __IO uint32_t TimingDelay;

/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nTime);
/** @addtogroup Template_Project
  * @{
  */


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
  
extern unsigned char uart1_getok;
extern char RxCounter1,RxBuffer1[100];
extern char RxCounter,RxBuffer[100];     //接收缓冲,最大USART_REC_LEN个字节.
  
int main(void)
{
//	char *strx,str[10];
	u8 sendata[100];
	u8 i;
	u8 uTemp;
	
	if (SysTick_Config(SystemCoreClock / 1000))//设置24bit定时器 1ms中断一次
	{ 
		/* Capture error */ 
		while (1);
	}

	uart1_getok = 0;
	DIR485_0;			//485接收状态
	LED_Init();
	uart_init(9600);
	uart3_init(9600);
	TIM3_Int_Init(99,3199);//10ms中断一次
	TIM4_Int_Init(4999,3199);//500ms中断一次	
	BC95_Init();
//	BC95_PDPACT();		//连接谷雨平台时，无用
	BC95_ConUDP();		//利用密钥连接谷雨平台
	
	sendata[0] = 30;
	while (1)
	{
		if(uart1_getok==1)
//		if(1)
		{
			//BC95发送数据
			RxBuffer1[RxCounter1] = 0;
			//必须转换为ASCII码传输, 0-9, A-F
			for (i=0;i<RxCounter1;i++)
			{
				uTemp = (RxBuffer1[i]&0xf0)>>4;
				if (uTemp<=9)		//number
				{
					sendata[i*2] = uTemp+0x30;
				}
				else
				{
					sendata[i*2] = uTemp+55;		//字母
				}
				uTemp = RxBuffer1[i]&0x0f;
				if (uTemp<=9)		//number
				{
					sendata[i*2+1] = uTemp+0x30;
				}
				else
				{
					sendata[i*2+1] = uTemp+55;		//字母
				}
			}
			sendata[RxCounter1*2] = 0;
			BC95_Senddata(RxCounter1,sendata);			//发送测试数据
			uart1_getok=0;
			RxCounter1=0;
		}
		Delay(1000);
	}
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
