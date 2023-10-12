#include <avr/sleep.h>
#include <util/delay.h>

#include "beeper.h"

int main(){

  beeper_init();

  beeper_tone(62);
  _delay_ms(1000.0);

  beeper_tone(124);
  _delay_ms(1000.0);

  beeper_tone(90);
  _delay_ms(1000.0);

  // for(;;){}
  // for(;;){sleep_mode();}

  return 0;

}
