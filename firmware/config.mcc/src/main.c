/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "segment_pins.h"
#include "seven_seg.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************

static volatile bool time_expire = false;
static volatile uint16_t tick_count = 0;
static uint8_t display_count = 0;

#define TICKS_PER_SECOND    250U    /* 4ms tick = 250 ticks per second */

// *****************************************************************************
// *****************************************************************************
// Section: Local Functions
// *****************************************************************************
// *****************************************************************************

static void TC0_Callback(TC_TIMER_STATUS status, uintptr_t context)
{
    (void)context;

    if ((status & TC_TIMER_STATUS_OVERFLOW) != 0U)
    {
        /* Refresh 7-segment display (multiplexing) */
        SevenSeg_Refresh();

        tick_count++;
        if (tick_count >= TICKS_PER_SECOND)
        {
            tick_count = 0;
            time_expire = true;
        }
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    /* Set timer period to 4ms (4000-1 at 1MHz) */
    TC0_Timer16bitPeriodSet(3999U);

    /* Initialize 7-segment display */
    SevenSeg_Init();
    SevenSeg_SetValue(0);

    /* Register TC0 callback and start timer */
    TC0_TimerCallbackRegister(TC0_Callback, 0);
    TC0_TimerStart();

    LED_T_Set();

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );

        if (time_expire)
        {
            time_expire = false;

            /* Test: Display 0-99, increment every second */
            SevenSeg_SetValue(display_count);
            display_count++;
            if (display_count > 99U)
            {
                display_count = 0U;
            }
        }
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}




/*******************************************************************************
 End of File
*/

