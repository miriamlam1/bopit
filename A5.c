/*
 * A5.c
 */
#include "A5.h"
#include "A7.h"
#include "msp.h"
#include "A2.h"

volatile uint16_t timer_count;

void timer_A_init(){
    P1->OUT &= ~BIT5; // probe P1.5
    P1->DIR |= BIT5; // output: 1

    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled
    TIMER_A0->CCR[0] = 30000; // set CCR0 to divide clock 3,000,000/2/

    TIMER_A0->CTL = TIMER_A_CTL_TASSEL_2 | // SMCLK
                    TIMER_A_CTL_MC_1;      // UP MODE

    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);   // set NVIC interrupt

    __enable_irq();     // Enable global interrupt
}

// Timer A0_0 interrupt service routine
void TA0_0_IRQHandler() {
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;  // Clear the CCR0 interrupt
    timer_count ++;
}

