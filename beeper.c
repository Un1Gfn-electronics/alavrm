#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <string.h>

#include "beeper.h"

uint16_t beeper_unit = 10;

void P(const char *s, uint16_t pitch){
  uint16_t rhythm = 0;
  if(0==strcmp(s, "\\breve")) rhythm = 64;
  else if(0==strcmp(s, "1"))  rhythm = 32;
  else if(0==strcmp(s, "2"))  rhythm = 16;
  else if(0==strcmp(s, "4"))  rhythm = 8;
  else if(0==strcmp(s, "8"))  rhythm = 4;
  else if(0==strcmp(s, "16")) rhythm = 2;
  else if(0==strcmp(s, "32")) rhythm = 1;
  else if(0==strcmp(s, "1.")) rhythm = 48;
  else if(0==strcmp(s, "2.")) rhythm = 24;
  else if(0==strcmp(s, "4.")) rhythm = 12;
  else if(0==strcmp(s, "8.")) rhythm = 6;
  else if(0==strcmp(s, "16.")) rhythm = 3;
  else for(;;){sleep_mode();}
  beeper_tone(rhythm, pitch);
}

void beeper_init(){

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

  // prescaler=1
  L(TCCR1B, CS12);
  L(TCCR1B, CS11);
  H(TCCR1B, CS10);

  // prescaler=8
  // L(TCCR1B, CS12);
  // H(TCCR1B, CS11);
  // L(TCCR1B, CS10);

  // prescaler=32
  // L(TCCR1B, CS12);
  // H(TCCR1B, CS11);
  // H(TCCR1B, CS10);

}

void beeper_tone(uint16_t rhythm, uint16_t tone){
  // FastPWM.TOP_OCR1A
  if(0==tone){
    L(DDRB, DDB1);
  }else{
    OCR1A = tone;
    H(DDRB, DDB1);
  }
  // _delay_ms(ms); // __builtin_avr_delay_cycles expects a compile time integer constant
  for(uint16_t i=beeper_unit*rhythm; i!=0; --i){
    _delay_loop_2(UINT16_MAX);
  }
}

void beeper_end(){
  TCCR1A = 0;
  TCCR1B = 0;
  L(DDRB, DDB1);
}
