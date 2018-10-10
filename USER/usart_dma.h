#ifndef _USART_DMA_H
#define _USART_DMA_H


#include "includes.h"
/*--- LumModule Usart Config ---------------------------------------*/
#define LUMMOD_UART 						USART3
#define LUMMOD_UART_GPIO 				GPIOC
#define LUMMOD_UART_CLK 				RCC_APB1Periph_USART3
#define LUMMOD_UART_GPIO_CLK 		RCC_APB2Periph_GPIOC


#define LUMMOD_UART_RxPin 			GPIO_Pin_11
#define LUMMOD_UART_TxPin 			GPIO_Pin_10
#define LUMMOD_UART_IRQn 				USART3_IRQn
#define LUMMOD_UART_DR_Base 		(USART3_BASE + 0x4) //0x40013804
#define LUMMOD_UART_Tx_DMA_Channel 			DMA1_Channel2
#define LUMMOD_UART_Tx_DMA_FLAG 				DMA1_FLAG_GL2//DMA1_FLAG_TC2 | DMA1_FLAG_TE2
#define LUMMOD_UART_Tx_DMA_IRQ 					DMA1_Channel2_IRQn
#define LUMMOD_UART_Rx_DMA_Channel 			DMA1_Channel3
#define LUMMOD_UART_Rx_DMA_FLAG 				DMA1_FLAG_GL3//DMA1_FLAG_TC3 | DMA1_FLAG_TE3
#define LUMMOD_UART_Rx_DMA_IRQ 					DMA1_Channel3_IRQn

#define LUMMOD_TX_BSIZE 200
#define LUMMOD_RX_BSIZE 200


void DMA_Uart_Init(void);
void LumMod_Uart_DMA_Rx_Data(void);
void LumMod_Uart_DAM_Tx_Over(void);


void Uart_Init(void);
void DMA_Uart_Init(void);



#endif 




