#include "usart_dma.h"

volatile  uint8_t LumMod_Tx_Buf[200];
volatile  uint8_t LumMod_Rx_Buf[200];
int rec_len;

void Uart_Init(void)
{
			memset((void *)LumMod_Rx_Buf, 0x00, 200);
			NVIC_InitTypeDef NVIC_InitStructure;
			GPIO_InitTypeDef GPIO_InitStructure;
			USART_InitTypeDef USART_InitStructure;
			/* System Clocks Configuration */
			//= System Clocks Configuration====================================================================//
			/* Enable GPIO clock */
			RCC_APB2PeriphClockCmd(LUMMOD_UART_GPIO_CLK , ENABLE ); 
			
			/* Enable USART Clock */
			RCC_APB1PeriphClockCmd(LUMMOD_UART_CLK, ENABLE); 
			//=NVIC_Configuration==============================================================================//
			/* Configure the NVIC Preemption Priority Bits */
//			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
			
			/* Enable the DMA Interrupt */
//			NVIC_InitStructure.NVIC_IRQChannel = LUMMOD_UART_Tx_DMA_IRQ; 
//			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//			NVIC_Init(&NVIC_InitStructure);
			
			/* Enable the USART Interrupt */
			NVIC_InitStructure.NVIC_IRQChannel = LUMMOD_UART_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
			
			
			//=GPIO_Configuration==============================================================================//
			GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);			
			/* Configure USART3 Rx as input floating */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
			GPIO_InitStructure.GPIO_Pin = LUMMOD_UART_RxPin;
			GPIO_Init(LUMMOD_UART_GPIO, &GPIO_InitStructure);
			
			/* Configure USART3 Tx as alternate function push-pull */
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
			GPIO_InitStructure.GPIO_Pin = LUMMOD_UART_TxPin;
			GPIO_Init(LUMMOD_UART_GPIO, &GPIO_InitStructure);
			DMA_Uart_Init();
			
			
			/* USART Format configuration
			------------------------------------------------------*/
			USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
			USART_InitStructure.USART_StopBits = USART_StopBits_1;
			USART_InitStructure.USART_Parity = USART_Parity_No;
			USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		
			/* Configure USART3 */
			USART_InitStructure.USART_BaudRate = 115200;
			USART_Init(LUMMOD_UART, &USART_InitStructure);	
			
			
			/* Enable USART3 Receive and Transmit interrupts */
			USART_ITConfig(LUMMOD_UART, USART_IT_IDLE, ENABLE); 
			/* Enable the USART3 */
			USART_Cmd(LUMMOD_UART, ENABLE); 	
			
			/* Enable USARTy DMA TX request */
			USART_DMACmd(LUMMOD_UART, USART_DMAReq_Tx, ENABLE);
			USART_DMACmd(LUMMOD_UART, USART_DMAReq_Rx, ENABLE); 
}



void DMA_Uart_Init(void)
{
			DMA_InitTypeDef DMA_InitStructure;
			/* DMA clock enable */
			RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
			//=DMA_Configuration==============================================================================//
			/*--- LUMMOD_UART_Tx_DMA_Channel DMA Config ---*/
//			DMA_Cmd(LUMMOD_UART_Tx_DMA_Channel, DISABLE);
//			DMA_DeInit(LUMMOD_UART_Tx_DMA_Channel); 
//			DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t)(&LUMMOD_UART->DR);
//			DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)LumMod_Tx_Buf; 
//			DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
//			DMA_InitStructure.DMA_BufferSize = LUMMOD_TX_BSIZE;
//			DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
//			DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
//			DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//			DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//			DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; 
//			DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; 
//			DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; 
//			DMA_Init(LUMMOD_UART_Tx_DMA_Channel, &DMA_InitStructure);
//			DMA_ClearFlag(LUMMOD_UART_Tx_DMA_FLAG);
//			DMA_Cmd(LUMMOD_UART_Tx_DMA_Channel, DISABLE); 
//			DMA_ITConfig(LUMMOD_UART_Tx_DMA_Channel, DMA_IT_TC, ENABLE);
			
			
			/*--- LUMMOD_UART_Rx_DMA_Channel DMA Config ---*/
			DMA_Cmd(LUMMOD_UART_Rx_DMA_Channel, DISABLE);
			DMA_DeInit(LUMMOD_UART_Rx_DMA_Channel);
			DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&LUMMOD_UART->DR);
			DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)LumMod_Rx_Buf;
			DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; 
			DMA_InitStructure.DMA_BufferSize = LUMMOD_RX_BSIZE;
			DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
			DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
			DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
			DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; 
			DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
			DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
			DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; 
			DMA_Init(LUMMOD_UART_Rx_DMA_Channel, &DMA_InitStructure);
			DMA_ClearFlag(LUMMOD_UART_Rx_DMA_FLAG);
			DMA_Cmd(LUMMOD_UART_Rx_DMA_Channel, ENABLE);
}






//============================================================//
void DMA1_Channel2_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_FLAG_TC2))
	{
			LumMod_Uart_DAM_Tx_Over();
	}
}
void LumMod_Uart_Start_DMA_Tx(uint16_t size);

void LumMod_Uart_DAM_Tx_Over(void)
{
	DMA_ClearFlag(LUMMOD_UART_Tx_DMA_FLAG);
	DMA_Cmd(LUMMOD_UART_Tx_DMA_Channel, DISABLE);
	LumMod_Uart_Start_DMA_Tx(rec_len);

}



void LumMod_Uart_Start_DMA_Tx(uint16_t size)
{
	LUMMOD_UART_Tx_DMA_Channel->CNDTR = (uint16_t)size;
	DMA_Cmd(LUMMOD_UART_Tx_DMA_Channel, ENABLE);
}


//============================================================//
void USART3_IRQHandler(void)
{
	
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET) 
	{
		LumMod_Uart_DMA_Rx_Data();
		USART_ReceiveData( USART3 ); // Clear IDLE interrupt flag bit
	}
}

void LumMod_Uart_DMA_Rx_Data(void)
{
		DMA_Cmd(LUMMOD_UART_Rx_DMA_Channel, DISABLE);
		DMA_ClearFlag( LUMMOD_UART_Rx_DMA_FLAG ); 
		rec_len = LUMMOD_RX_BSIZE - DMA_GetCurrDataCounter(LUMMOD_UART_Rx_DMA_Channel); 
		LUMMOD_UART_Rx_DMA_Channel->CNDTR = LUMMOD_RX_BSIZE; 
	
		DMA_Cmd(LUMMOD_UART_Rx_DMA_Channel, ENABLE);
}





