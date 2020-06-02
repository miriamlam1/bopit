/*
 * A7.h
 */
#include "msp.h"

#ifndef A7_H_
#define A7_H_

#define TWOV 2482 //4096/3.3 *2
#define NOTCS BIT1
#define SCLK BIT6
#define MOSI BIT5
#define GAIN BIT5
#define SHDN BIT4
#define INCREMENT 10

void triangle();
void square();
void DAC_init();
void sendto_DAC(uint16_t data);

#endif /* A7_H_ */
