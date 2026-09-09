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
#include "switch.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************

static volatile bool time_expire = false;
static volatile bool switch_scan_flag = false;
static volatile uint16_t tick_count = 0;
static volatile uint8_t scan_tick_count = 0;
static uint8_t display_count = 0;

#define TICKS_PER_SECOND    167U    /* 6ms tick = ~167 ticks per second */
#define SWITCH_SCAN_TICKS   4U      /* Scan switches every 24ms (4 x 6ms) */

// *****************************************************************************
// *****************************************************************************
// Section: Local Functions
// *****************************************************************************
// *****************************************************************************

static uint8_t GetPressedSwitchNumber(void)
{
    uint8_t swState = Switch_GetState();

    if (swState & SW_S1_B)  return 1U;
    if (swState & SW_S2_F)  return 2U;
    if (swState & SW_S3_G)  return 3U;
    if (swState & SW_S4_DP) return 4U;
    if (swState & SW_S5_E)  return 5U;
    if (swState & SW_S6_D)  return 6U;
    if (swState & SW_S7_C)  return 7U;

    return 0U;  /* No switch pressed */
}

static void TC0_Callback(TC_TIMER_STATUS status, uintptr_t context)
{
    (void)context;

    if ((status & TC_TIMER_STATUS_OVERFLOW) != 0U)
    {
        /* Refresh 7-segment display (multiplexing) */
        SevenSeg_Refresh();

        /* Switch scan timing */
        scan_tick_count++;
        if (scan_tick_count >= SWITCH_SCAN_TICKS)
        {
            scan_tick_count = 0;
            switch_scan_flag = true;
        }

        /* 1 second timing */
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

    /* Set timer period to 6ms (6000-1 at 1MHz) */
    TC0_Timer16bitPeriodSet(5999U);

    /* Initialize 7-segment display */
    SevenSeg_Init();
    SevenSeg_SetValue(0);

    /* Initialize switch scanning */
    Switch_Init();

    /* Register TC0 callback and start timer */
    TC0_TimerCallbackRegister(TC0_Callback, 0);
    TC0_TimerStart();

    LED_T_Set();

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );

        /* Switch scanning (every 20ms) */
        if (switch_scan_flag)
        {
            uint8_t switchNum;

            switch_scan_flag = false;
            Switch_Scan();

            /* Test: Display switch number when pressed */
            switchNum = GetPressedSwitchNumber();
            if (switchNum != 0U)
            {
                SevenSeg_SetValue(switchNum);
            }
        }

        if (time_expire)
        {
            time_expire = false;

            /* Test: Display 0-99, increment every second (when no switch pressed) */
            if (GetPressedSwitchNumber() == 0U)
            {
                SevenSeg_SetValue(display_count);
                display_count++;
                if (display_count > 99U)
                {
                    display_count = 0U;
                }
            }
        }
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}




/*******************************************************************************
 End of File
*/

