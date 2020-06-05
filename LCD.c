/*
 * LCD.c - This file contains all functions for the LCD used in final project.
 */

#include "msp.h"
#include "A3.h"
#include "LCD.h"
#include "P3.h"
#include <stdio.h>
#include <string.h>

char score = 0; //starting score is zero
char* tasks[] = {"PRESS BTN RIGHT ", // P1.1
                 "PRESS BTN LEFT ", // P1.4
                 "MAKE NOISE    ",
                 "PRESS KEYPAD ",
                 "PRESS EXTERNAL BTN"};

void print_task(uint16_t rando, uint16_t keypad_rand){
    uint16_t task = rando % CHOICES;
    line_LCD(1);
    Write_word_LCD("TASK: ");
    Write_word_LCD(tasks[task]);
    if (task == KEYPAD){
        char button_no[2];
        sprintf(button_no, "%d  ", keypad_rand);
        Write_word_LCD(button_no);
    }
}

void game_over(){
    Clear_LCD();
    Write_word_LCD("GAME OVER");
    line_LCD(2);
    Write_word_LCD("FINAL SCORE: ");

    char scoreword[4];
    sprintf(scoreword, "%d", score);
    Write_word_LCD(scoreword); //write score to LCD

    score = 0;
}

void print_score(){
    score += 1; //everytime func gets called they pass a level
    line_LCD(2); //move to the second line of LCD
    Write_word_LCD("SCORE: ");

    char scoreword[4];
    sprintf(scoreword, "%d", score);
    Write_word_LCD(scoreword); //write score to LCD
}
