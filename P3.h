/*
 * P3.h
 *
 *  Created on: May 28, 2020
 *      Author: miriam
 */

#ifndef P3_H_
#define P3_H_

#define CHOICES 5
#define STARTING_TIME 10000
#define BUTTON11 0
#define KEYPAD 3
#define MICROPHONE 2
#define BUTTON14 1
#define EXTERNALBUTTON 4

void init_button();
void init_button_external();
uint8_t random_task(uint16_t rand);
uint8_t game_keypad(uint16_t button);

#endif /* P3_H_ */
