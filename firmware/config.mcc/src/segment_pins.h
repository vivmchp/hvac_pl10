/*******************************************************************************
  Segment Display Pin Control Header

  File Name:
    segment_pins.h

  Summary:
    Functions to configure segment display pins as input/output with pullup.

  Description:
    This file provides functions to configure the segment display pins
    (L_S0_A through L_S7_C and L_S4_DP) as input, output, or with pullup enabled.
*******************************************************************************/

#ifndef SEGMENT_PINS_H
#define SEGMENT_PINS_H

#include "definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

void SegmentPins_OutputEnable(void);
void SegmentPins_InputEnable(void);
void SegmentPins_PullupEnable(void);

void SegmentPin_L_S0_A_OutputEnable(void);
void SegmentPin_L_S0_A_InputEnable(void);
void SegmentPin_L_S0_A_PullupEnable(void);

void SegmentPin_L_S1_B_OutputEnable(void);
void SegmentPin_L_S1_B_InputEnable(void);
void SegmentPin_L_S1_B_PullupEnable(void);

void SegmentPin_L_S2_F_OutputEnable(void);
void SegmentPin_L_S2_F_InputEnable(void);
void SegmentPin_L_S2_F_PullupEnable(void);

void SegmentPin_L_S3_G_OutputEnable(void);
void SegmentPin_L_S3_G_InputEnable(void);
void SegmentPin_L_S3_G_PullupEnable(void);

void SegmentPin_L_S4_DP_OutputEnable(void);
void SegmentPin_L_S4_DP_InputEnable(void);
void SegmentPin_L_S4_DP_PullupEnable(void);

void SegmentPin_L_S5_E_OutputEnable(void);
void SegmentPin_L_S5_E_InputEnable(void);
void SegmentPin_L_S5_E_PullupEnable(void);

void SegmentPin_L_S6_D_OutputEnable(void);
void SegmentPin_L_S6_D_InputEnable(void);
void SegmentPin_L_S6_D_PullupEnable(void);

void SegmentPin_L_S7_C_OutputEnable(void);
void SegmentPin_L_S7_C_InputEnable(void);
void SegmentPin_L_S7_C_PullupEnable(void);

#ifdef __cplusplus
}
#endif

#endif /* SEGMENT_PINS_H */
