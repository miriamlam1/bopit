/*
 * Speaker.c
 */

#include "msp.h"
#include "A9.h"
#include "Speaker.h"
#include <stdio.h>

uint16_t microphone_sensor(){
    uint16_t data = 0;
    if(get_global_flag())
        {
            data = get_conversion_results();
            set_global_flag(0);
            ADC14 -> CTL0 |= ADC14_CTL0_SC; //initiate a new sample for the ADC14
            ADC14 -> IER0 |= ADC14_IER0_IE0;
        }
    if (data>= THRESHOLD)
        return 1;
    return 0;
}
