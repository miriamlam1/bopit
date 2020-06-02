/*
 * provided.h
 *
 *  Created on: Apr 14, 2020
 *      Author: malna
 */
#ifndef PROVIDED_H_
#define PROVIDED_H_

#define PORT_MCLK_OUT (P4)
#define BITM_MCLK_OUT (BIT3)

void setup_DCO(void);
void mapout_MCLK(void);

#endif /* PROVIDED_H_ */
