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

#include  "ucos_ii.h"  		//uC/OS-IIϵͳ����ͷ�ļ�

#include  "BSP.h"			//�뿪������صĺ���
#include 	"app.h"			//�û�������
#include 	"led.h"			//LED��������

typedef unsigned char BYTE;
typedef unsigned int UINT;



#define ENDMARK_OD 0x0D
#define ENDMARK_0A 0x0A

#define BREATH_WHITE     0x01
#define BREATH_GREEN     0x02



#endif //__INCLUDES_H__
