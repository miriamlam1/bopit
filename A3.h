#ifndef A3_H_
#define A3_H_

#define PORT_RS_OUT (P3) //RS 3.0 (0=instruction 1= data)
#define PORT_RW_OUT (P3) //read/write 3.2 (0=write 1= read)
#define PORT_E_OUT (P3) //enable 3.3
#define PORT_DB_OUT (P4) //data 4
#define BITM_DB_OUT (BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7)

void Clear_LCD();
void Home_LCD();
void line_LCD(char line_no);
void Write_char_LCD(char c);
void Write_word_LCD(char* word);
void LCD_init();
void command_LCD(char command);
void nibble_write_command(unsigned char command);
void data_LCD(char data);
void nibble_write_data(unsigned char data);

#endif /* A3_H_ */

