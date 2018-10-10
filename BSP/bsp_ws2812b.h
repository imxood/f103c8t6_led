#ifndef __WS2812B_H
#define	__WS2812B_H

#include "includes.h"

#define WS2812_FREQ											(800000) 			
#define TIMER_CLOCK_FREQ									(8000000)   	    
#define TIMER_PERIOD										90//(TIMER_CLOCK_FREQ / WS2812_FREQ)
#define LED_NUMBER											(8)			        
#define LED_DATA_SIZE										(LED_NUMBER * 24)
#define RESET_SLOTS_BEGIN									(50)
#define RESET_SLOTS_END										(50)
#define WS2812_LAST_SLOT									(1)
#define LED_BUFFER_SIZE										(RESET_SLOTS_BEGIN + LED_DATA_SIZE + WS2812_LAST_SLOT + RESET_SLOTS_END)
#define WS2812_0											(TIMER_PERIOD / 3)		
#define WS2812_1											(TIMER_PERIOD * 2 / 3)	
#define WS2812_RESET										(0)


#define GROUP_A                                             0       // 1盏LED, 针对不同的中断源
#define GROUP_B                                             1       // 4盏LED



void WS2812_Init ( void );
void WS2812_update ( uint8_t group );
void SetLedColor ( uint8_t index, uint8_t red, uint8_t green, uint8_t blue );
void SetWholeColor ( uint8_t num, uint8_t red, uint8_t green, uint8_t blue );



#endif /* __WS2812B_H */
