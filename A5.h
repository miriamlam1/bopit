
#ifndef A5_H_
#define A5_H_
#include "msp.h"

extern volatile uint16_t timer_count;

void timer_A_init();
void PORT1_IRQHandler();
void TA0_0_IRQHandler();
void TA0_N_IRQHandler();


#endif /* A5_H_ */
