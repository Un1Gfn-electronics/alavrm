#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "beeper.h"

int main(){

  beeper_init();

  // beeper_tone(450);
  // wavelength
  const uint16_t a[] = {

    18181u,
    14430u,
    12134u,
    9090u,

    // 627u,

    // CS = 011

    // 560u, // A
    // 465u, // C*
    // 380u, // E

    // 280u, // A*
    // 233u, // C
    // 190u, // E*

    // 157u,

    // 140u, // A
    // 116u, // C
    //  95u, // E

    0u

  };

  for(;;){
    for(const uint16_t *p = a; *p!=0; ++p){
      beeper_tone(*p);
      _delay_ms(1000.0);
    }
    // beeper_end();
  }
  beeper_end();

  // for(;;){}
  // for(;;){sleep_mode();}

  return 0;

}
