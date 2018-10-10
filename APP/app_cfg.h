#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__


/*******************设置任务优先级*******************/
#define OS_TASK_TMR_PRIO 				20
#define STARTUP_TASK_PRIO       21   
#define	TASK_USART_PRIO				22
#define	TASK_LED_PRIO			23 


/************设置栈大小（单位为 OS_STK ）************/
#define STARTUP_TASK_STK_SIZE   80   
#define	TASK_LED_STK_SIZE				80
#define	TASK_USART_STK_SIZE			80


#endif

