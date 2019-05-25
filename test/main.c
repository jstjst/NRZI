//----- test timer

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int main (void)
{
  DDRD &= ~_BV(DDD2);   //PD2(INT0) Input
  EIMSK |= _BV(INT0);    //enable INT0
  EICRA |= _BV(ISC00);  //INT0 at change

  DDRD |= _BV(DDD6) | _BV(DDD7);    //PD6(OC0A) Output

  TCCR0A |= _BV(WGM01); //CTC (TOP at OCR0A)
  TCCR0B |= _BV(CS00) | _BV(CS01);  // clk/64

  OCR0A |= 208;         //Overflow after 208 cycles (833µs/1200Hz)
  OCR0B |= 104;         //Overflow after 104 cycles (416µs)

  TIMSK0 |= _BV(OCIE0B);  //Interrupt at OCR0B

  sei();    //activate interrupts

  while(true)
  return 0;
}

ISR(INT0_vect)
{
  TCNT0 = 0;    //clear timer to synchronize
  TCCR0B |= _BV(FOC0A);   //Fource Output Compare
}

ISR(TIMER0_COMPB_vect)
{
  PORTD ^= _BV(PORTD7);
  if (PIND & _BV(PIND2))
  {
    TCCR0A |= _BV(COM0A0) | _BV(COM0A1);   //Set OC0A on Compare Match
  }
  else
  {
    TCCR0A &= ~_BV(COM0A0);   //Clear OC0A on Compare Match
    TCCR0A |=  _BV(COM0A1);
  }
}
