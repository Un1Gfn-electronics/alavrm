#include "beeper.h"

void song();

// file:///Users/darren/bible.lilypond/2562095675.ly

int main(){

  // cli();
  // sei();
  beeper_init();

  // A major chord
  // beeper_unit = 20;
  // beeper_tone(1,18181);
  // beeper_tone(1,14430);
  // beeper_tone(1,12134);
  // beeper_tone(1,9090);

  beeper_unit = 5;
  for(;;){
    song();
  }

  beeper_end();
  // for(;;){sleep_mode();}

  return 0;

}
