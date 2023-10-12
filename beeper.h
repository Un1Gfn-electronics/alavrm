#ifndef PWM_H
#define PWM_H

#include <stdint.h>

#define H(REG,BIT) {REG|=_BV(BIT);}
#define L(REG,BIT) {REG&=~_BV(BIT);}

void beeper_init();

void beeper_tone(uint16_t);

#endif
