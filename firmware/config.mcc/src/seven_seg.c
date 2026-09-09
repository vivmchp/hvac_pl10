/*******************************************************************************
  7-Segment Display Driver Source

  File Name:
    seven_seg.c

  Summary:
    Driver for 2-digit 7-segment display with multiplexing.

  Description:
    Common Anode display - COM HIGH turns on digit, Segment LOW turns on segment.
    COM2_AL = Left digit (tens), COM1_AL = Right digit (units).
    Segment mapping:
      L_S0_A = Segment A (top)
      L_S1_B = Segment B (upper right)
      L_S2_F = Segment F (upper left)
      L_S3_G = Segment G (middle)
      L_S4_DP = Decimal Point
      L_S5_E = Segment E (lower left)
      L_S6_D = Segment D (bottom)
      L_S7_C = Segment C (lower right)
*******************************************************************************/

#include "seven_seg.h"

/* Segment bit positions */
#define SEG_A_PIN   5U      /* PA05 */
#define SEG_B_PIN   0U      /* PA00 */
#define SEG_C_PIN   19U     /* PA19 */
#define SEG_D_PIN   18U     /* PA18 */
#define SEG_E_PIN   11U     /* PA11 */
#define SEG_F_PIN   4U      /* PA04 */
#define SEG_G_PIN   22U     /* PA22 */
#define SEG_DP_PIN  10U     /* PA10 */

#define SEG_A   (1U << SEG_A_PIN)
#define SEG_B   (1U << SEG_B_PIN)
#define SEG_C   (1U << SEG_C_PIN)
#define SEG_D   (1U << SEG_D_PIN)
#define SEG_E   (1U << SEG_E_PIN)
#define SEG_F   (1U << SEG_F_PIN)
#define SEG_G   (1U << SEG_G_PIN)
#define SEG_DP  (1U << SEG_DP_PIN)

#define ALL_SEGMENTS (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G | SEG_DP)

/*
 * 7-segment digit patterns (bits set = segment ON)
 * For common anode: we invert when writing (LOW = ON)
 *
 *   AAA
 *  F   B
 *   GGG
 *  E   C
 *   DDD
 */
static const uint32_t digitPatterns[10] = {
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,           /* 0 */
    SEG_B | SEG_C,                                            /* 1 */
    SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,                   /* 2 */
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,                   /* 3 */
    SEG_B | SEG_C | SEG_F | SEG_G,                           /* 4 */
    SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,                   /* 5 */
    SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,           /* 6 */
    SEG_A | SEG_B | SEG_C,                                    /* 7 */
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,   /* 8 */
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G            /* 9 */
};

static uint8_t currentDigit = 0;    /* 0 = right (units), 1 = left (tens) */
static uint8_t tensValue = 0;
static uint8_t unitsValue = 0;

static void SegmentPins_SetOutput(void)
{
    PORT_GroupOutputEnable(PORT_GROUP_0, ALL_SEGMENTS);
}

static void SegmentPins_SetInput(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, ALL_SEGMENTS);
}

static void WriteSegments(uint32_t pattern)
{
    /* Common Anode: LOW = segment ON, HIGH = segment OFF */
    /* Clear segments that should be ON (in pattern) */
    PORT_GroupClear(PORT_GROUP_0, pattern & ALL_SEGMENTS);
    /* Set segments that should be OFF (not in pattern) */
    PORT_GroupSet(PORT_GROUP_0, (~pattern) & ALL_SEGMENTS);
}

static void AllSegmentsOff(void)
{
    /* All segments OFF (HIGH for common anode) */
    PORT_GroupSet(PORT_GROUP_0, ALL_SEGMENTS);
}

void SevenSeg_Init(void)
{
    /* Turn off both COMs */
    COM1_AL_Clear();
    COM2_AL_Clear();

    /* Set segment pins as output */
    SegmentPins_SetOutput();

    /* All segments off */
    AllSegmentsOff();

    /* Initialize values */
    tensValue = 0;
    unitsValue = 0;
    currentDigit = 0;
}

void SevenSeg_SetValue(uint8_t value)
{
    if (value > 99U)
    {
        value = 99U;
    }
    tensValue = value / 10U;
    unitsValue = value % 10U;
}

void SevenSeg_Refresh(void)
{
    /* Turn off both COMs first (blank during transition) */
    COM1_AL_Clear();
    COM2_AL_Clear();

    /* Set segment pins as output */
    SegmentPins_SetOutput();

    if (currentDigit == 0U)
    {
        /* Display right digit (units) on COM1_AL */
        WriteSegments(digitPatterns[unitsValue]);
        COM1_AL_Set();
        currentDigit = 1U;
    }
    else
    {
        /* Display left digit (tens) on COM2_AL */
        WriteSegments(digitPatterns[tensValue]);
        COM2_AL_Set();
        currentDigit = 0U;
    }
}

void SevenSeg_Off(void)
{
    /* Turn off both COMs */
    COM1_AL_Clear();
    COM2_AL_Clear();

    /* All segments off */
    AllSegmentsOff();
}

void SevenSeg_SegmentPinsToInput(void)
{
    /* Turn off display first */
    COM1_AL_Clear();
    COM2_AL_Clear();

    /* Set segment pins as input for other usage */
    SegmentPins_SetInput();
}
