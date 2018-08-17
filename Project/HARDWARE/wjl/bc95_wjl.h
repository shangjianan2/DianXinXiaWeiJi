#ifndef _BC95_WJL_H_
#define _BC95_WJL_H_

#include "usart.h"
#include <stm32l1xx.h>
#include "bc95.h"

void Clear_Buffer_wjl(void);
void BC95_Init_wjl(void);
void output_usart1(char *p_str);
int str_contain(char *str_1, char *str_2, int size_1, int size_2);
void send_printRec(char *str_send);
void bc95_init_new(void);

#endif
