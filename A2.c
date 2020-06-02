#include "msp.h"
#include <stdint.h>
#include "A2.h"
#include <stdio.h>

// change the MSP432 MCLK using the DCO
void set_DCO(int freq){
    CS->KEY = CS_KEY_VAL; //unlock CS to access registers
    CS->CTL0 = 0; //reset CS

    switch(freq){
        case FREQ_1_5_MHz:
            CS->CTL0 = CS_CTL0_DCORSEL_0;
            break;
        case FREQ_6_MHz:
            CS->CTL0 = CS_CTL0_DCORSEL_2;
            break;
        case FREQ_12_MHz:
            CS->CTL0 = CS_CTL0_DCORSEL_3;
            break;
        case FREQ_24_MHz:
            CS->CTL0 = CS_CTL0_DCORSEL_4;
            break;
        default:
            CS->CTL0 = CS_CTL0_DCORSEL_1; //default 3 MHz
    }

    CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3; //enabling DCO->MCLK in CTL1
    CS->KEY = 0; //lock CS
}

// delay in uS
void delay_us(int delay)
{
    int i, j;
    int freq = (CS->CTL0) >> 16; //0x10000;
    switch(freq)
    {
    case 0:
        delay = delay/19-2;
        freq = 1.5;
        break;
    case 1:
        delay = delay/17;
        freq = 3;
        break;
    case 2:
        delay = delay/14;
        freq = 6;
        break;
    case 3:
        delay = delay/12;
        freq = 12;
        break;
    case 4:
        delay = delay/11;
        freq = 24;
        break;
    default:
        delay = delay/21;
        freq = 3;
    }
    for(i=0; i<delay;i++){ // # us
        for(j=0;j<freq;j++); // # 1 us
    }
}
