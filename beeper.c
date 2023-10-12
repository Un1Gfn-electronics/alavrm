#include <avr/io.h>
#include <avr/interrupt.h>

#include "beeper.h"

void beeper_init(){

  cli();

  // 17.3.1 - Alternate Functions of Port B - OC1A
  // PWM mode timer function
  // Timer/Counter1 Compare Match A
  H(DDRB, DDB1);

  // FastPWM.WGM_15 Toggle OC1A when TCT reaches TOP aka OCR1A
  L(TCCR1A, COM1A1);
  H(TCCR1A, COM1A0);

  // FastPWM.TOP_OCR1A
  H(TCCR1B, WGM13);
  H(TCCR1B, WGM12);
  H(TCCR1A, WGM11);
  H(TCCR1A, WGM10);

  // prescaler
  L(TCCR1B, CS12);
  H(TCCR1B, CS11);
  H(TCCR1B, CS10);

}


void beeper_tone(uint16_t tone){

  cli();

  // FastPWM.TOP_OCR1A
  OCR1A = tone;

  sei();

}
