/* P3.c
 *  Created on: May 28, 2020
 *      Author: miriam
 */

#include "A7.h"
#include "A3.h"
#include "A4.h"
#include "P3.h"
#include "LEDs.h"
#include "LCD.h"
#include <stdio.h>
#include <stdlib.h>

uint8_t win;
uint16_t timer_threshold = STARTING_TIME;

volatile uint16_t timer_count;

void init_button(){
    P1->DIR &= ~(BIT1 | BIT4); //input
    P1->IES |= (BIT1 | BIT4);
    P1->IFG &= ~(BIT1 | BIT4);
    P1->IE |= (BIT1 | BIT4);
    P1->REN |= (BIT1 | BIT4);
    P1->OUT |= (BIT1 | BIT4);
    NVIC->ISER[1] = 1 <<((PORT1_IRQn)&31);
}

uint8_t random_task(uint16_t rando){
    win = 0;
    uint16_t keypad_rand = 0;

    switch(rando % CHOICES){
        case BUTTON11:
            P1->IE |= BIT1;
            break;
        case KEYPAD:
            keypad_rand = rand() % 12;
            return game_keypad(keypad_rand);
        case MICROPHONE:
            win = 1;
            break;
        case BUTTON14:
            P1->IE |= BIT4;
            break;
    }

    green_led_off();
    print_task(rando,keypad_rand);

    while(timer_count < timer_threshold){
        if (win == 1){
            timer_threshold = (timer_threshold*100)/110; // make 10% faster each time
            timer_count = 0;
            return win;
        }
        sendto_DAC(4095 - (1200 * timer_count / timer_threshold));
    }

    // LOSS:
    timer_count = 0;
    timer_threshold = STARTING_TIME;
    return 0;
}

uint8_t game_keypad(uint16_t button){
    print_task(KEYPAD,button);
    while(timer_count < timer_threshold){
        if (getKeyVal() == (button+0x30)){
            timer_threshold = (timer_threshold*100)/110; // make 10% faster each time
            timer_count = 0;
            return 1;
        }
        sendto_DAC(4095 - (1200 * timer_count / timer_threshold));
        }
    return 0;
}

void PORT1_IRQHandler(void){

    if(P1->IFG & (BIT1 | BIT4)){
        printf("WIN\n");
        win = 1;
        // button press
    }
    P1->IFG &= ~(BIT1 | BIT4);
    P1->IE &= ~(BIT1 | BIT4); // disable interrupts
}

