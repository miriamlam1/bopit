/*
 * LEDs.c
 * All functions responsible for LED activity throughout project.
 * P1.0 - RED LED
 * P2.0 - RED LED
 * P2.1 - GREEN LED
 * P2.2 - BLUE LED
 */
#include "msp.h"
#include "A2.h"
#include <stdio.h>
#include <stdlib.h>

void init_LEDs()
{
    /*LED 1*/
    P1->SEL1 &= ~BIT0; /* configure P1.0 as simple I/O */
    P1->SEL0 &= ~BIT0; /* configure P1.0 as simple I/O */
    P1->DIR  |= BIT0;  /* configure P1.0 set as output pin */
}

void green_led_on(){
    P2->SEL1 &= ~0x02; /* configure P2.1 as simple I/O */
    P2->SEL0 &= ~0x07; /* configure P2.1 as simple I/O*/
    P2->DIR |= BIT1; /* P2.1 set as output pin */
    P2->OUT |= BIT1; //display green light
}

void green_led_off(){
    P2->OUT &= ~BIT1; // green light off
}

void when_lost(){
        uint16_t BIT;
        uint16_t bits[3] = {0x001,0x002,0x004};

        P1->OUT |= BIT0; //turning red LED on
        delay_us(100000);

        P1->OUT &= ~BIT0; //turning red LED off

        /*picks a random numbers from 0 to 2 */
        BIT = bits[rand() % 3];

        /*LED 2*/
        P2->SEL1 &= ~(BIT); /* configure P2.0/1/2 as simple I/O */
        P2->SEL0 &= ~(BIT); /* configure P2.0/1/2 as simple I/O*/
        P2->DIR |= (BIT); /* P2.0/1/2 set as output pin */
        P2->OUT |= BIT; //display green light

        delay_us(100000); //delay 1.5s
        P2->OUT &= ~BIT; // green light off
}
