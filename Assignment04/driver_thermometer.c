/*
 * driver_
 thermometer.c
 *
 * Created: 06-Apr-19 18:26:44
 *  Author: radug
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "driver_7segment.h"

uint8_t counter = 1;
bool update = false;
float temperature;

void init_timer1();

void init_adc()
{
	//Internal 1.1V Voltage Reference
	ADMUX |= _BV(REFS1);
	
	//Enable ADC (ADEN)
	ADCSRA |= _BV(ADEN);
	
	//Enable Interrupt (ADIE)
	ADCSRA |=  _BV(ADIE);
	
	//set port F as input
	DDRF = 0x00;
	init_timer1();
}

void init_timer1()
{
	//reset to avoid incorrect setup
	TCCR1A = 0;
	TCCR1B = 0;
	
	//initialize compare value
	//f = 360 hz
	//lower refresh rates are suitable as long as there are less than 4 segments lit up at the same time
	OCR1A=159;
	
	//reset counter
	TCNT1=0;
	
	//pre-scaler to clk/64
	TCCR1B |= _BV(CS12);
	TCCR1B &= ~(_BV(CS11));
	TCCR1B &= ~(_BV(CS10));

	//enable compare interrupt
	TIMSK1 |= _BV(OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
	//set bit to start conversion
	ADCSRA |= _BV(ADSC);
}

ISR(ADC_vect)
{

	//get temperature according to the formula in the TC1047A sensor datasheet
	temperature = (ADC - 500.0)/ 10.0;
	
	//having a 2nd decimal position is pointless as it's always 0
	display_7_segment(temperature, 1);
}