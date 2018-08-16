#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include <stm32l1xx.h>
#define u8 int8_t
#define u16 int16_t
#define u32 int32_t

void uart_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);
void Uart1_SendStr(char*SendBuf);
#endif


