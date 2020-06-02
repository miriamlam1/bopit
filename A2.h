#ifndef A2_H_
#define A2_H_

#define FREQ_1_5_MHz 1500000
#define FREQ_3_MHz 3000000
#define FREQ_6_MHz 6000000
#define FREQ_12_MHz 12000000
#define FREQ_24_MHz 24000000

void set_DCO(int freq);
void delay_us(int delay);

#endif /* A2_H_ */
