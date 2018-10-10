#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>

#define USART_REC_LEN 200

void Delay(__IO u32 nCount);
void USART1_Config(void);
unsigned char UART1GetByte(unsigned char* GetData);
void UART1Test(void);


#endif /* __USART1_H */
