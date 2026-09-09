/*******************************************************************************
  Segment Display Pin Control Source

  File Name:
    segment_pins.c

  Summary:
    Functions to configure segment display pins as input/output with pullup.

  Description:
    This file provides functions to configure the segment display pins
    (L_S0_A through L_S7_C and L_S4_DP) as input, output, or with pullup enabled.
*******************************************************************************/

#include "segment_pins.h"

#define SEGMENT_PIN_MASK    ((1U << 0U)  |  /* L_S1_B  - PA00 */ \
                             (1U << 4U)  |  /* L_S2_F  - PA04 */ \
                             (1U << 5U)  |  /* L_S0_A  - PA05 */ \
                             (1U << 10U) |  /* L_S4_DP - PA10 */ \
                             (1U << 11U) |  /* L_S5_E  - PA11 */ \
                             (1U << 18U) |  /* L_S6_D  - PA18 */ \
                             (1U << 19U) |  /* L_S7_C  - PA19 */ \
                             (1U << 22U))   /* L_S3_G  - PA22 */

/* All pins functions */
void SegmentPins_OutputEnable(void)
{
    PORT_GroupOutputEnable(PORT_GROUP_0, SEGMENT_PIN_MASK);
}

void SegmentPins_InputEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, SEGMENT_PIN_MASK);
}

void SegmentPins_PullupEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, SEGMENT_PIN_MASK);

    PORT_REGS->GROUP[0].PORT_PINCFG[0]  |= PORT_PINCFG_PULLEN_Msk;
    PORT_REGS->GROUP[0].PORT_PINCFG[4]  |= PORT_PINCFG_PULLEN_Msk;
    PORT_REGS->GROUP[0].PORT_PINCFG[5]  |= PORT_PINCFG_PULLEN_Msk;
    PORT_REGS->GROUP[0].PORT_PINCFG[10] |= PORT_PINCFG_PULLEN_Msk;
    PORT_REGS->GROUP[0].PORT_PINCFG[11] |= PORT_PINCFG_PULLEN_Msk;
    PORT_REGS->GROUP[0].PORT_PINCFG[18] |= PORT_PINCFG_PULLEN_Msk;
    PORT_REGS->GROUP[0].PORT_PINCFG[19] |= PORT_PINCFG_PULLEN_Msk;
    PORT_REGS->GROUP[0].PORT_PINCFG[22] |= PORT_PINCFG_PULLEN_Msk;

    PORT_GroupSet(PORT_GROUP_0, SEGMENT_PIN_MASK);
}

/* L_S0_A - PA05 */
void SegmentPin_L_S0_A_OutputEnable(void)
{
    PORT_GroupOutputEnable(PORT_GROUP_0, (1U << 5U));
}

void SegmentPin_L_S0_A_InputEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, (1U << 5U));
}

void SegmentPin_L_S0_A_PullupEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, (1U << 5U));
    PORT_REGS->GROUP[0].PORT_PINCFG[5] |= PORT_PINCFG_PULLEN_Msk;
    PORT_GroupSet(PORT_GROUP_0, (1U << 5U));
}

/* L_S1_B - PA00 */
void SegmentPin_L_S1_B_OutputEnable(void)
{
    PORT_GroupOutputEnable(PORT_GROUP_0, (1U << 0U));
}

void SegmentPin_L_S1_B_InputEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, (1U << 0U));
}

void SegmentPin_L_S1_B_PullupEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, (1U << 0U));
    PORT_REGS->GROUP[0].PORT_PINCFG[0] |= PORT_PINCFG_PULLEN_Msk;
    PORT_GroupSet(PORT_GROUP_0, (1U << 0U));
}

/* L_S2_F - PA04 */
void SegmentPin_L_S2_F_OutputEnable(void)
{
    PORT_GroupOutputEnable(PORT_GROUP_0, (1U << 4U));
}

void SegmentPin_L_S2_F_InputEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, (1U << 4U));
}

void SegmentPin_L_S2_F_PullupEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, (1U << 4U));
    PORT_REGS->GROUP[0].PORT_PINCFG[4] |= PORT_PINCFG_PULLEN_Msk;
    PORT_GroupSet(PORT_GROUP_0, (1U << 4U));
}

/* L_S3_G - PA22 */
void SegmentPin_L_S3_G_OutputEnable(void)
{
    PORT_GroupOutputEnable(PORT_GROUP_0, (1U << 22U));
}

void SegmentPin_L_S3_G_InputEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, (1U << 22U));
}

void SegmentPin_L_S3_G_PullupEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, (1U << 22U));
    PORT_REGS->GROUP[0].PORT_PINCFG[22] |= PORT_PINCFG_PULLEN_Msk;
    PORT_GroupSet(PORT_GROUP_0, (1U << 22U));
}

/* L_S4_DP - PA10 */
void SegmentPin_L_S4_DP_OutputEnable(void)
{
    PORT_GroupOutputEnable(PORT_GROUP_0, (1U << 10U));
}

void SegmentPin_L_S4_DP_InputEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, (1U << 10U));
}

void SegmentPin_L_S4_DP_PullupEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, (1U << 10U));
    PORT_REGS->GROUP[0].PORT_PINCFG[10] |= PORT_PINCFG_PULLEN_Msk;
    PORT_GroupSet(PORT_GROUP_0, (1U << 10U));
}

/* L_S5_E - PA11 */
void SegmentPin_L_S5_E_OutputEnable(void)
{
    PORT_GroupOutputEnable(PORT_GROUP_0, (1U << 11U));
}

void SegmentPin_L_S5_E_InputEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, (1U << 11U));
}

void SegmentPin_L_S5_E_PullupEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, (1U << 11U));
    PORT_REGS->GROUP[0].PORT_PINCFG[11] |= PORT_PINCFG_PULLEN_Msk;
    PORT_GroupSet(PORT_GROUP_0, (1U << 11U));
}

/* L_S6_D - PA18 */
void SegmentPin_L_S6_D_OutputEnable(void)
{
    PORT_GroupOutputEnable(PORT_GROUP_0, (1U << 18U));
}

void SegmentPin_L_S6_D_InputEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, (1U << 18U));
}

void SegmentPin_L_S6_D_PullupEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, (1U << 18U));
    PORT_REGS->GROUP[0].PORT_PINCFG[18] |= PORT_PINCFG_PULLEN_Msk;
    PORT_GroupSet(PORT_GROUP_0, (1U << 18U));
}

/* L_S7_C - PA19 */
void SegmentPin_L_S7_C_OutputEnable(void)
{
    PORT_GroupOutputEnable(PORT_GROUP_0, (1U << 19U));
}

void SegmentPin_L_S7_C_InputEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, (1U << 19U));
}

void SegmentPin_L_S7_C_PullupEnable(void)
{
    PORT_GroupInputEnable(PORT_GROUP_0, (1U << 19U));
    PORT_REGS->GROUP[0].PORT_PINCFG[19] |= PORT_PINCFG_PULLEN_Msk;
    PORT_GroupSet(PORT_GROUP_0, (1U << 19U));
}
