/*
 * Assignment04.c
 *
 * Created: 06-Apr-19 17:54:14
 * Author : radug
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "driver_7segment.h"
#include "driver_thermometer.h"

#define F_CPU 7372800

int main(void)
{
	init_7_segment();
	init_adc();	
	sei();
	
    while (1) 
    {
			
    }
}

