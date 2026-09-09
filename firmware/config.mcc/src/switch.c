/*******************************************************************************
  Switch Scanning Source

  File Name:
    switch.c

  Summary:
    Switch scanning using shared segment pins.

  Description:
    Scans switches on segment pins (L_S1_B to L_S7_C, excluding L_S0_A).
    LED_T driven LOW during scan. Internal pullup enabled.
    Switch pressed = pin LOW, Switch released = pin HIGH (pullup).

    Switch pin mapping:
      L_S1_B  - PA00 - SW_S1_B
      L_S2_F  - PA04 - SW_S2_F
      L_S3_G  - PA22 - SW_S3_G
      L_S4_DP - PA10 - SW_S4_DP
      L_S5_E  - PA11 - SW_S5_E
      L_S6_D  - PA18 - SW_S6_D
      L_S7_C  - PA19 - SW_S7_C
*******************************************************************************/

#include "switch.h"

/* Pin definitions */
#define PIN_S1_B    0U      /* PA00 */
#define PIN_S2_F    4U      /* PA04 */
#define PIN_S3_G    22U     /* PA22 */
#define PIN_S4_DP   10U     /* PA10 */
#define PIN_S5_E    11U     /* PA11 */
#define PIN_S6_D    18U     /* PA18 */
#define PIN_S7_C    19U     /* PA19 */

/* Mask for all switch pins (excludes L_S0_A which is display only) */
#define SWITCH_PIN_MASK ((1U << PIN_S1_B) | (1U << PIN_S2_F) | (1U << PIN_S3_G) | \
                         (1U << PIN_S4_DP) | (1U << PIN_S5_E) | (1U << PIN_S6_D) | \
                         (1U << PIN_S7_C))

static uint8_t switchState = 0;
static uint8_t switchDebounce = 0;

#define DEBOUNCE_COUNT  3U  /* Require 3 consecutive reads to confirm press */

static void SwitchPins_InputWithPullup(void)
{
    /* Set switch pins as input */
    PORT_REGS->GROUP[0].PORT_DIRCLR = SWITCH_PIN_MASK;

    /* Enable input buffer and pullup for each switch pin */
    PORT_REGS->GROUP[0].PORT_PINCFG[PIN_S1_B]  |= (PORT_PINCFG_INEN_Msk | PORT_PINCFG_PULLEN_Msk);
    PORT_REGS->GROUP[0].PORT_PINCFG[PIN_S2_F]  |= (PORT_PINCFG_INEN_Msk | PORT_PINCFG_PULLEN_Msk);
    PORT_REGS->GROUP[0].PORT_PINCFG[PIN_S3_G]  |= (PORT_PINCFG_INEN_Msk | PORT_PINCFG_PULLEN_Msk);
    PORT_REGS->GROUP[0].PORT_PINCFG[PIN_S4_DP] |= (PORT_PINCFG_INEN_Msk | PORT_PINCFG_PULLEN_Msk);
    PORT_REGS->GROUP[0].PORT_PINCFG[PIN_S5_E]  |= (PORT_PINCFG_INEN_Msk | PORT_PINCFG_PULLEN_Msk);
    PORT_REGS->GROUP[0].PORT_PINCFG[PIN_S6_D]  |= (PORT_PINCFG_INEN_Msk | PORT_PINCFG_PULLEN_Msk);
    PORT_REGS->GROUP[0].PORT_PINCFG[PIN_S7_C]  |= (PORT_PINCFG_INEN_Msk | PORT_PINCFG_PULLEN_Msk);

    /* Set output register HIGH to enable pull-up (not pull-down) */
    PORT_REGS->GROUP[0].PORT_OUTSET = SWITCH_PIN_MASK;
}

static uint8_t ReadSwitchPins(void)
{
    uint32_t portIn;
    uint8_t result = 0;

    portIn = PORT_REGS->GROUP[0].PORT_IN;

    /* Read each pin - LOW = pressed, so invert logic */
    if ((portIn & (1U << PIN_S1_B)) == 0U)  result |= SW_S1_B;
    if ((portIn & (1U << PIN_S2_F)) == 0U)  result |= SW_S2_F;
    if ((portIn & (1U << PIN_S3_G)) == 0U)  result |= SW_S3_G;
    if ((portIn & (1U << PIN_S4_DP)) == 0U) result |= SW_S4_DP;
    if ((portIn & (1U << PIN_S5_E)) == 0U)  result |= SW_S5_E;
    if ((portIn & (1U << PIN_S6_D)) == 0U)  result |= SW_S6_D;
    if ((portIn & (1U << PIN_S7_C)) == 0U)  result |= SW_S7_C;

    return result;
}

void Switch_Init(void)
{
    switchState = 0;
    switchDebounce = 0;
}

void Switch_Scan(void)
{
    volatile uint16_t delay;
    uint8_t currentRead;

    /* Turn off display COMs to avoid conflict */
    COM1_AL_Clear();
    COM2_AL_Clear();

    /* Keep LED_T HIGH so LEDs don't affect switch scanning */
    LED_T_Set();

    /* Set switch pins as input with pullup */
    SwitchPins_InputWithPullup();

    /* Delay for pullup to settle */
    for (delay = 0; delay < 500U; delay++)
    {
        __NOP();
    }

    /* Read switch states */
    currentRead = ReadSwitchPins();

    /* Simple debounce: only accept if same as previous read */
    if (currentRead == switchDebounce)
    {
        switchState = currentRead;
    }
    switchDebounce = currentRead;
}

uint8_t Switch_GetState(void)
{
    return switchState;
}

bool Switch_IsPressed(uint8_t switchMask)
{
    return ((switchState & switchMask) != 0U);
}
