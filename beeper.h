#ifndef PWM_H
#define PWM_H

#include <stdint.h>

#define H(REG,BIT) {REG|=_BV(BIT);}
#define L(REG,BIT) {REG&=~_BV(BIT);}

extern uint16_t beeper_unit;

void beeper_init();
void beeper_tone(uint16_t, uint16_t);
void P(const char*, uint16_t);
void beeper_end();

#endif
