#ifndef  __INCLUDES_H__
#define  __INCLUDES_H__

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "misc.h"

#include  "ucos_ii.h"  		//uC/OS-II系统函数头文件

#include  "BSP.h"			//与开发板相关的函数
#include 	"app.h"			//用户任务函数
#include 	"led.h"			//LED驱动函数

typedef unsigned char BYTE;
typedef unsigned int UINT;



#define ENDMARK_OD 0x0D
#define ENDMARK_0A 0x0A

#define BREATH_WHITE     0x01
#define BREATH_GREEN     0x02



#endif //__INCLUDES_H__
