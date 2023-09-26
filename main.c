#include <stdint.h>
#include <avr/io.h>
#include <avr/sleep.h>

_Static_assert(UINT8_MAX==255);
_Static_assert(UINT16_MAX==65535);
_Static_assert(UINT32_MAX==4294967295);
// #define M0E8SH_0 4500000

#define DELAY_ON  180000
#define DELAY_DIM   3000

#define DELAY_OFF 500000

// void f_txled_on(){
//   DDRD |= (1<<5);
//   PORTD &= ~(1<<5);
// }

// void f_brightness(const uint8_t ceil){
//   DDRB |= (1<<5);
//   for(uint8_t i=0; 1; ++i){
//     if(i<ceil)
//       PORTB |= 1<<5;
//     else
//       PORTB &= ~(1<<5);
//   }
// }

static inline void delay(const uint32_t interval){
  for(uint32_t i=0; i<interval; ++i){
    __asm__ __volatile__("");
  }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
static inline void on(){
  PORTB |= 1<<5;
}
static inline void off(){
  PORTB &= ~(1<<5);
}
// static inline void flip(){
//   PORTB ^= 1<<5;
// }
#pragma GCC diagnostic pop

// https://stackoverflow.com/questions/2219829
// https://stackoverflow.com/questions/7083482

void f_blink_loop(){
  DDRB |= (1<<5);
  // for(;;){
  //   on(); delay(M0E8SH_X);
  //   off(); delay(M0E8SH_0);
  //   for(uint32_t i=0; i<DELAY_DIM; ++i){(i%20>0)?off():on();}
  //   off(); delay(M0E8SH_0);
  // }
  for(;;){
    on(); delay(DELAY_ON); off(); delay(DELAY_OFF);
    #define BEAT_WEAK 600
    #define BEAT_HALF   5
    for(uint32_t i=0; i<DELAY_DIM; ++i){(i%BEAT_WEAK>0)?off():on();} off(); delay(DELAY_OFF);
    for(uint32_t i=0; i<DELAY_DIM; ++i){(i%BEAT_WEAK>0)?off():on();} off(); delay(DELAY_OFF);
    for(uint32_t i=0; i<DELAY_DIM; ++i){(i%BEAT_HALF>0)?off():on();} off(); delay(DELAY_OFF);
    for(uint32_t i=0; i<DELAY_DIM; ++i){(i%BEAT_WEAK>0)?off():on();} off(); delay(DELAY_OFF);
    for(uint32_t i=0; i<DELAY_DIM; ++i){(i%BEAT_WEAK>0)?off():on();} off(); delay(DELAY_OFF);
  }
}

int main(){

  // f_brightness(15);

  f_blink_loop();

  // f_blink_tc0();

  // for(;;){sleep_mode();}

  return 0;

}