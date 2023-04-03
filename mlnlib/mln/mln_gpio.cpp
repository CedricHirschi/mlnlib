/* 
* mln_gpio.cpp
*
* Created: 03.04.2023 11:41:24
* Author: cedr0
*/


#include "mln_gpio.h"

PORT_t mln_gpio_ports[] = {
	PORTA, PORTC, PORTD,
	#ifdef PORTB
	PORTB,
	#endif
	#ifdef PORTE
	PORTE,
	#endif
	PORTF,
	#ifdef PORTG
	PORTG
	#endif
};

PORT_t MLN_GPIO_PIN_GET_PORT(PIN_t pin)
{
	return mln_gpio_ports[pin / 8];
}

uint8_t MLN_GPIO_PIN_GET_NUM(PIN_t pin)
{
	return pin % 8;
}

// default constructor
mln_gpio::mln_gpio(PIN_t new_pin, PIN_DIR_t new_dir)
{
	pin = new_pin;
	port = MLN_GPIO_PIN_GET_PORT(new_pin);
	pin_num = MLN_GPIO_PIN_GET_NUM(new_pin);
	
	set_dir(new_dir);
} //mln_gpio

void mln_gpio::set_dir(PIN_DIR_t new_dir)
{
	dir = new_dir;
	
	switch(dir)
	{
		case OUTPUT:
			break;
		case INPUT:
			break;
		case INPUT_PULLUP:
			break;
	}
}
