/*
 * mlnlib.cpp
 *
 * Created: 03.04.2023 11:13:26
 * Author : cedr0
 */ 

#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "mln/mln_gpio.h"

mln_gpio led_builtin = mln_gpio(PB3, OUTPUT);
mln_gpio btn_builtin = mln_gpio(PB2, INPUT);

int main(void)
{
	led_builtin.invert(1);
	btn_builtin.invert(1);
	
    while (1) 
	{
		if(btn_builtin.get())
		{
			led_builtin.toggle();
			_delay_ms(250);
		}
    }
	/* while (1)
	{
		if(PORTB.IN & 128)
		{
			PORTB.OUT ^= 8;
			_delay_ms(250);
		}
	} */
}

