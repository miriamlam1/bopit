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
char* tasks[] = {"PRESS BUTTON 1.1", "PRESS BUTTON 1.4", "SCREAM", "PRESS KEYPAD"};

void print_task(uint16_t rando){
    uint16_t task = rando % CHOICES;
    Clear_LCD();
    Write_word_LCD("TASK: ");
    Write_word_LCD(tasks[task]);
        printf("task: %s\n", tasks[task]);
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
        printf("LOSS\n");
}

void print_score(){
    line_LCD(2); //move to the second line of LCD
    Write_word_LCD("SCORE: ");
        printf("\n score: ");
    char scoreword[4];
    sprintf(scoreword, "%d", score);
    Write_word_LCD(scoreword); //write score to LCD
        printf("%d\n", score);

    score += 1; //everytime func gets called they pass a level
}
