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
#include "speaker.h"

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

void init_button_external(){
    P3->DIR &= ~BIT6; //input
    P3->IES |= BIT6;
    P3->IFG &= ~BIT6;
    P3->IE |= BIT6;
    P3->REN |= BIT6;
    P3->OUT |= BIT6;
    NVIC->ISER[1] = 1 <<((PORT3_IRQn)&31);
}

uint8_t random_task(uint16_t rando){
    win = 0;
    //uint16_t keypad_rand = 0;
    //uint16_t current_task = 4;
    uint16_t keypad_rand = 0;
    uint16_t current_task = rando % CHOICES;

    switch(current_task){
        case BUTTON11:
            P1->IE |= BIT1;
            break;
        case KEYPAD:
            keypad_rand = rand() % 10;
        case MICROPHONE:
            win = 1;
            break;
        case BUTTON14:
            P1->IE |= BIT4;
            break;
        case EXTERNALBUTTON:
            P3->IE |= BIT6;
            break;
    }

    green_led_off();
    print_task(rando,keypad_rand);

    while(timer_count < timer_threshold){
        if (current_task == KEYPAD){
            win = 0;
            if (getKeyVal() == (keypad_rand+0x30)){
                win = 1;
            }
        }
        else if (current_task == MICROPHONE){
            if (microphone_sensor() == 1)
                win = 1;
        }
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
    return win; // 0
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

void PORT3_IRQHandler(void){
    if(P3->IFG & BIT6){
        printf("button3 pressed\n");
        win = 1;
        // button press
    }
    P3->IFG &= ~BIT6;
    P3->IE &= ~BIT6; // disable interrupts
}

