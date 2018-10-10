#ifndef __BSP_LEDSTRIP_H
#define	__BSP_LEDSTRIP_H

#include "includes.h"

/* 设置LED灯效任务优先级 */
#define LED_TASK_PRIO 26
#define CIRCULARRING_TASK_PRIO              LED_TASK_PRIO
#define BREATHING_TASK_PRIO                 LED_TASK_PRIO
#define FLASHING_TASK_PRIO                  LED_TASK_PRIO
#define COLOURAROUND_TASK_PRIO              LED_TASK_PRIO

/* 设置LED灯效任务堆栈大小 */

#define CIRCULARRING_STK_SIZE               128
#define BREATHING_STK_SIZE                  128
#define FLASHING_STK_SIZE                   128
#define COLOURAROUND_STK_SIZE               128

/* 设置LED灯效任务堆栈 */

extern OS_STK CIRCULARRING_TASK_STK[CIRCULARRING_STK_SIZE];
extern OS_STK BREATHING_TASK_STK[BREATHING_STK_SIZE];
extern OS_STK FLASHING_TASK_STK[FLASHING_STK_SIZE];
extern OS_STK COLOURAROUND_TASK_STK[COLOURAROUND_STK_SIZE];

/* 设置LED灯效任务控制块 */
extern OS_TCB CircularRingTCB;
extern OS_TCB BreathingTCB;
extern OS_TCB Flashing_TCB;
extern OS_TCB ColourAround_TCB;

extern OS_EVENT *WS2812_WRITE;

void CircularRing_Task ( void *p_arg );
void Breathing_Task ( void *p_arg );
void Flashing_Task ( void *p_arg );
void ColourAround_Task ( void *p_arg );
void oneLedTest( void *p_arg );


#endif /* __BSP_LEDSTRIP_H */

