/* 
* mln_gpio.cpp
*
* Created: 03.04.2023 11:41:24
* Author: cedr0
*/


#include "mln_gpio.h"


#define BITMAP(pin) (1 << pin)

// default constructor
mln_gpio::mln_gpio(PIN_t new_pin, PIN_DIR_t new_dir, uint8_t new_inverted)
{
	pin = new_pin;
	inverted = new_inverted;
	
	conf_dir(new_dir);
} //mln_gpio

void mln_gpio::conf_dir(PIN_DIR_t new_dir)
{
	dir = new_dir;
	
	if(dir == OUTPUT)
		pin.port.DIR |= (1 << pin.pin_num);
	else
		pin.port.DIR &= ~(1 << pin.pin_num);
	
	conf_pull(new_dir);
}

void mln_gpio::conf_pull(PIN_DIR_t dir)
{
	if(dir == INPUT_PULLUP)
		*((uint8_t *)(&pin.port) + 0x10 + pin.pin_num) |= PORT_PULLUPEN_bm;
	else
		*((uint8_t *)(&pin.port) + 0x10 + pin.pin_num) &= ~PORT_PULLUPEN_bm;
}

void mln_gpio::set(void)
{
	inverted ? pin.port.DIRCLR = BITMAP(pin.pin_num) : pin.port.DIRSET = BITMAP(pin.pin_num);
}

void mln_gpio::clear(void)
{
	inverted ? pin.port.DIRSET = BITMAP(pin.pin_num) : pin.port.DIRCLR = BITMAP(pin.pin_num);
}

void mln_gpio::toggle(void)
{
	pin.port.DIR ^= BITMAP(pin.pin_num);
}

void mln_gpio::put(uint8_t val)
{
	val ? inverted ? clear() : set() : clear();
}

void mln_gpio::invert(uint8_t new_inverted)
{
	if(dir == OUTPUT && new_inverted != inverted)
		toggle();
	
	inverted = new_inverted;
}

uint8_t mln_gpio::get(void)
{
	return inverted ? !(pin.port.OUT >> pin.pin_num) & 0x01 : (pin.port.OUT >> pin.pin_num) & 0x01;
}