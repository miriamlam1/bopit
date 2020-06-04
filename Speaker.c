/*
 * Speaker.c
 */

#include "msp.h"
#include "A9.h"
#include  "Speaker.h"

uint16_t microphone_sensor(){
    uint32_t data = get_conversion_results();
    uint16_t volts = voltage_conversion(data);
    uint16_t flag = 0; //init to zero to in indicate no noise

    if(data >= THRESHOLD){
        flag = 1;
    }else{
        flag = 0;
    }

    return flag;
}
