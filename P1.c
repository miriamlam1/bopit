#include "msp.h"
#include "A3.h"
#include "A2.h"
#include "A4.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

void lock_setup(){
    Clear_LCD();
    Write_word_LCD("LOCKED");      // Display "LOCKED" on first line of LCD
    line_LCD(2);                   // Move to second line of LCD
    Write_word_LCD("ENTER KEY ");  // Display "ENTER KEY " on second line of LCD
}

int digit_counter(int num){            // Determines the num of digits in the default password
    int count = 0;
    while(num != 0){
        num/=10;
        count ++;
    }
    return count;
}

void blink_red(){
    P1->SEL1 &= ~BIT0; /* configure P1.0 as simple I/O */
    P1->SEL0 &= ~BIT0; /* configure P1.0 as simple I/O */
    P1->DIR  |= BIT0;  /* configure P1.0 set as output pin */

    int i;
    for(i =0; i< 7; i++) // 1.5 second total-ish
    {
        P1->OUT |= BIT0; //turning red LED on
        delay_us(100000);

        P1->OUT &= ~BIT0; //turning red LED off
        delay_us(100000);
    }
}

void green_leds(){
    P2->SEL1 &= ~0x02; /* configure P2.1 as simple I/O */
    P2->SEL0 &= ~0x07; /* configure P2.1 as simple I/O*/
    P2->DIR |= BIT1; /* P2.1 set as output pin */
    P2->OUT |= BIT1; //display green light
    delay_us(1500000); //delay 1.5s
    P2->OUT &= ~BIT1; // green light off
}

void lock(int pass){
    int current_key = 0;
    char button, i;
    int pass_length = digit_counter(pass);

    lock_setup();

    for(i=0;i<pass_length;i++){
        button = sent_to_LCD();
        if (button == BUTTON_STAR){
            return; //resets the lock
        }else{
            current_key += ((button-48)*pow(10,pass_length-1-i)); // add new button press to overall current password
            Write_char_LCD(button); // write current button to LCD
        }
    }
    line_LCD(1); // go back to first line of LCD
    if (current_key == pass){ // correct pass entered
        Write_word_LCD("UNLOCKED");
        //green_led();
    } else{// INCORRECT - still shows LOCKED
        blink_red();
    }
}
