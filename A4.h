#ifndef A4_H_
#define A4_H_

#define COL0 BIT0 // P5.0 KeyPadPin5
#define COL1 BIT1 // P5.1 KeyPadPin6
#define COL2 BIT2 // P5.2 KeyPadPin7

#define ROW0 BIT4 // P6.4 KeyPadPin1
#define ROW1 BIT5 // P6.5 KeyPadPin2
#define ROW2 BIT6 // P6.6 KeyPadPin3
#define ROW3 BIT7 // P6.7 KeyPadPin4

#define BUTTON0 0x30
#define BUTTON1 0x31
#define BUTTON2 0x32
#define BUTTON3 0x33
#define BUTTON4 0x34
#define BUTTON5 0x35
#define BUTTON6 0x36
#define BUTTON7 0x37
#define BUTTON8 0x38
#define BUTTON9 0x39
#define BUTTON9 0x39
#define BUTTON_POUND 0x23
#define BUTTON_STAR 0x2A
#define NO_BUTTON_PRESS 0xFF

#define PORT_KEYPAD_ROW P6 //use P5 for ROW
#define PORT_KEYPAD_COL P5 //use P6 for COL

void keypad_init();
uint16_t getKeyVal();
uint8_t sent_to_LCD();

#endif /* A4_H_ */
