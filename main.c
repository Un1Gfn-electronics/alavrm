#include <stdint.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

_Static_assert(UINT8_MAX==255);
_Static_assert(UINT16_MAX==65535);
_Static_assert(UINT32_MAX==4294967295);
// #define M0E8SH_0 4500000

// #define DELAY_ON  180000
// #define DELAY_DIM   3000

// #define DELAY_OFF 500000

// #define H(REG,BIT) {REG|=_BV(BIT);}
// #define L(REG,BIT) {REG&=~_BV(BIT);}

// void f_brightness(const uint8_t ceil){
//   DDRB |= (1<<5);
//   for(uint8_t i=0; 1; ++i){
//     if(i<ceil)
//       PORTB |= 1<<5;
//     else
//       PORTB &= ~(1<<5);
//   }
// }

// static inline void delay(const uint32_t interval){
//   for(uint32_t i=0; i<interval; ++i){
//     // __asm__ __volatile__("");
//   }
// }

// static inline void cycle(const uint32_t half, const uint32_t n){
//   const uint32_t nn = n / half;
//   if(0==n){
//     for(;;){
//       PORTB &= ~(1<<PB1);
//       delay(half);
//       PORTB |= (1<<PB1);
//       delay(half);
//     }
//   }else{
//     for(uint32_t i=0; i<nn; ++i){
//       PORTB &= ~(1<<PB1);
//       delay(half);
//       PORTB |= (1<<PB1);
//       delay(half);
//     }
//   }
// }

// void f_pwm_loop(){
//   DDRB |= (1<<DDB1);
//   // static const uint32_t interval = 200;
//   cycle(100,200000);
//   cycle(200,200000);
//   cycle(300,200000);
//   cycle(410,0);

//   // for(uint32_t i=0; i<1000; ++i){PORTB &= ~(1<<PB1); delay(interval); PORTB |= (1<<PB1); delay(interval);}
//   // for(uint32_t i=0; i<1000; ++i){PORTB &= ~(1<<PB1); delay(interval); PORTB |= (1<<PB1); delay(interval);}
//   // for(;;){PORTB &= ~(1<<PB1); delay(interval); PORTB |= (1<<PB1); delay(interval);}
//   // for(;;){sleep_mode();}
//   for(;;){}
// }

// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Warray-bounds"
// static inline void on(){
//   PORTB |= 1<<5;
// }
// static inline void off(){
//   PORTB &= ~(1<<5);
// }
// // static inline void flip(){
// //   PORTB ^= 1<<5;
// // }
// #pragma GCC diagnostic pop

// https://stackoverflow.com/questions/2219829
// https://stackoverflow.com/questions/7083482

// void f_blink_loop(){
//   DDRB |= (1<<5);
//   // for(;;){
//   //   on(); delay(M0E8SH_X);
//   //   off(); delay(M0E8SH_0);
//   //   for(uint32_t i=0; i<DELAY_DIM; ++i){(i%20>0)?off():on();}
//   //   off(); delay(M0E8SH_0);
//   // }
//   for(;;){
//     on(); delay(DELAY_ON); off(); delay(DELAY_OFF);
//     #define BEAT_WEAK 600
//     #define BEAT_HALF   5
//     for(uint32_t i=0; i<DELAY_DIM; ++i){(i%BEAT_WEAK>0)?off():on();} off(); delay(DELAY_OFF);
//     for(uint32_t i=0; i<DELAY_DIM; ++i){(i%BEAT_WEAK>0)?off():on();} off(); delay(DELAY_OFF);
//     for(uint32_t i=0; i<DELAY_DIM; ++i){(i%BEAT_HALF>0)?off():on();} off(); delay(DELAY_OFF);
//     for(uint32_t i=0; i<DELAY_DIM; ++i){(i%BEAT_WEAK>0)?off():on();} off(); delay(DELAY_OFF);
//     for(uint32_t i=0; i<DELAY_DIM; ++i){(i%BEAT_WEAK>0)?off():on();} off(); delay(DELAY_OFF);
//   }
// }

// void f_3led(){
//   DDRD |= (1<<DDD0)|(1<<DDD1)|(1<<DDD5);
//   DDRB |= (1<<DDB1)|(1<<DDB5);
//   static const uint8_t d_high_off = (1<<PD0)|(1<<PD1)|(1<<PD5);
//   static const uint8_t b_high_on = (1<<PB1)|(1<<PB5);
//   for(;;){
//     PORTD |= d_high_off;
//     PORTB &= ~b_high_on;
//     delay(180000);
//     PORTD &= ~d_high_off;
//     PORTB |= b_high_on;
//     delay(180000);
//   }
// }

// // OC0A - Port.D.6 - IO6
// void f_pwm_tcc0(){


//   cli();

//   // 17.3.1 - Alternate Functions of Port B - OC1A
//   // PWM mode timer function
//   // Timer/Counter1 Compare Match A
//   DDRD |= (1<<DDD6);

//   // set PWM for 50% duty cycle at 10bit
//   OCR1A = 0x01FF;

//   // set non-inverting mode
//   TCCR1A |= (1 << COM1A1);

//   // set 10bit phase corrected PWM Mode
//   TCCR1A |= (1 << WGM11) | (1 << WGM10);

//   // set prescaler to 8 and starts PWM
//   // TCCR1B |= (0<<CS12)|(0<<CS11)|(1<<CS10);
//   TCCR1B |= (0<<CS12)|(1<<CS11)|(0<<CS10);
//   // TCCR1B |= (0<<CS12)|(1<<CS11)|(1<<CS10);
//   // TCCR1B |= (1<<CS12)|(0<<CS11)|(0<<CS10);

//   sei();

//   for(;;){}

// }

// OC1A - PORT.B.1 - IO9
void f_pwm_tcc1(){

  cli();

  // 17.3.1 - Alternate Functions of Port B - OC1A
  // PWM mode timer function
  // Timer/Counter1 Compare Match A
  DDRB |= _BV(DDB1);

  // FastPWM.TOP_OCR1A
  // OCR1A = 65535;
  OCR1A = 500;

  // FastPWM.WGM_15 Toggle OC1A when TCT reaches TOP aka OCR1A
  TCCR1A &= ~_BV(COM1A1);
  TCCR1A |= _BV(COM1A0);

  // FastPWM.TOP_OCR1A
  TCCR1B |= _BV(WGM13) | _BV(WGM12);
  TCCR1A |= _BV(WGM11) | _BV(WGM10);

  // prescaler
  TCCR1B |= _BV(CS11);

  sei();

  for(;;){}

}

// static const uint16_t value = 3035;

// static uint8_t pd7_io7 = 0b00000000;

// ISR(TIMER1_OVF_vect){
//   pd7_io7 ^= (1<<DDB7);
//   TCNT1 = value; // preload timer
//   PORTD = pd7_io7;
//   reti();
// }

// void f_int(){
//   cli();
//   TCCR1A = 0b00000000;
//   TCCR1B = 0b00000000;
//   TCNT1 = value;                       // preload timer
//   TCCR1B |= (1<<CS10)|(1<<CS12);      // 1024 prescaler
//   TIMSK1 |= (1<<TOIE1);               // enable timer overflow interrupt ISR aka TIMER1_OVF_vect
//   sei();
//   DDRD |= (1<<PB7);
// }

int main(){

  // f_brightness(15);

  // f_blink_loop();
  // f_blink_tc0();
  // f_3led();

  f_pwm_tcc1();
  // f_pwm_loop();

  // f_int();

  // for(;;){sleep_mode();}

  return 0;

}