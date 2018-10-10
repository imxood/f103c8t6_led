#include "bsp_ledstrip.h"
#include "bsp_ws2812b.h"


OS_STK CIRCULARRING_TASK_STK[CIRCULARRING_STK_SIZE];
OS_STK BREATHING_TASK_STK[BREATHING_STK_SIZE];
OS_STK FLASHING_TASK_STK[FLASHING_STK_SIZE];
OS_STK COLOURAROUND_TASK_STK[COLOURAROUND_STK_SIZE];


OS_TCB CircularRingTCB;
OS_TCB BreathingTCB;
OS_TCB Flashing_TCB;
OS_TCB ColourAround_TCB;



void CircularRing_Task ( void *p_arg )
{
    INT8U err;		
    uint8_t index = 0;
		WS2812_WRITE = OSMutexCreate(26 ,&err);
    while ( 1 )
    {
        //MY_DEBUG_PRINT_INFO ( "CircularRing_Task\r\n" );
        OSMutexPend ( WS2812_WRITE, 0, &err );
        SetWholeColor ( GROUP_B, 0, 0, 0 );
        SetLedColor ( index, 0, 0, 250 );
        WS2812_update ( GROUP_B );
        index++;

        if ( index >= LED_NUMBER )
            index = 0;

        OSTimeDlyHMSM ( 0, 0, 0, 10); //延时20ms
        OSMutexPost ( WS2812_WRITE);
        OSTimeDlyHMSM ( 0, 0, 0, 100); //延时100ms
    }

}

void Breathing_Task ( void *p_arg )
{
    INT8U err;
//    uint8_t red = 0;
    uint8_t green = 0;
//    uint8_t blue = 0;
    uint8_t dirc = 0;

    while ( 1 )
    {
        //MY_DEBUG_PRINT_INFO ( "Breathing_Task\r\n" );
        OSMutexPend ( WS2812_WRITE, 0, &err );

        if ( dirc == 0 )
        {

            green += 5;
            SetWholeColor ( GROUP_B, 0, green, 0 );
            WS2812_update ( GROUP_B );

            if ( green == 255 )
                dirc = 1;
        }
        else
        {
            green -= 5;
            SetWholeColor ( GROUP_B, 0, green, 0 );
            WS2812_update ( GROUP_B );

            if ( green == 0 )
                dirc = 0;

        }

        OSTimeDlyHMSM ( 0, 0, 0, 10); //延时20ms
        OSMutexPost ( WS2812_WRITE);
        OSTimeDlyHMSM ( 0, 0, 0, 10); //延时10ms
    }

}

void Flashing_Task ( void *p_arg )
{
    INT8U err;


    while ( 1 )
    {

        //MY_DEBUG_PRINT_INFO ( "Flashing_Task_0\r\n" );
        OSMutexPend ( WS2812_WRITE, 0, &err );
        SetWholeColor ( GROUP_B, 0, 0, 0 );
        WS2812_update ( GROUP_B );
        OSTimeDlyHMSM ( 0, 0, 0, 50); //延时20ms
        SetWholeColor ( GROUP_B, 150, 0, 150 );
        WS2812_update ( GROUP_B );
        OSTimeDlyHMSM ( 0, 0, 0, 10); //延时20ms
        OSMutexPost ( WS2812_WRITE);
        OSTimeDlyHMSM ( 0, 0, 0, 100); //延时20ms

    }

}



void ColourAround_Task ( void *p_arg )
{
    INT8U err;
    uint8_t i = 0;
		
    while ( 1 )
    {
			
				
        //MY_DEBUG_PRINT_INFO ( "ColourAround_Task\r\n" );

        OSMutexPend ( WS2812_WRITE, 0, &err );

        SetLedColor ( ( 0 + i ) % 4, 250, 0, 0 );
        SetLedColor ( ( 1 + i ) % 4, 0, 25, 0 );
        SetLedColor ( ( 2 + i ) % 4, 150, 0, 150 );
        SetLedColor ( ( 3 + i ) % 4, 0, 0, 250 );
        WS2812_update ( GROUP_B );
        i++;

        if ( i == 4 )
        {
            i = 0;
        }

        OSTimeDlyHMSM ( 0, 0, 0, 10); //延时20ms
        OSMutexPost ( WS2812_WRITE);
        OSTimeDlyHMSM ( 0, 0, 0, 100); //延时100ms
    }
}


void oneLedTest(void *p_arg)
{
	INT8U err;
	while(1)
	{
		OSMutexPend ( WS2812_WRITE, 0, &err );
		OSTimeDlyHMSM ( 0, 0, 0, 10); //延时20ms
		SetLedColor(0, 50, 50, 50);
		WS2812_update ( GROUP_B );
		OSTimeDlyHMSM ( 0, 0, 0, 10); //延时20ms
    OSMutexPost ( WS2812_WRITE);
    OSTimeDlyHMSM ( 0, 0, 0, 100); //延时100ms
	}
}
