/*
 * A9.c
 */

#include "msp.h"
#include "A9.h"

uint8_t received = 0;

/* 14-bit -> 3FFF = 16383
 * */
void ADC_init()
{
    P5 -> SEL0 |= BIT4; //config. A1 pin for ADC tertiary mode for adc
    P5 -> SEL1 |= BIT4;

    P5 -> DIR |= BIT4; // set input
    P5 -> OUT |= BIT4; // out on

    ADC14 -> CTL0 &= ~ADC14_CTL0_ENC; //ADC14 disable while configure

    ADC14 -> CTL0 |= ADC14_CTL0_ON //ADC14 on - reset is removed
                  |  ADC14_CTL0_SSEL_4 //SMCLK
                  | ADC14_CTL0_SHP // internal sample timer
                  | ADC14_CTL0_SHT0_0; // sample every 4 clock cycles

    ADC14 -> CTL1 |= ADC14_CTL1_RES__14BIT; //conversion result resolution
    ADC14 -> MCTL[0] |= ADC14_MCTLN_INCH_1; //input channel select bc A1
    ADC14 -> CTL0 |= ADC14_CTL0_ENC; //must be set to 1 before any conv.enable adc to start running
    ADC14 -> IER0 |= ADC14_IER0_IE0; //where to write in memory when interrupt
    NVIC -> ISER[0] = 1 <<(ADC14_IRQn & 31); //set NVIC interrupt

    __enable_irq();  //enabled global interrupts
    ADC14 -> CTL0 |= ADC14_CTL0_SC; //start conversion
}

uint32_t get_conversion_results() // returns weird number look at p62 -> voltage you want
{
    uint32_t data;// = 0;
    data = ADC14 -> MEM[0]; //conversion results are written to ADC14MEM
    return data;
}
uint16_t voltage_conversion(uint16_t data){ //
    uint16_t voltage;
    voltage = 1000*(data - 150)/4980; // formula
    return voltage;
}

void transmit_word(uint16_t word){ // 999 for 1v
    if (word <= 0 || word > 4000)
        word = 0;
    transmit_data(word/1000 + '0'); //digit
    delay_us(5000);
    transmit_data('.');
    delay_us(5000);
    transmit_data((word /100)%10 + '0');
    delay_us(5000);
    transmit_data((word /10)%10 + '0');
    delay_us(5000);
    transmit_data(' ');
    delay_us(5000);
}

void set_global_flag(uint8_t val){
    received = val;
}

uint8_t get_global_flag(){
    return received;
}

void ADC14_IRQHandler(){
    ADC14 -> IER0 &= ~ADC14_IER0_IE0;
    received = 1;
}
