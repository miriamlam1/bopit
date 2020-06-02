/*******************************************************************************
 * HEADER FILES
 ******************************************************************************/
#include "msp.h"
#include "A2.h"
/*******************************************************************************
 * LOCAL CONSTANTS AND MACROS (PRIVATE TO MODULE)
 ******************************************************************************/
#define PORT_MCLK_OUT (P4)
#define BITM_MCLK_OUT (BIT3)
/*******************************************************************************
 * GLOBAL FUNCTIONS (PUBLIC TO OTHER MODULES)
 ******************************************************************************/
/* @brief : sets the MCLK using the digitally controlled oscillator
 * to 24MHz and the SMCLK to 12MHz
 * @param : frequency bitmask (macro defined in dco.h)
 * @return: N/A
 */
void setup_DCO(void)
{
    /* Setting up Master CLK based on freq_sel */
    CS->KEY = CS_KEY_VAL; // unlocks CS
    CS->CTL0 = FREQ_24_MHz;
    CS->CTL1 |= CS_CTL1_SELM__DCOCLK | CS_CTL1_DIVM__1; // MCLK = 24MHz
    CS->CTL1 |= CS_CTL1_SELS__DCOCLK | CS_CTL1_DIVS__2; // SMCLK = 12MHz
    CS->KEY = 0; // locks CS
}
/* @brief : maps MCLK to P4.3 for oscilloscope verification
 * @param : N/A
 * @return: N/A
 */
void mapout_MCLK(void)
{
    PORT_MCLK_OUT ->DIR |= BITM_MCLK_OUT;
    PORT_MCLK_OUT ->SEL0 |= BITM_MCLK_OUT;
    PORT_MCLK_OUT ->SEL1 &= ~BITM_MCLK_OUT;
}
