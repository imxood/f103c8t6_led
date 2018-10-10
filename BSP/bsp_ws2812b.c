#include "bsp_ws2812b.h"
#include "includes.h"


#define TIM4CCR1ADDR        0x40000834
#define TIM4CCR2ADDR        0x40000838

volatile  uint8_t LEDbuffer[LED_BUFFER_SIZE];



static GPIO_InitTypeDef tim4ch1pwm =
{
    .GPIO_Pin = GPIO_Pin_6,
    .GPIO_Speed = GPIO_Speed_50MHz,
    .GPIO_Mode = GPIO_Mode_AF_PP
};
static GPIO_InitTypeDef tim4ch2pwm =
{
    .GPIO_Pin = GPIO_Pin_7,
    .GPIO_Speed = GPIO_Speed_50MHz,
    .GPIO_Mode = GPIO_Mode_AF_PP
};


static DMA_InitTypeDef dmachan1 =
{
    .DMA_PeripheralBaseAddr = ( uint32_t )&TIM4->CCR1,
    .DMA_MemoryBaseAddr = ( uint32_t ) ( &LEDbuffer[0] ),
    .DMA_DIR = DMA_DIR_PeripheralDST,
    .DMA_BufferSize = LED_BUFFER_SIZE + 1,
    .DMA_PeripheralInc = DMA_PeripheralInc_Disable,
    .DMA_MemoryInc = DMA_MemoryInc_Enable,
    .DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord,
    .DMA_MemoryDataSize = DMA_MemoryDataSize_Byte,
    .DMA_Mode = DMA_Mode_Circular,
    .DMA_Priority = DMA_Priority_High,
    .DMA_M2M = DMA_M2M_Disable
};

static DMA_InitTypeDef dmachan4 =
{
    .DMA_PeripheralBaseAddr = ( uint32_t )&TIM4->CCR2,
    .DMA_MemoryBaseAddr = ( uint32_t ) ( &LEDbuffer[0] ),
    .DMA_DIR = DMA_DIR_PeripheralDST,
    .DMA_BufferSize = LED_BUFFER_SIZE + 1,
    .DMA_PeripheralInc = DMA_PeripheralInc_Disable,
    .DMA_MemoryInc = DMA_MemoryInc_Enable,
    .DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord,
    .DMA_MemoryDataSize = DMA_MemoryDataSize_Byte,
    .DMA_Mode = DMA_Mode_Circular,
    .DMA_Priority = DMA_Priority_High,
    .DMA_M2M = DMA_M2M_Disable
};

static TIM_TimeBaseInitTypeDef tim4 =
{
    .TIM_Period = TIMER_PERIOD - 1,
    .TIM_Prescaler = 0,
    .TIM_ClockDivision = TIM_CKD_DIV1,
    .TIM_CounterMode = TIM_CounterMode_Up
};
static TIM_OCInitTypeDef timingmode =
{
    .TIM_OCMode = TIM_OCMode_PWM1,
    .TIM_OutputState = TIM_OutputState_Enable,
    .TIM_Pulse = 0,
    .TIM_OCPolarity = TIM_OCPolarity_High
};



/*************************************************************
* 函 数 名 : WS2812_Init
* 函数描述 : 初始化
* 返 回 值 : none
* 输入参数 : none
* 输出参数 : none

*************************************************************/
#include "led.h"
void WS2812_Init ()
{

		NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE );
//    RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOB, ENABLE );

    RCC_APB1PeriphClockCmd ( RCC_APB1Periph_TIM4, ENABLE );
    GPIO_Init ( GPIOB, &tim4ch1pwm );
    GPIO_Init ( GPIOB, &tim4ch2pwm );

    /* 初始化时基 */
    TIM_TimeBaseInit ( TIM4, &tim4 );

    /* 初始化channel1 */
    TIM_OC1PreloadConfig ( TIM4, TIM_OCPreload_Enable );
    TIM_OC1Init ( TIM4, &timingmode );

    /* 初始化channel2 */
    TIM_OC2PreloadConfig ( TIM4, TIM_OCPreload_Enable );
    TIM_OC2Init ( TIM4, &timingmode );

//    /* 初始化DMA1 */
    RCC_AHBPeriphClockCmd ( RCC_AHBPeriph_DMA1, ENABLE );

    /* 初始化DMA1通道 */
    DMA_Init ( DMA1_Channel1, &dmachan1 );
    DMA_Init ( DMA1_Channel4, &dmachan4 );

    TIM_DMACmd ( TIM4, TIM_DMA_CC1, ENABLE );
    TIM_DMACmd ( TIM4, TIM_DMA_CC2, ENABLE );

    /* 使能DMA中断 */
    DMA_ITConfig ( DMA1_Channel1, DMA_IT_TC | DMA_IT_TE, ENABLE );
    DMA_ITConfig ( DMA1_Channel4, DMA_IT_TC | DMA_IT_TE, ENABLE );
		
		
		//中断优先级NVIC设置
		NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn; //DMA中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ; //抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
		
//		NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn; //DMA中断
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ; //抢占优先级
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
		
		LED1( ON );
}

/*************************************************************
* 函 数 名 : WS2812_update
* 函数描述 : DMA发送数据
* 输入参数 : none
* 输出参数 : none
* 返 回 值 : none
*************************************************************/

void WS2812_update ( uint8_t group )
{

    TIM_Cmd ( TIM4, ENABLE );

    if ( group == GROUP_A )                                             // GROUP_A只有1盏LED灯
    {


        DMA_SetCurrDataCounter ( DMA1_Channel1, LED_BUFFER_SIZE );      

        DMA_Cmd ( DMA1_Channel1, ENABLE );                              

        TIM_DMACmd ( TIM4, TIM_DMA_Update, ENABLE );                    // 使能TIM4 DMA请求
    }
    else
    {


        DMA_SetCurrDataCounter ( DMA1_Channel4, LED_BUFFER_SIZE );      

        DMA_Cmd ( DMA1_Channel4, ENABLE );                              

        TIM_DMACmd ( TIM4, TIM_DMA_Update, ENABLE );                    // 使能TIM4 DMA请求

    }
}

/*************************************************************
* 函 数 名 : SetLedColor
* 函数描述 : 设置某一盏LED颜色
* 输入参数 : index  需要点亮的LED序号（第一盏、第二盏.....）
* 输出参数 : none
* 返 回 值 : none
*************************************************************/

void SetLedColor ( uint8_t index, uint8_t RED, uint8_t GREEN, uint8_t BLUE )
{
    uint8_t tempBuffer[24] = {0};
    uint8_t i;

    for ( i = 0; i < 8; i++ ) // GREEN data
        tempBuffer[i] = ( ( GREEN << i ) & 0x80 ) ? WS2812_1 : WS2812_0;

    for ( i = 0; i < 8; i++ ) // RED
        tempBuffer[8 + i] = ( ( RED << i ) & 0x80 ) ? WS2812_1 : WS2812_0;

    for ( i = 0; i < 8; i++ ) // BLUE
        tempBuffer[16 + i] = ( ( BLUE << i ) & 0x80 ) ? WS2812_1 : WS2812_0;

    for ( i = 0; i < 24; i++ )
        LEDbuffer[RESET_SLOTS_BEGIN + index * 24 + i] = tempBuffer[i];

}

void SetWholeColor (uint8_t num, uint8_t red, uint8_t green, uint8_t blue )
{
    uint32_t index;

		for ( index = 0; index < num; index++ )
            SetLedColor ( index, red, green, blue );
 
}




/****************************************************************
* 函 数 名：DMA1_Channel1_IRQHandler
* 函数描述：channel1中断处理
* 输入参数：none
* 输出参数：none
* 返回类型：void
*****************************************************************/

void DMA1_Channel1_IRQHandler()
{
    OSIntEnter();

    TIM_Cmd ( TIM4, DISABLE );
    TIM_DMACmd ( TIM4, TIM_DMA_Update, DISABLE );           // 禁止请求
    DMA_Cmd ( DMA1_Channel1, DISABLE );                     
    DMA_ClearFlag ( DMA1_FLAG_TC1 );
    memset ( ( char * ) LEDbuffer, 0, LED_BUFFER_SIZE );
    OSIntExit();

}

/****************************************************************
* 函 数 名：DMA1_Channel4_IRQHandler
* 函数描述：channel4中断处理
* 输入参数：none
* 输出参数：none
* 返回类型：void
*****************************************************************/

void DMA1_Channel4_IRQHandler()
{
    OSIntEnter();

    TIM_Cmd ( TIM4, DISABLE );
    TIM_DMACmd ( TIM4, TIM_DMA_Update, DISABLE );           // 禁止请求
    DMA_Cmd ( DMA1_Channel4, DISABLE );                     
    DMA_ClearFlag ( DMA1_FLAG_TC4 );
    memset ( ( char * ) LEDbuffer, 0, LED_BUFFER_SIZE );
    OSIntExit();
}
