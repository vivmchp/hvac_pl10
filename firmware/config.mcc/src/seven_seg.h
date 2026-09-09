/*******************************************************************************
  7-Segment Display Driver Header

  File Name:
    seven_seg.h

  Summary:
    Driver for 2-digit 7-segment display with multiplexing.

  Description:
    This file provides functions to drive a 2-digit common anode 7-segment
    display using multiplexing. COM2_AL is left digit (tens), COM1_AL is
    right digit (units). Call SevenSeg_Refresh() from timer callback at 4ms.
*******************************************************************************/

#ifndef SEVEN_SEG_H
#define SEVEN_SEG_H

#include "definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

void SevenSeg_Init(void);
void SevenSeg_SetValue(uint8_t value);
void SevenSeg_Refresh(void);
void SevenSeg_Off(void);
void SevenSeg_SegmentPinsToInput(void);

#ifdef __cplusplus
}
#endif

#endif /* SEVEN_SEG_H */
