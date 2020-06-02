#include "msp.h"
#include "A7.h"
#include <stdio.h>
#include <stdlib.h>
#include "A5.h"
#include "A9.h"
#include "A4.h"
#include "A2.h"
#include "A3.h"
#include "P3.h"
#include "LEDs.h"
#include "LCD.h"

void main(void){

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    set_DCO(FREQ_24_MHz);
    timer_A_init();
    ADC_init();
    keypad_init();
    LCD_init();
    init_button();
    DAC_init();

    __enable_irq();

    while(1){
        uint16_t rando = rand();
        if (random_task(rando) == 1){
            green_led_on();
            print_score();
        } else {
            game_over();
        }
    }

}
