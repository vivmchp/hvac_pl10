/*******************************************************************************
  Switch Scanning Header

  File Name:
    switch.h

  Summary:
    Switch scanning using shared segment pins.

  Description:
    Scans switches on segment pins (L_S1_B to L_S7_C, excluding L_S0_A).
    LED_T must be LOW during scan. Internal pullup enabled for scanning.
    When switch pressed, pin reads LOW.
*******************************************************************************/

#ifndef SWITCH_H
#define SWITCH_H

#include "definitions.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Switch bit definitions */
#define SW_S1_B     (1U << 0U)
#define SW_S2_F     (1U << 1U)
#define SW_S3_G     (1U << 2U)
#define SW_S4_DP    (1U << 3U)
#define SW_S5_E     (1U << 4U)
#define SW_S6_D     (1U << 5U)
#define SW_S7_C     (1U << 6U)

void Switch_Init(void);
void Switch_Scan(void);
uint8_t Switch_GetState(void);
bool Switch_IsPressed(uint8_t switchMask);

#ifdef __cplusplus
}
#endif

#endif /* SWITCH_H */
