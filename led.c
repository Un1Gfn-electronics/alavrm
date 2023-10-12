
_Static_assert(UINT8_MAX==255);
_Static_assert(UINT16_MAX==65535);
_Static_assert(UINT32_MAX==4294967295);
#define M0E8SH_0 4500000

#define DELAY_ON  180000
#define DELAY_DIM   3000

#define DELAY_OFF 500000

void f_brightness(const uint8_t ceil){
  DDRB |= (1<<5);
  for(uint8_t i=0; 1; ++i){
    if(i<ceil)
      PORTB |= 1<<5;
    else
      PORTB &= ~(1<<5);
  }
}

static inline void delay(const uint32_t interval){
  for(uint32_t i=0; i<interval; ++i){
    // __asm__ __volatile__("");
  }
}

static inline void cycle(const uint32_t half, const uint32_t n){
  const uint32_t nn = n / half;
  if(0==n){
    for(;;){
      PORTB &= ~(1<<PB1);
      delay(half);
      PORTB |= (1<<PB1);
      delay(half);
    }
  }else{
    for(uint32_t i=0; i<nn; ++i){
      PORTB &= ~(1<<PB1);
      delay(half);
      PORTB |= (1<<PB1);
      delay(half);
    }
  }
}

void f_pwm_loop(){
  DDRB |= (1<<DDB1);
  // static const uint32_t interval = 200;
  cycle(100,200000);
  cycle(200,200000);
  cycle(300,200000);
  cycle(410,0);

  // for(uint32_t i=0; i<1000; ++i){PORTB &= ~(1<<PB1); delay(interval); PORTB |= (1<<PB1); delay(interval);}
  // for(uint32_t i=0; i<1000; ++i){PORTB &= ~(1<<PB1); delay(interval); PORTB |= (1<<PB1); delay(interval);}
  // for(;;){PORTB &= ~(1<<PB1); delay(interval); PORTB |= (1<<PB1); delay(interval);}
  // for(;;){sleep_mode();}
  for(;;){}
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

https://stackoverflow.com/questions/2219829
https://stackoverflow.com/questions/7083482

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

void f_3led(){
  DDRD |= (1<<DDD0)|(1<<DDD1)|(1<<DDD5);
  DDRB |= (1<<DDB1)|(1<<DDB5);
  static const uint8_t d_high_off = (1<<PD0)|(1<<PD1)|(1<<PD5);
  static const uint8_t b_high_on = (1<<PB1)|(1<<PB5);
  for(;;){
    PORTD |= d_high_off;
    PORTB &= ~b_high_on;
    delay(180000);
    PORTD &= ~d_high_off;
    PORTB |= b_high_on;
    delay(180000);
  }
}

static const uint16_t value = 3035;

static uint8_t pd7_io7 = 0b00000000;

ISR(TIMER1_OVF_vect){
  pd7_io7 ^= (1<<DDB7);
  TCNT1 = value; // preload timer
  PORTD = pd7_io7;
  reti();
}

void f_int(){
  cli();
  TCCR1A = 0b00000000;
  TCCR1B = 0b00000000;
  TCNT1 = value;                       // preload timer
  TCCR1B |= (1<<CS10)|(1<<CS12);      // 1024 prescaler
  TIMSK1 |= (1<<TOIE1);               // enable timer overflow interrupt ISR aka TIMER1_OVF_vect
  sei();
  DDRD |= (1<<PB7);
}
