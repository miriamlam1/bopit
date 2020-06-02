#include "msp.h"
#include "A3.h"
#include "A2.h"

void Clear_LCD(){
    command_LCD(0x01);
}

void Home_LCD(){
    command_LCD(0x02);
}

void line_LCD(char line_no){ //only enter 1 or 2
    if (line_no == 2){
        command_LCD(0xC0); //second line
    }
    else{ // line_no is 1
        command_LCD(0x80); //first line
    }
}

void Write_char_LCD(char c){
    data_LCD(c);
    delay_us(1000);
}

void Write_word_LCD(char* word){
    int i = 0;
    for (i = 0; word[i] != '\0'; i++)
    {
        Write_char_LCD(word[i]);
    }
}

void LCD_init(){
    PORT_RS_OUT -> DIR |= (BIT0 | BIT2 | BIT3); /*make pins RS = P3.0 RW = P3.2 E = P3.3 output*/
    PORT_DB_OUT -> DIR = BITM_DB_OUT; /*make P4 pins output for DBs*/

    delay_us(30000);
    nibble_write_command(0x30);
    delay_us(100000);   /*10000us = 10ms*/
    nibble_write_command(0x30);
    delay_us(100000);
    nibble_write_command(0x20);
    delay_us(100000);

    command_LCD(0x28); // set nibble, 4-bit data, 2-line, 5x7 font (Function Set)
    command_LCD(0x06); // entry mode set
    Clear_LCD(); // clear screen
    command_LCD(0x0F); // display on (DCB)
}

void command_LCD(char command){

    nibble_write_command(command & 0xF0); //upper bits
    nibble_write_command((command & 0x0F)<<4); //lower bits

    if (command <= 3){
        delay_us(1640); //1.64 ms - Clear Display & Display/ Cursor Home
    }
    else{
        delay_us(40); //40 us - Everything else
    }
}

void nibble_write_command(unsigned char command) // RS low RW low
{
    PORT_RS_OUT -> OUT &= ~(0x05); /*setting RS and RW (P3.0 and P3.2) */
    PORT_DB_OUT -> OUT = command; /*putting command on DBs*/
    PORT_E_OUT -> OUT |= BIT3;        /*sending E (P3.3) high to read DBs*/
    delay_us(0);

    PORT_E_OUT -> OUT &= ~BIT3;        /*sending E back low*/
}

void data_LCD(char data)
{
    nibble_write_data(data & 0xF0);
    nibble_write_data((data & 0x0F) << 4);
    delay_us(1000);
}

void nibble_write_data(unsigned char data) // RS high RW low
{
    PORT_RS_OUT -> OUT |= BIT0; /*setting RS high P3.0*/
    PORT_RW_OUT -> OUT &= ~BIT2;   /*setting RW (P3.2) low*/
    PORT_DB_OUT -> OUT = data;     /*putting command on DBs*/
    PORT_E_OUT -> OUT |= BIT3;         /*sending E (P3.3) high to read DBs*/
    delay_us(0);

    PORT_E_OUT -> OUT &= ~BIT3;        /*sending E back low*/
}
