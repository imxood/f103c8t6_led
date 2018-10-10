#include "includes.h"
#include "bsp_ws2812b.h"

#define LEDNUM 8

enum
{
	emR,
	emG,
	emB,
	emHZ,
	emS,
	em0D,
	em0A
}; //7

OS_STK task_led_stk[TASK_LED_STK_SIZE]; //定义栈

OS_EVENT *WS2812_WRITE;

extern volatile uint8_t LumMod_Rx_Buf[200];

void Task_Start(void *p_arg)
{
	INT8U err;
	WS2812_WRITE = OSMutexCreate(26, &err);
	(void)p_arg; // 'p_arg' 并没有用到，防止编译器提示警告
	SysTick_init();

	OSStatInit(); //初始化统计任务.这里会延时1秒钟左右

	OSTaskCreate(Task_LED, (void *)0, //创建LED灯带显示
				 &task_led_stk[TASK_LED_STK_SIZE - 1], TASK_LED_PRIO);

	OSTaskSuspend(STARTUP_TASK_PRIO); //挂起起始任务.
}

//灯带任务
void Task_LED(void *p_arg)
{
	SysTick_init();
	INT8U err;

	uint8_t green = 0;
	uint8_t white = 0;
	uint8_t dirc = 0;

	//	SetWholeColor(LEDNUM, 60, 60, 60);
	//	WS2812_update ( GROUP_B );

	while (1)
	{

		OSMutexPend(WS2812_WRITE, 0, &err);

		if (LumMod_Rx_Buf[em0D] == ENDMARK_OD && LumMod_Rx_Buf[em0A] == ENDMARK_0A)
		{

			if (LumMod_Rx_Buf[emS] == 0)
			{
				SetWholeColor(LEDNUM, LumMod_Rx_Buf[emR], LumMod_Rx_Buf[emG], LumMod_Rx_Buf[emB]);
				WS2812_update(GROUP_B);
				if (LumMod_Rx_Buf[emHZ] != 0)
				{
					OSTimeDlyHMSM(0, 0, 0, 999 / LumMod_Rx_Buf[emHZ]);
					SetWholeColor(LEDNUM, 0, 0, 0);
					WS2812_update(GROUP_B);
					OSTimeDlyHMSM(0, 0, 0, 999 / LumMod_Rx_Buf[emHZ]);
				}
			}

			if (LumMod_Rx_Buf[emS] == BREATH_WHITE) //呼吸状态
			{
				if (dirc == 0)
				{
					white += 5;
					SetWholeColor(LEDNUM, white, white, white);
					WS2812_update(GROUP_B);

					if (white == 95)
						dirc = 1;
				}
				else
				{
					white -= 5;
					SetWholeColor(LEDNUM, white, white, white);
					WS2812_update(GROUP_B);

					if (white == 10)
						dirc = 0;
				}
				OSTimeDlyHMSM(0, 0, 0, 200); //延时10ms
			}
			else if (LumMod_Rx_Buf[emS] == BREATH_GREEN) //呼吸状态
			{

				if (dirc == 0)
				{
					green += 5;
					SetWholeColor(LEDNUM, green, green, green);
					WS2812_update(GROUP_B);

					if (green == 95)
						dirc = 1;
				}
				else
				{
					green -= 5;
					SetWholeColor(LEDNUM, green, green, green);
					WS2812_update(GROUP_B);

					if (green == 10)
						dirc = 0;
				}
				OSTimeDlyHMSM(0, 0, 0, 200); //延时10ms
			}
		}
		OSTimeDlyHMSM(0, 0, 0, 10); //延时10ms
		OSMutexPost(WS2812_WRITE);
		OSTimeDlyHMSM(0, 0, 0, 10); //延时10ms
	}
}
