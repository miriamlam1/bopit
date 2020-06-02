//A4.c
#include "msp.h"
#include "A3.h"
#include "A2.h"
#include "A4.h"
#include <stdio.h>
#include <math.h>

#define ROWS 4 //number of ROWS
#define COLS 3 //number of COLS

void keypad_init(){
    PORT_KEYPAD_ROW->DIR &= ~(ROW0 | ROW1 | ROW2 | ROW3); // set ROWS to inputs
    PORT_KEYPAD_ROW->REN |= (ROW0 | ROW1 | ROW2 | ROW3);  // resistor enable
    PORT_KEYPAD_ROW->OUT &= ~(ROW0 | ROW1 | ROW2 | ROW3); // pulling down
}

uint16_t getKeyVal(){
    int row, col;
    int keypad[ROWS][COLS]={{BUTTON1,BUTTON2,BUTTON3},
                    {BUTTON4,BUTTON5,BUTTON6},
                    {BUTTON7,BUTTON8,BUTTON9},
                    {BUTTON_STAR,BUTTON0,BUTTON_POUND}};

    PORT_KEYPAD_COL->DIR |= (COL0 | COL1 | COL2);               // COLS outputs (set dir to 1)
    PORT_KEYPAD_COL->OUT |= (COL0 | COL1 | COL2);               // pulling up
    row = (PORT_KEYPAD_ROW->IN) & (ROW0 | ROW1 | ROW2 | ROW3);  // reading in the ROWS

    if (row == 0){ // no button was pressed
        return NO_BUTTON_PRESS;
    }

    for (col = 0; col < COLS; col++){                              // COLS = 3 (in #def)
        PORT_KEYPAD_COL->OUT &= ~(COL0 | COL1 | COL2);             // reset COLS
        PORT_KEYPAD_COL->OUT |= (COL0 << col);                     // see which col is going high or low
        row = (PORT_KEYPAD_ROW->IN) & (ROW0 | ROW1 | ROW2 | ROW3); // checking to see if row is high
        if (row != 0){                                             // means a button was detected
            break;                                                 // break loop to find what was pressed
        }
    }
    if (col == 3){                  // no button has been pressed
        return NO_BUTTON_PRESS;
    }
    row = log2(row)-log2(ROW0);     // convert row to row index
    return keypad[row][col];
}

uint8_t sent_to_LCD(){
    uint8_t button;
    while(1){
        button = getKeyVal();           // poll for keypress
        if(button != NO_BUTTON_PRESS){  // key was pressed
            while(getKeyVal()!=NO_BUTTON_PRESS){
                //wait for button to be released
            }
            return button;
        }
    }
}

