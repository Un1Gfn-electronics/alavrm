#include <stdint.h>
#include <avr/io.h>
#include <avr/sleep.h>

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

// https://stackoverflow.com/questions/2219829
// https://stackoverflow.com/questions/7083482
void f_blink_loop(const uint32_t until){
  DDRB |= (1<<5);
  _Static_assert(UINT16_MAX==65535);
  _Static_assert(UINT32_MAX==4294967295);
  for(;;){
    // PORTB ^= 1<<5;
    PORTB |= 1<<5;
    for(uint32_t i=0; i<until; ++i){
      __asm__ __volatile__("");
    }
    PORTB &= ~(1<<5);
    for(uint32_t i=0; i<until; ++i){
      __asm__ __volatile__("");
    }
  }
}

int main(){

  // f_brightness(15);

  f_blink_loop(50000);

  // f_blink_tc0();

  // for(;;){sleep_mode();}

  return 0;

}